/* synthesizer.c
 *
 * Copyright 2026 Alan Crispin <crispinalan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// =====================================================================
// Implementation of the speech synthesis logic
// =====================================================================
#include "synthesizer.h"
#include "phonemes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

// =====================================================================================
// Global Variables for the Synthesis Engine (defined here)
// =====================================================================================
double glottal_pulse_phase = 0.0;
double glottal_pulse_last_sample = 0.0;
unsigned int random_seed = 1;

KlattFilter f1, f2, f3, f4, f5, f6; // Main formant filters for voiced source
KlattFilter fn_noise;               // A separate parallel filter for the noise source

// High-pass filter for DC offset removal
double hp_a1 = 0.0;
double hp_b0 = 0.0;
double hp_b1 = 0.0;
double hp_y1 = 0.0;
double hp_x1 = 0.0;

// =====================================================================================
// Synthesis Engine Functions
// =====================================================================================

// Resets the state of the entire synthesis engine
void reset_synthesis_engine_state() {
    glottal_pulse_phase = 0.0;
    glottal_pulse_last_sample = 0.0;
    random_seed = 1;

    // Reset all filters
    initialize_filter(&f1, 0, 0);
    initialize_filter(&f2, 0, 0);
    initialize_filter(&f3, 0, 0);
    initialize_filter(&f4, 0, 0);
    initialize_filter(&f5, 0, 0);
    initialize_filter(&f6, 0, 0);
    initialize_filter(&fn_noise, 0, 0);
    initialize_high_pass_filter();
}


// Initializes the filter to a quiescent state
void initialize_filter(KlattFilter *filter, double frequency, double bandwidth) {
if (frequency == 0.0 || bandwidth == 0.0) {
        filter->frequency = 0.0;
        filter->bandwidth = 0.0;
        filter->a1 = 0.0;
        filter->a2 = 0.0;
        filter->y1 = 0.0;
        filter->y2 = 0.0;
        return;
    }
    
    double dt = 1.0 / SAMPLE_RATE;
    double r = exp(-M_PI * bandwidth * dt);
    double theta = 2 * M_PI * frequency * dt;
    filter->radius = r;
    filter->angle = theta;
    filter->a1 = -2.0 * r * cos(theta);
    filter->a2 = r * r;
    filter->y1 = 0.0;
    filter->y2 = 0.0;
    filter->frequency = frequency;
    filter->bandwidth = bandwidth;
}

// Updates a Klatt filter's coefficients without resetting state
void update_filter_coefficients(KlattFilter *filter, double frequency, double bandwidth) {
   if (frequency == 0.0 || bandwidth == 0.0) {
        // If frequency or bandwidth is zero, turn off the filter.
        filter->frequency = 0.0;
        filter->bandwidth = 0.0;
        filter->a1 = 0.0;
        filter->a2 = 0.0;
        return;
    }
    
    double dt = 1.0 / SAMPLE_RATE;
    double r = exp(-M_PI * bandwidth * dt);
    double theta = 2 * M_PI * frequency * dt;
    filter->radius = r;
    filter->angle = theta;
    filter->a1 = -2.0 * r * cos(theta);
    filter->a2 = r * r;
    filter->frequency = frequency;
    filter->bandwidth = bandwidth;
}

// Applies the filter to an input sample and returns the output
double process_filter(KlattFilter *filter, double input) {
    if (filter->frequency == 0.0) {
        return input;
    }
    double output = input - filter->a1 * filter->y1 - filter->a2 * filter->y2;
    filter->y2 = filter->y1;
    filter->y1 = output;
    return output;
}

// Generates the glottal pulse derivative (Fant's model)
double generate_glottal_pulse_derivative(double F0, double amplitude) {
    if (F0 <= 0.0 || amplitude == 0.0) {
        glottal_pulse_phase = 0.0;
        glottal_pulse_last_sample = 0.0;
        return 0.0;
    }

    double T0 = 1.0 / F0; // Period
    double dt = 1.0 / SAMPLE_RATE;
    
    // Increment the phase
    glottal_pulse_phase += dt;
    if (glottal_pulse_phase >= T0) {
        glottal_pulse_phase -= T0;
    }

    double alpha = 0.3; // Asymmetry parameter
    double beta = 0.05; // Smoothing parameter
    double T_open = T0 * alpha; // Open phase duration
    double T_close = T0 * beta; // Closing phase duration

    double output;
    if (glottal_pulse_phase < T_open) {
        // Opening phase
        output = sin(M_PI * glottal_pulse_phase / T_open);
    } else {
        // Closing phase
        double t_prime = glottal_pulse_phase - T_open;
        output = -sin(M_PI * t_prime / T_close);
    }

    // High-pass filter the glottal source to create the derivative-like shape
    double hp_output = output - glottal_pulse_last_sample;
    glottal_pulse_last_sample = output;

    return hp_output * amplitude;
}

double generate_noise_source(double amplitude) {
    if (amplitude == 0.0) {
        return 0.0;
    }
    
    // Use a simple pseudo-random number generator
    random_seed = random_seed * 1103515245 + 12345;
    double random_val = ((double)random_seed / (double)UINT32_MAX) * 2.0 - 1.0;
    
    // Filter the noise with a simple pole
    double noise_output = process_filter(&fn_noise, random_val);

    return noise_output * amplitude;
}

// High-pass filter initialization
void initialize_high_pass_filter() {
    double cutoff_freq_hz = 50.0;
    double theta_c = 2.0 * M_PI * cutoff_freq_hz / SAMPLE_RATE;
    hp_a1 = (1.0 - theta_c) / (1.0 + theta_c);
    hp_b0 = 0.5 * (1.0 + hp_a1);
    hp_b1 = -0.5 * (1.0 + hp_a1);
    hp_y1 = 0.0;
    hp_x1 = 0.0;
}


// High-pass filter to remove DC offset
double process_high_pass_filter(double input) {
    double output = hp_b0 * input + hp_b1 * hp_x1 - hp_a1 * hp_y1;
    hp_y1 = output;
    hp_x1 = input;
    return output;
}


// Linear interpolation of phoneme parameters
PhonemeParams interpolate_params(const PhonemeParams *p1, const PhonemeParams *p2, int total_frames, int current_frame) {
    PhonemeParams interpolated;
    double t = (double)current_frame / (double)total_frames;
    
    interpolated.F0 = p1->F0 + t * (p2->F0 - p1->F0);
    interpolated.F1 = p1->F1 + t * (p2->F1 - p1->F1);
    interpolated.B1 = p1->B1 + t * (p2->B1 - p1->B1);
    interpolated.F2 = p1->F2 + t * (p2->F2 - p1->F2);
    interpolated.B2 = p1->B2 + t * (p2->B2 - p1->B2);
    interpolated.F3 = p1->F3 + t * (p2->F3 - p1->F3);
    interpolated.B3 = p1->B3 + t * (p2->B3 - p1->B3);
    interpolated.F4 = p1->F4 + t * (p2->F4 - p1->F4);
    interpolated.B4 = p1->B4 + t * (p2->B4 - p1->B4);
    interpolated.F5 = p1->F5 + t * (p2->F5 - p1->F5);
    interpolated.B5 = p1->B5 + t * (p2->B5 - p1->B5);
    interpolated.F6 = p1->F6 + t * (p2->F6 - p1->F6);
    interpolated.B6 = p1->B6 + t * (p2->B6 - p1->B6);
    interpolated.FN = p1->FN + t * (p2->FN - p1->FN);
    interpolated.BN = p1->BN + t * (p2->BN - p1->BN);
    interpolated.AF = p1->AF + t * (p2->AF - p1->AF);
    interpolated.AN = p1->AN + t * (p2->AN - p1->AN);
    
    return interpolated;
}

// Synthesizes a single frame of speech 
void synthesize_frame(const PhonemeParams *params, double *audio_buffer, int *current_sample) {
    
    // Update the Klatt filter coefficients for the current frame
    update_filter_coefficients(&f1, params->F1, params->B1);
    update_filter_coefficients(&f2, params->F2, params->B2);
    update_filter_coefficients(&f3, params->F3, params->B3);
    update_filter_coefficients(&f4, params->F4, params->B4);
    update_filter_coefficients(&f5, params->F5, params->B5);
    update_filter_coefficients(&f6, params->F6, params->B6);
    
    // Determine the number of samples in this frame
    int num_frame_samples = (int)(SAMPLE_RATE * FRAME_PERIOD_S);
    
    for (int i = 0; i < num_frame_samples; i++) {
        // Generate the glottal and noise sources
        double voiced_source = generate_glottal_pulse_derivative(params->F0, params->AF);
        double noise_source = generate_noise_source(params->AN);
        
        // The total source is the sum of voiced and unvoiced sources
        double total_source = voiced_source + noise_source;
        
        // Pass the source through the parallel Klatt filters
        double output_f1 = process_filter(&f1, total_source);
        double output_f2 = process_filter(&f2, total_source);
        double output_f3 = process_filter(&f3, total_source);
        double output_f4 = process_filter(&f4, total_source);
        double output_f5 = process_filter(&f5, total_source);
        double output_f6 = process_filter(&f6, total_source);
        
        // Sum the outputs of all parallel filters
        double output_sample = (output_f1 + output_f2 + output_f3 + output_f4 + output_f5 + output_f6);
        
        // Apply high-pass filter to remove DC offset
        output_sample = process_high_pass_filter(output_sample);
        
        if (*current_sample < MAX_SAMPLES) {
            audio_buffer[*current_sample] = output_sample;
        }
        (*current_sample)++;
    }
}

// Synthesizes a single diphone and adds the output to a buffer
void synthesize_diphone(const Diphone *diphone, double *audio_buffer, int *current_sample) {
    // Calculate total frames for the diphone
    //int total_frames = diphone->start_frames + diphone->transition_frames + diphone->end_frames;

    if(DEBUG_PRINTF)
    printf("Synthesizing diphone with p1->F1: %f and p1->AF: %f\n", diphone->p1->F1, diphone->p1->AF);
    

    // Stage 1: Initial phoneme (p1)
    for (int i = 0; i < diphone->start_frames; i++) {
        synthesize_frame(diphone->p1, audio_buffer, current_sample);
    }

    // Stage 2: Transition from p1 to p2
    for (int i = 0; i < diphone->transition_frames; i++) {
        PhonemeParams interpolated = interpolate_params(diphone->p1, diphone->p2, diphone->transition_frames, i);
        synthesize_frame(&interpolated, audio_buffer, current_sample);
    }

    // Stage 3: End phoneme (p2)
    for (int i = 0; i < diphone->end_frames; i++) {
        synthesize_frame(diphone->p2, audio_buffer, current_sample);
    }
}

// Function to write the WAV header
void write_wav_header(FILE* file, int num_samples, int sample_rate) {
    int num_channels = 1; // Mono
    int byte_rate = sample_rate * num_channels * sizeof(int16_t);
    int total_file_size = 36 + num_samples * num_channels * sizeof(int16_t);
    
    // RIFF chunk
    fwrite("RIFF", 1, 4, file);
    fwrite(&total_file_size, 4, 1, file);
    fwrite("WAVE", 1, 4, file);
    
    // fmt chunk
    fwrite("fmt ", 1, 4, file);
    int fmt_chunk_size = 16;
    fwrite(&fmt_chunk_size, 4, 1, file);
    int audio_format = 1; // PCM
    fwrite(&audio_format, 2, 1, file);
    fwrite(&num_channels, 2, 1, file);
    fwrite(&sample_rate, 4, 1, file);
    fwrite(&byte_rate, 4, 1, file);
    int block_align = num_channels * sizeof(int16_t);
    fwrite(&block_align, 2, 1, file);
    int bits_per_sample = 16;
    fwrite(&bits_per_sample, 2, 1, file);
    
    // data chunk
    fwrite("data", 1, 4, file);
    int total_data_size = num_samples * sizeof(int16_t);
    fwrite(&total_data_size, 4, 1, file);
}

// Normalizes the audio buffer and writes it to a WAV file
void normalize_and_write_to_file(const char* filename, double* buffer, int num_samples, int sample_rate) {
    // Find the maximum absolute value for normalization
    double max_abs = 0.0;
    for (int i = 0; i < num_samples; i++) {
        double abs_val = fabs(buffer[i]);
        if (abs_val > max_abs) {
            max_abs = abs_val;
        }
    }
    
    // Open the WAV file
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s for writing.\n", filename);
        return;
    }
    
    // Write the WAV header
    write_wav_header(file, num_samples, sample_rate);
    
    // Normalize and convert to 16-bit integers, then write to file
    double norm_factor = (max_abs > 0.0) ? MAX_AMPLITUDE / max_abs : 0.0;
    int16_t sample_int;
    for (int i = 0; i < num_samples; i++) {
        sample_int = (int16_t)(buffer[i] * norm_factor);
        fwrite(&sample_int, 2, 1, file);
    }
    
    fclose(file);
    
    if(DEBUG_PRINTF)
    printf("Saved file: %s with %d samples. Max abs value: %f\n", filename, num_samples, max_abs);
    
}
