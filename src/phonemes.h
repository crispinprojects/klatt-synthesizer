/* phonemes.h
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
#ifndef PHONEMES_H
#define PHONEMES_H

#include <stdint.h>
#include <math.h>

// All the parameters for a single phoneme or frame
typedef struct {
    double F0;  // Fundamental frequency
    double F1;
    double B1;
    double F2;
    double B2;
    double F3;
    double B3;
    double F4;
    double B4;
    double F5;
    double B5;
    double F6;
    double B6;
    double FN;  // Nasal filter frequency
    double BN;  // Nasal filter bandwidth
    double AF;  // Voiced amplitude (relative to max)
    double AN;  // Unvoiced amplitude (relative to max)
} PhonemeParams;

//this is a better structure as we can display diphone names
//when constructing words
typedef struct {
    const char* name;
    const PhonemeParams *p1;//start phoneme
    const PhonemeParams *p2;//end phoneme
    int start_frames;
    int transition_frames;
    int end_frames;
} Diphone;

// =====================================================================================
// Diphone Definitions for Words
// =====================================================================================

//----------------------------------------------------------------------
// External declarations for words
extern const Diphone diphones_hello[];
extern const Diphone diphones_world[];
extern const Diphone diphones_happy[];
extern const Diphone diphones_birthday[];
// External declarations for the number of diphones
extern const int num_diphones_hello;
extern const int num_diphones_world;
extern const int num_diphones_happy;
extern const int num_diphones_birthday;


//---------------------------------------------------------------------
// External declarations for the day of the week diphone arrays
extern const Diphone diphones_monday[];
extern const Diphone diphones_tuesday[];
extern const Diphone diphones_wednesday[];
extern const Diphone diphones_thursday[];
extern const Diphone diphones_friday[];
extern const Diphone diphones_saturday[];
extern const Diphone diphones_sunday[];
// External declarations for the number of diphones in the days of the week

extern const int num_diphones_monday;
extern const int num_diphones_tuesday;
extern const int num_diphones_wednesday;
extern const int num_diphones_thursday;
extern const int num_diphones_friday;
extern const int num_diphones_saturday;
extern const int num_diphones_sunday;
//---------------------------------------------------------------------

// External declarations for months 
extern const Diphone diphones_january[];
extern const Diphone diphones_february[];
extern const Diphone diphones_march[];
extern const Diphone diphones_april[];
extern const Diphone diphones_may[];
extern const Diphone diphones_june[];
extern const Diphone diphones_july[];
extern const Diphone diphones_august[];
extern const Diphone diphones_september[];
extern const Diphone diphones_october[];
extern const Diphone diphones_november[];
extern const Diphone diphones_december[];

// External declarations for the number of diphones in the months
extern const int num_diphones_january;
extern const int num_diphones_february;
extern const int num_diphones_march;
extern const int num_diphones_april;
extern const int num_diphones_may;
extern const int num_diphones_june;
extern const int num_diphones_july;
extern const int num_diphones_august;
extern const int num_diphones_september;
extern const int num_diphones_october;
extern const int num_diphones_november;
extern const int num_diphones_december;

//----------------------------------------------------------------------

// External declarations for ordinal number diphone arrays
extern const Diphone diphones_first[];
extern const Diphone diphones_second[];
extern const Diphone diphones_third[];
extern const Diphone diphones_fourth[];
extern const Diphone diphones_fifth[];
extern const Diphone diphones_sixth[];
extern const Diphone diphones_seventh[];
extern const Diphone diphones_eighth[];
extern const Diphone diphones_ninth[];
extern const Diphone diphones_tenth[];
extern const Diphone diphones_eleventh[];
extern const Diphone diphones_twelfth[];
extern const Diphone diphones_thirteenth[];
extern const Diphone diphones_fourteenth[];
extern const Diphone diphones_fifteenth[];
extern const Diphone diphones_sixteenth[];
extern const Diphone diphones_seventeenth[];
extern const Diphone diphones_eighteenth[];
extern const Diphone diphones_nineteenth[];
extern const Diphone diphones_twentieth[];
extern const Diphone diphones_twentyfirst[];
extern const Diphone diphones_twentysecond[];
extern const Diphone diphones_twentythird[];
extern const Diphone diphones_twentyfourth[];
extern const Diphone diphones_twentyfifth[];
extern const Diphone diphones_twentysixth[];
extern const Diphone diphones_twentyseventh[];
extern const Diphone diphones_twentyeighth[];
extern const Diphone diphones_twentyninth[];
extern const Diphone diphones_thirtieth[];
extern const Diphone diphones_thirtyfirst[];

// External declarations for the number of diphones in the ordinal numbers
extern const int num_diphones_first;
extern const int num_diphones_second;
extern const int num_diphones_third;
extern const int num_diphones_fourth;
extern const int num_diphones_fifth;
extern const int num_diphones_sixth;
extern const int num_diphones_seventh;
extern const int num_diphones_eighth;
extern const int num_diphones_ninth;
extern const int num_diphones_tenth;
extern const int num_diphones_eleventh;
extern const int num_diphones_twelfth;
extern const int num_diphones_thirteenth;
extern const int num_diphones_fourteenth;
extern const int num_diphones_fifteenth;
extern const int num_diphones_sixteenth;
extern const int num_diphones_seventeenth;
extern const int num_diphones_eighteenth;
extern const int num_diphones_nineteenth;
extern const int num_diphones_twentieth;
extern const int num_diphones_twentyfirst;
extern const int num_diphones_twentysecond;
extern const int num_diphones_twentythird;
extern const int num_diphones_twentyfourth;
extern const int num_diphones_twentyfifth;
extern const int num_diphones_twentysixth;
extern const int num_diphones_twentyseventh;
extern const int num_diphones_twentyeighth;
extern const int num_diphones_twentyninth;
extern const int num_diphones_thirtieth;
extern const int num_diphones_thirtyfirst;

#endif // PHONEMES_H
