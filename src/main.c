/* main.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include "phonemes.h"
#include "synthesizer.h"


// Function prototypes
void synthesize_word_and_save(const char* word_name, const Diphone* diphones, int num_diphones);
void synthesize_phrase_and_save(const char* filename, const Diphone** word_diphones, int* num_diphones, int num_words);

// Dictionaries for date components
const char* weekdays[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
const char* months[] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
const char* ordinal_digits[] = {"first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth", "twenty-first", "twenty-second", "twenty-third", "twenty-fourth", "twenty-fifth", "twenty-sixth", "twenty-seventh", "twenty-eighth", "twenty-ninth", "thirtieth", "thirty-first"};

int main(void) {
    
    printf("Date reader speech synthesizer up and running ...\n");
    // Reset the synthesis engine state once at the beginning
    reset_synthesis_engine_state();
    //say hello
    
     // Get the current day of the week and day of the month
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_day_of_week = tm.tm_wday; // 0 = Sunday, 1 = Monday, etc.
    int current_day_of_month = tm.tm_mday;//current day of the month (1-31)
    int current_month_index = tm.tm_mon; //month (0=Jan, 7=Aug)
    int current_year = tm.tm_year+1900;
    printf("date: %d-%d-%d\n",current_day_of_month,current_month_index+1,current_year);
    
    const char* weekday =weekdays[tm.tm_wday];
    const char* ordinal_day =ordinal_digits[tm.tm_mday - 1]; // Array is 0-indexed
    const char* month = months[tm.tm_mon];
    
    printf("speech synthesizer saying: %s %s %s\n",weekday,ordinal_day,month);
    
    const Diphone* date_phrase_diphones[3];
    int num_diphones_in_date_phrase[3];
    
    // Select the correct day of the week
    switch (current_day_of_week) {
        case 0: date_phrase_diphones[0] = diphones_sunday; num_diphones_in_date_phrase[0] = num_diphones_sunday; break;
        case 1: date_phrase_diphones[0] = diphones_monday; num_diphones_in_date_phrase[0] = num_diphones_monday; break;
        case 2: date_phrase_diphones[0] = diphones_tuesday; num_diphones_in_date_phrase[0] = num_diphones_tuesday; break;
        case 3: date_phrase_diphones[0] = diphones_wednesday; num_diphones_in_date_phrase[0] = num_diphones_wednesday; break;
        case 4: date_phrase_diphones[0] = diphones_thursday; num_diphones_in_date_phrase[0] = num_diphones_thursday; break;
        case 5: date_phrase_diphones[0] = diphones_friday; num_diphones_in_date_phrase[0] = num_diphones_friday; break;
        case 6: date_phrase_diphones[0] = diphones_saturday; num_diphones_in_date_phrase[0] = num_diphones_saturday; break;
        default:
            fprintf(stderr, "Error: Invalid day of week.\n");
            return 1;
    }

    //Select the correct day of the month
    switch (current_day_of_month) {
		case 1: date_phrase_diphones[1] = diphones_first; num_diphones_in_date_phrase[1] = num_diphones_first; break;
		case 2: date_phrase_diphones[1] = diphones_second; num_diphones_in_date_phrase[1] = num_diphones_second; break;
		case 3: date_phrase_diphones[1] = diphones_third; num_diphones_in_date_phrase[1] = num_diphones_third; break;
        case 4: date_phrase_diphones[1] = diphones_fourth; num_diphones_in_date_phrase[1] = num_diphones_fourth; break;
        case 5: date_phrase_diphones[1] = diphones_fifth; num_diphones_in_date_phrase[1] = num_diphones_fifth; break;
        case 6: date_phrase_diphones[1] = diphones_sixth; num_diphones_in_date_phrase[1] = num_diphones_sixth; break;
        case 7: date_phrase_diphones[1] = diphones_seventh; num_diphones_in_date_phrase[1] = num_diphones_seventh; break;
        case 8: date_phrase_diphones[1] = diphones_eighth; num_diphones_in_date_phrase[1] = num_diphones_eighth; break;
        case 9: date_phrase_diphones[1] = diphones_ninth; num_diphones_in_date_phrase[1] = num_diphones_ninth; break;
        case 10: date_phrase_diphones[1] = diphones_tenth; num_diphones_in_date_phrase[1] = num_diphones_tenth; break;
        case 11: date_phrase_diphones[1] = diphones_eleventh; num_diphones_in_date_phrase[1] = num_diphones_eleventh; break;
        case 12: date_phrase_diphones[1] = diphones_twelfth; num_diphones_in_date_phrase[1] = num_diphones_twelfth; break;
        case 13: date_phrase_diphones[1] = diphones_thirteenth; num_diphones_in_date_phrase[1] = num_diphones_thirteenth; break;       
        case 14: date_phrase_diphones[1] = diphones_fourteenth; num_diphones_in_date_phrase[1] = num_diphones_fourteenth; break;
        case 15: date_phrase_diphones[1] = diphones_fifteenth; num_diphones_in_date_phrase[1] = num_diphones_fifteenth; break;
        case 16: date_phrase_diphones[1] = diphones_sixteenth; num_diphones_in_date_phrase[1] = num_diphones_sixteenth; break;
        case 17: date_phrase_diphones[1] = diphones_seventeenth; num_diphones_in_date_phrase[1] = num_diphones_seventeenth; break;
        case 18: date_phrase_diphones[1] = diphones_eighteenth; num_diphones_in_date_phrase[1] = num_diphones_eighteenth; break;
        case 19: date_phrase_diphones[1] = diphones_nineteenth; num_diphones_in_date_phrase[1] = num_diphones_nineteenth; break;
        case 20: date_phrase_diphones[1] = diphones_twentieth; num_diphones_in_date_phrase[1] = num_diphones_twentieth; break;
        case 21: date_phrase_diphones[1] = diphones_twentyfirst; num_diphones_in_date_phrase[1] = num_diphones_twentyfirst; break;
        case 22: date_phrase_diphones[1] = diphones_twentysecond; num_diphones_in_date_phrase[1] = num_diphones_twentysecond; break;
        case 23: date_phrase_diphones[1] = diphones_twentythird; num_diphones_in_date_phrase[1] = num_diphones_twentythird; break;
        case 24: date_phrase_diphones[1] = diphones_twentyfourth; num_diphones_in_date_phrase[1] = num_diphones_twentyfourth; break;
        case 25: date_phrase_diphones[1] = diphones_twentyfifth; num_diphones_in_date_phrase[1] = num_diphones_twentyfifth; break;
        case 26: date_phrase_diphones[1] = diphones_twentysixth; num_diphones_in_date_phrase[1] = num_diphones_twentysixth; break;
        case 27: date_phrase_diphones[1] = diphones_twentyseventh; num_diphones_in_date_phrase[1] = num_diphones_twentyseventh; break;
        case 28: date_phrase_diphones[1] = diphones_twentyeighth; num_diphones_in_date_phrase[1] = num_diphones_twentyeighth; break;
        case 29: date_phrase_diphones[1] = diphones_twentyninth; num_diphones_in_date_phrase[1] = num_diphones_twentyninth; break;
        case 30: date_phrase_diphones[1] = diphones_thirtieth; num_diphones_in_date_phrase[1] = num_diphones_thirtieth; break;
        case 31: date_phrase_diphones[1] = diphones_thirtyfirst; num_diphones_in_date_phrase[1] = num_diphones_thirtyfirst; break;        
        default:
            fprintf(stderr, "Error: Invalid day of month.\n");
            return 1;
    }
    
    switch (current_month_index) {
        case 0: date_phrase_diphones[2] = diphones_january; num_diphones_in_date_phrase[2] = num_diphones_january; break;
        case 1: date_phrase_diphones[2] = diphones_february; num_diphones_in_date_phrase[2] = num_diphones_february; break;
        case 2: date_phrase_diphones[2] = diphones_march; num_diphones_in_date_phrase[2] = num_diphones_march; break;
        case 3: date_phrase_diphones[2] = diphones_april; num_diphones_in_date_phrase[2] = num_diphones_april; break;
        case 4: date_phrase_diphones[2] = diphones_may; num_diphones_in_date_phrase[2] = num_diphones_may; break;
        case 5: date_phrase_diphones[2] = diphones_june; num_diphones_in_date_phrase[2] = num_diphones_june; break;
        case 6: date_phrase_diphones[2] = diphones_july; num_diphones_in_date_phrase[2] = num_diphones_july; break;
        case 7: date_phrase_diphones[2] = diphones_august; num_diphones_in_date_phrase[2] = num_diphones_august; break;
        case 8: date_phrase_diphones[2] = diphones_september; num_diphones_in_date_phrase[2] = num_diphones_september; break;
        case 9: date_phrase_diphones[2] = diphones_october; num_diphones_in_date_phrase[2] = num_diphones_october; break;
        case 10: date_phrase_diphones[2] = diphones_november; num_diphones_in_date_phrase[2] = num_diphones_november; break;
        case 11: date_phrase_diphones[2] = diphones_december; num_diphones_in_date_phrase[2] = num_diphones_december; break; 
        default:
            fprintf(stderr, "Error: Invalid day of week.\n");
            return 1;
    }   

    
    int num_phrase_words=3; //e.g. monday second february
    
    synthesize_phrase_and_save("date.wav", date_phrase_diphones, num_diphones_in_date_phrase, num_phrase_words);
        
    char* aplay_str ="aplay -r 10000 -c 1 -f S16_LE date.wav"; 
    system(aplay_str); 
   

    return 0;
}

// =====================================================================
// Helper function to synthesize a single word and save it to a file
// =====================================================================
void synthesize_word_and_save(const char* word_name, const Diphone* diphones, int num_diphones) {
    int total_duration_samples = 0;
    for (int i = 0; i < num_diphones; i++) {
        total_duration_samples += (diphones[i].start_frames + diphones[i].transition_frames + diphones[i].end_frames) * (int)(SAMPLE_RATE * FRAME_PERIOD_S);
    }

    // Allocate buffer for the entire word
    double* audio_buffer = (double*)calloc(total_duration_samples, sizeof(double));
    if (!audio_buffer) {
        fprintf(stderr, "Error: Could not allocate audio buffer.\n");
        return;
    }

    // Synthesize the diphones into the buffer
    int current_sample = 0;
    for (int i = 0; i < num_diphones; i++) {
        synthesize_diphone(&diphones[i], audio_buffer, &current_sample);
    }
    
    // Normalize and write the buffer to a WAV file
    normalize_and_write_to_file(word_name, audio_buffer, total_duration_samples, SAMPLE_RATE);

    // Free the allocated buffer
    free(audio_buffer);
}

// =====================================================================
// Helper function to synthesize a phrase and save it to a single file
// =====================================================================
void synthesize_phrase_and_save(const char* filename, const Diphone** word_diphones, int* num_diphones, int num_words) {
    printf("synthesizing phrase and saving...\n");
       
    
    int total_duration_samples = 0;
    int pause_samples = SAMPLE_RATE / 4; // A quarter second pause

    // Calculate total duration
    for (int j = 0; j < num_words; j++) {
        for (int i = 0; i < num_diphones[j]; i++) {
            total_duration_samples += (word_diphones[j][i].start_frames + word_diphones[j][i].transition_frames + word_diphones[j][i].end_frames) * (int)(SAMPLE_RATE * FRAME_PERIOD_S);
        }
        if (j < num_words - 1) {
            total_duration_samples += pause_samples;
        }
    }

    // Allocate a single buffer for the entire phrase
    double* audio_buffer = (double*)calloc(total_duration_samples, sizeof(double));
    if (audio_buffer == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for audio buffer for '%s'.\n", filename);
        return;
    }

  // Reset the synthesis engine state 
    reset_synthesis_engine_state();
    
    int current_sample = 0;

    // Synthesize each word and add a pause
    for (int j = 0; j < num_words; j++) {
        for (int i = 0; i < num_diphones[j]; i++) {
            synthesize_diphone(&word_diphones[j][i], audio_buffer, &current_sample);
        }
        // Add a pause between words
        if (j < num_words - 1) {
            for (int k = 0; k < pause_samples; k++) {
                if (current_sample >= total_duration_samples) break;
                audio_buffer[current_sample++] = 0.0;
            }
        }
    }
    
    printf("Synthesis of phrase complete. Writing to %s.\n", filename);
    normalize_and_write_to_file(filename, audio_buffer, current_sample, SAMPLE_RATE);
    
    // Free the allocated memory
    free(audio_buffer);
}


