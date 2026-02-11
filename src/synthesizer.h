/* synthesizer.h
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
// Header file for speech synthesis functions and data structures
// =====================================================================
#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "phonemes.h"

// =====================================================================================
// Global Constants and Defines
// =====================================================================================
#define SAMPLE_RATE 16000
#define MAX_SAMPLES (SAMPLE_RATE * 5) // 5 seconds max
#define MAX_AMPLITUDE 32767
#define FRAME_PERIOD_MS 10
#define FRAME_PERIOD_S (FRAME_PERIOD_MS / 1000.0)
#define SILENCE_DURATION_MS 200 // Duration of silence between words

// Define this macro to enable debug printing
//#define DEBUG_PRINTF 1
#define DEBUG_PRINTF 0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// =====================================================================================
// Data Structures
// =====================================================================================
// Represents a single Klatt filter (a second-order resonator)
typedef struct {
    double frequency;
    double bandwidth;
    double radius;
    double angle;
    double a1;
    double a2;
    double y1;
    double y2;
} KlattFilter;

// =====================================================================================
// Function Prototypes
// =====================================================================================
void reset_synthesis_engine_state();
void initialize_filter(KlattFilter *filter, double frequency, double bandwidth);
void update_filter_coefficients(KlattFilter *filter, double frequency, double bandwidth);
double process_filter(KlattFilter *filter, double input);
double generate_glottal_pulse_derivative(double F0, double amplitude);
double generate_noise_source(double amplitude);
void initialize_high_pass_filter();
double process_high_pass_filter(double input);
PhonemeParams interpolate_params(const PhonemeParams *p1, const PhonemeParams *p2, int total_frames, int current_frame);
void synthesize_frame(const PhonemeParams *params, double *audio_buffer, int *current_sample);
void synthesize_diphone(const Diphone *diphone, double *audio_buffer, int *current_sample);
void normalize_and_write_to_file(const char* filename, double* buffer, int num_samples, int sample_rate);
void write_wav_header(FILE* file, int num_samples, int sample_rate);

#endif // SYNTHESIZER_H
