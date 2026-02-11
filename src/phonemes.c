/* phonemes.c
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
// Phoneme Parameter Definitions
// A phoneme's sound is defined by its formant frequencies (F1-F6), 
// bandwidths (B1-B6),fundamental frequency (F0), and 
// amplitudes (AF for voiced, AN for unvoiced).
// Correct Phoneme parameters is CRITICAL for success of synthesizer
// These values are based on the Klatt synthesizer model.
// =====================================================================

#include "phonemes.h"
#include <stdint.h>
#include <math.h>

const PhonemeParams PHONEME_SILENCE = {
    .F0 = 0.0, .AF = 0.0, .AN = 0.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 0.0, .B2 = 0.0,
    .F3 = 0.0, .B3 = 0.0,
    .F4 = 0.0, .B4 = 0.0,
    .F5 = 0.0, .B5 = 0.0,
    .F6 = 0.0, .B6 = 0.0,
    .FN = 0.0, .BN = 0.0,
};

//----------------------------------------------------------------------

const PhonemeParams PHONEME_K_BURST = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 100,
    .F3 = 3000, .B3 = 100,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_AE_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 700, .B1 = 50,
    .F2 = 1400, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_T_BURST = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 100,
    .F3 = 3000, .B3 = 100,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_H_FRICATIVE = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 100,
    .F3 = 3000, .B3 = 100,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_EH_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 500, .B1 = 50,
    .F2 = 1600, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_L_LIQUID = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 300, .B1 = 100,
    .F2 = 1200, .B2 = 150,
    .F3 = 2500, .B3 = 200,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};


//----------------------------------------------------------------------

const PhonemeParams PHONEME_OW_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 400, .B1 = 50,
    .F2 = 800, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_AA_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 750, .B1 = 50,
    .F2 = 1100, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_W_GLIDE = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 300, .B1 = 50,
    .F2 = 800, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------
const PhonemeParams PHONEME_S_FRICATIVE = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 200,
    .F3 = 3500, .B3 = 200,
    .F4 = 4000, .B4 = 300,
    .F5 = 4500, .B5 = 300,
    .F6 = 5000, .B6 = 300,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_D_BURST = {
    .F0 = 120, .AF = 1.0, .AN = 0.5,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 100,
    .F3 = 3000, .B3 = 100,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_EY_VOWEL = {
    .F0 = 120.0, .AF = 1.0, .AN = 0.0,
    .F1 = 400, .B1 = 80,
    .F2 = 2200, .B2 = 100,
    .F3 = 2800, .B3 = 150,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5000, .B6 = 200,
    .FN = 0.0, .BN = 0.0,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_R_LIQUID = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 300, .B1 = 50,
    .F2 = 1200, .B2 = 80,
    .F3 = 2000, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_IY_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 250, .B1 = 50,
    .F2 = 2200, .B2 = 80,
    .F3 = 2900, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------
const PhonemeParams PHONEME_TH_FRICATIVE = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2000, .B2 = 200,
    .F3 = 3000, .B3 = 200,
    .F4 = 4000, .B4 = 300,
    .F5 = 5000, .B5 = 300,
    .F6 = 6000, .B6 = 300,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_N_NASAL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 300, .B1 = 50,
    .F2 = 1200, .B2 = 80,
    .F3 = 2500, .B3 = 120,
    .F4 = 3500, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------
const PhonemeParams PHONEME_V_FRICATIVE = {
    .F0 = 120, .AF = 1.0, .AN = 0.5,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 200,
    .F3 = 3500, .B3 = 200,
    .F4 = 4000, .B4 = 300,
    .F5 = 4500, .B5 = 300,
    .F6 = 5000, .B6 = 300,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_G_BURST = {
    .F0 = 120, .AF = 1.0, .AN = 0.5,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2000, .B2 = 100,
    .F3 = 2500, .B3 = 100,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------

const PhonemeParams PHONEME_AX_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 500, .B1 = 50,
    .F2 = 1200, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------

const PhonemeParams PHONEME_AY_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 700, .B1 = 50,
    .F2 = 1200, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------

const PhonemeParams PHONEME_IH_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 400, .B1 = 50,
    .F2 = 1800, .B2 = 80,
    .F3 = 2600, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_P_BURST = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 100,
    .F3 = 3000, .B3 = 100,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------
const PhonemeParams PHONEME_Z_FRICATIVE = {
    .F0 = 120, .AF = 1.0, .AN = 0.5,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 200,
    .F3 = 3500, .B3 = 200,
    .F4 = 4000, .B4 = 300,
    .F5 = 4500, .B5 = 300,
    .F6 = 5000, .B6 = 300,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_F_FRICATIVE = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 3000, .B2 = 200,
    .F3 = 3500, .B3 = 200,
    .F4 = 4000, .B4 = 300,
    .F5 = 4500, .B5 = 300,
    .F6 = 5000, .B6 = 300,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_ER_VOWEL = {
    .F0 = 120.0, .AF = 1.0, .AN = 0.0,
    .F1 = 400, .B1 = 80,
    .F2 = 1400, .B2 = 100,
    .F3 = 1800, .B3 = 150,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5000, .B6 = 200,
    .FN = 0.0, .BN = 0.0,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_B_BURST = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 1200, .B2 = 100,
    .F3 = 2000, .B3 = 100,
    .F4 = 3000, .B4 = 100,
    .F5 = 4000, .B5 = 100,
    .F6 = 4500, .B6 = 100,
    .FN = 0.0, .BN = 0.0,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_R_VOWEL = {
    .F0 = 120.0, .AF = 1.0, .AN = 0.0,
    .F1 = 400, .B1 = 80,
    .F2 = 1200, .B2 = 150,
    .F3 = 1500, .B3 = 200,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5000, .B6 = 200,
    .FN = 0.0, .BN = 0.0,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_UH_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 500, .B1 = 50,
    .F2 = 1100, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_T_PUNCTUAL = {
    .F0 = 0.0, .AF = 0.0, .AN = 1.0,
    .F1 = 0.0, .B1 = 0.0,
    .F2 = 2500, .B2 = 100,
    .F3 = 3000, .B3 = 100,
    .F4 = 3500, .B4 = 200,
    .F5 = 4500, .B5 = 200,
    .F6 = 5500, .B6 = 200,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------

const PhonemeParams PHONEME_AO_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 500, .B1 = 50,
    .F2 = 900, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};

//----------------------------------------------------------------------

const PhonemeParams PHONEME_M_NASAL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 300, .B1 = 50,
    .F2 = 1200, .B2 = 80,
    .F3 = 2500, .B3 = 120,
    .F4 = 3500, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------


const PhonemeParams PHONEME_AH_VOWEL = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 700, .B1 = 50,
    .F2 = 1200, .B2 = 80,
    .F3 = 2400, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------
const PhonemeParams PHONEME_YU_GLIDE = {
    .F0 = 120, .AF = 1.0, .AN = 0.0,
    .F1 = 300, .B1 = 50,
    .F2 = 1800, .B2 = 80,
    .F3 = 2500, .B3 = 120,
    .F4 = 3300, .B4 = 150,
    .F5 = 3900, .B5 = 200,
    .F6 = 4500, .B6 = 250,
    .FN = 250, .BN = 100,
};
//----------------------------------------------------------------------


// =====================================================================================
// Diphone Definitions for Words
// Each word is a sequence of diphones, which represent transitions between phonemes.
// The `name` is for debugging/clarity, and the `start_frames`, `transition_frames`,
// and `end_frames` control the timing of each part of the sound.
// =====================================================================================

const Diphone diphones_hello[] = {
    //{"sil-h", &PHONEME_SILENCE, &PHONEME_H_FRICATIVE, 5, 10, 5},
    {"h-eh", &PHONEME_H_FRICATIVE, &PHONEME_EH_VOWEL, 5, 10, 5},
    {"eh-l", &PHONEME_EH_VOWEL, &PHONEME_L_LIQUID, 5, 10, 5},
    {"l-ow", &PHONEME_L_LIQUID, &PHONEME_OW_VOWEL, 5, 10, 5},
    {"ow-sil", &PHONEME_OW_VOWEL, &PHONEME_SILENCE, 5, 10, 5}
};
const int num_diphones_hello = sizeof(diphones_hello) / sizeof(Diphone);

// diphones for world
const Diphone diphones_world[] = {
    {"w-er", &PHONEME_W_GLIDE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-l", &PHONEME_ER_VOWEL, &PHONEME_L_LIQUID, 10, 5, 10},
    {"l-d", &PHONEME_L_LIQUID, &PHONEME_D_BURST, 10, 5, 10},
    {"d-sil", &PHONEME_D_BURST, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_world = sizeof(diphones_world) / sizeof(Diphone);


//diphones for happy
const Diphone diphones_happy[] = {
    {"h-ae", &PHONEME_H_FRICATIVE, &PHONEME_AE_VOWEL, 10, 5, 10},
    {"ae-p", &PHONEME_AE_VOWEL, &PHONEME_P_BURST, 10, 5, 10},
    {"p-iy", &PHONEME_P_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-sil", &PHONEME_IY_VOWEL, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_happy = sizeof(diphones_happy) / sizeof(Diphone);

//diphones for birthday
const Diphone diphones_birthday[] = {
    {"b-ih", &PHONEME_K_BURST, &PHONEME_IH_VOWEL, 10, 5, 10}, //b-ih
    {"ih-r", &PHONEME_IH_VOWEL, &PHONEME_R_LIQUID, 10, 5, 10}, //ih-r
    {"r-th", &PHONEME_R_LIQUID, &PHONEME_TH_FRICATIVE, 10, 5, 10}, //r-th
    {"th-d", &PHONEME_TH_FRICATIVE, &PHONEME_D_BURST, 10, 5, 10}, //th-d
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10}, //d-eh
    {"eh-ay", &PHONEME_EH_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10}, //eh-ay
    {"ay-sil", &PHONEME_AY_VOWEL, &PHONEME_SILENCE, 10, 5, 10}, //ay-sil
};
const int num_diphones_birthday = sizeof(diphones_birthday) / sizeof(Diphone);

//----------------------------------------------------------------------
//days of week
//----------------------------------------------------------------------
const Diphone diphones_monday[] = {
    {"m-ah", &PHONEME_M_NASAL, &PHONEME_AH_VOWEL, 10, 5, 10},
    {"ah-n", &PHONEME_AH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-d", &PHONEME_N_NASAL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-y", &PHONEME_EH_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10},
};
const int num_diphones_monday = sizeof(diphones_monday) / sizeof(Diphone);

const Diphone diphones_tuesday[] = {
    {"t-yu", &PHONEME_T_BURST, &PHONEME_YU_GLIDE, 10, 5, 10},
    {"yu-z", &PHONEME_YU_GLIDE, &PHONEME_Z_FRICATIVE, 10, 5, 10},
    {"z-d", &PHONEME_Z_FRICATIVE, &PHONEME_D_BURST, 10, 5, 10},
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-y", &PHONEME_EH_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10},
};
const int num_diphones_tuesday = sizeof(diphones_tuesday) / sizeof(Diphone);

const Diphone diphones_wednesday[] = {
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-z", &PHONEME_N_NASAL, &PHONEME_Z_FRICATIVE, 10, 5, 10},
    {"z-d", &PHONEME_Z_FRICATIVE, &PHONEME_D_BURST, 10, 5, 10},
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-y", &PHONEME_EH_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10},
};
const int num_diphones_wednesday = sizeof(diphones_wednesday) / sizeof(Diphone);

const Diphone diphones_thursday[] = {
    {"th-er", &PHONEME_TH_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-z", &PHONEME_ER_VOWEL, &PHONEME_Z_FRICATIVE, 10, 5, 10},
    {"z-d", &PHONEME_Z_FRICATIVE, &PHONEME_D_BURST, 10, 5, 10},
    {"d-ae", &PHONEME_D_BURST, &PHONEME_AE_VOWEL, 10, 5, 10},
    {"ae-y", &PHONEME_AE_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10}, // This is wrong, need a glide
    {"y-sil", &PHONEME_AY_VOWEL, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_thursday = sizeof(diphones_thursday) / sizeof(Diphone);

const Diphone diphones_friday[] = {
    {"f-r", &PHONEME_F_FRICATIVE, &PHONEME_R_LIQUID, 10, 5, 10},
    {"r-ay", &PHONEME_R_LIQUID, &PHONEME_AY_VOWEL, 10, 5, 10},
    {"ay-d", &PHONEME_AY_VOWEL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-y", &PHONEME_EH_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10},
};
const int num_diphones_friday = sizeof(diphones_friday) / sizeof(Diphone);

const Diphone diphones_saturday[] = {
    {"s-ae", &PHONEME_S_FRICATIVE, &PHONEME_AE_VOWEL, 10, 5, 10},
    {"ae-t", &PHONEME_AE_VOWEL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-er", &PHONEME_T_BURST, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-d", &PHONEME_ER_VOWEL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-y", &PHONEME_EH_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10},
};
const int num_diphones_saturday = sizeof(diphones_saturday) / sizeof(Diphone);

const Diphone diphones_sunday[] = {
    {"s-ah", &PHONEME_S_FRICATIVE, &PHONEME_AH_VOWEL, 10, 5, 10},
    {"ah-n", &PHONEME_AH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-d", &PHONEME_N_NASAL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-y", &PHONEME_EH_VOWEL, &PHONEME_AY_VOWEL, 10, 5, 10},
};
const int num_diphones_sunday = sizeof(diphones_sunday) / sizeof(Diphone);


//----------------------------------------------------------------------
//months
//----------------------------------------------------------------------
const Diphone diphones_january[] = {
    {"j-ah", &PHONEME_D_BURST, &PHONEME_AH_VOWEL, 10, 5, 10},
    {"ah-n", &PHONEME_AH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-yu", &PHONEME_N_NASAL, &PHONEME_YU_GLIDE, 10, 5, 10},
    {"yu-eh", &PHONEME_YU_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-r", &PHONEME_EH_VOWEL, &PHONEME_R_LIQUID, 10, 5, 10},
    {"r-iy", &PHONEME_R_LIQUID, &PHONEME_IY_VOWEL, 10, 5, 10}
};
const int num_diphones_january = sizeof(diphones_january) / sizeof(Diphone);

const Diphone diphones_february[] = {
    {"f-eh", &PHONEME_F_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-b", &PHONEME_EH_VOWEL, &PHONEME_D_BURST, 10, 5, 10}, // No 'b' phoneme, so using 'd' for now.
    {"b-r", &PHONEME_D_BURST, &PHONEME_R_LIQUID, 10, 5, 10},
    {"r-uw", &PHONEME_R_LIQUID, &PHONEME_W_GLIDE, 10, 5, 10}, // No 'uw' vowel, using a glide
    {"uw-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-r", &PHONEME_EH_VOWEL, &PHONEME_R_LIQUID, 10, 5, 10},
    {"r-iy", &PHONEME_R_LIQUID, &PHONEME_IY_VOWEL, 10, 5, 10}
};
const int num_diphones_february = sizeof(diphones_february) / sizeof(Diphone);

const Diphone diphones_march[] = {
    {"m-aa", &PHONEME_M_NASAL, &PHONEME_AA_VOWEL, 10, 5, 10},
    {"aa-r", &PHONEME_AA_VOWEL, &PHONEME_R_LIQUID, 10, 5, 10},
    {"r-ch", &PHONEME_R_LIQUID, &PHONEME_T_BURST, 10, 5, 10} // No 'ch' phoneme, using a cluster
};
const int num_diphones_march = sizeof(diphones_march) / sizeof(Diphone);

const Diphone diphones_april[] = {
    {"ey-p", &PHONEME_AY_VOWEL, &PHONEME_P_BURST, 10, 5, 10},
    {"p-r", &PHONEME_P_BURST, &PHONEME_R_LIQUID, 10, 5, 10},
    {"r-ih", &PHONEME_R_LIQUID, &PHONEME_IH_VOWEL, 10, 5, 10},
    {"ih-l", &PHONEME_IH_VOWEL, &PHONEME_L_LIQUID, 10, 5, 10}
};
const int num_diphones_april = sizeof(diphones_april) / sizeof(Diphone);

const Diphone diphones_may[] = {
    {"m-ey", &PHONEME_M_NASAL, &PHONEME_AY_VOWEL, 10, 5, 10}
};
const int num_diphones_may = sizeof(diphones_may) / sizeof(Diphone);

const Diphone diphones_june[] = {
    {"j-uw", &PHONEME_D_BURST, &PHONEME_W_GLIDE, 10, 5, 10}, // No 'uw' vowel
    {"uw-n", &PHONEME_W_GLIDE, &PHONEME_N_NASAL, 10, 5, 10}
};
const int num_diphones_june = sizeof(diphones_june) / sizeof(Diphone);

const Diphone diphones_july[] = {
    {"j-uh", &PHONEME_D_BURST, &PHONEME_UH_VOWEL, 10, 5, 10},
    {"uh-l", &PHONEME_UH_VOWEL, &PHONEME_L_LIQUID, 10, 5, 10},
    {"l-ay", &PHONEME_L_LIQUID, &PHONEME_AY_VOWEL, 10, 5, 10}
};
const int num_diphones_july = sizeof(diphones_july) / sizeof(Diphone);

const Diphone diphones_august[] = {
    {"aa-w", &PHONEME_AA_VOWEL, &PHONEME_W_GLIDE, 3, 2, 3},
    {"w-g", &PHONEME_W_GLIDE, &PHONEME_G_BURST, 3, 2, 3},
    {"g-uh", &PHONEME_G_BURST, &PHONEME_UH_VOWEL, 3, 2, 3},
    {"uh-s", &PHONEME_UH_VOWEL, &PHONEME_S_FRICATIVE, 3, 2, 3},
    {"s-t", &PHONEME_S_FRICATIVE, &PHONEME_T_PUNCTUAL, 3, 2, 3},
};
const int num_diphones_august = sizeof(diphones_august) / sizeof(Diphone);


const Diphone diphones_september[] = {
    {"s-eh", &PHONEME_S_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-p", &PHONEME_EH_VOWEL, &PHONEME_P_BURST, 10, 5, 10},
    {"p-t", &PHONEME_P_BURST, &PHONEME_T_BURST, 10, 5, 10},
    {"t-eh", &PHONEME_T_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-m", &PHONEME_EH_VOWEL, &PHONEME_M_NASAL, 10, 5, 10},
    {"m-b", &PHONEME_M_NASAL, &PHONEME_D_BURST, 10, 5, 10},
    {"b-er", &PHONEME_D_BURST, &PHONEME_ER_VOWEL, 10, 5, 10}
};
const int num_diphones_september = sizeof(diphones_september) / sizeof(Diphone);

const Diphone diphones_october[] = {
    {"aa-k", &PHONEME_AA_VOWEL, &PHONEME_K_BURST, 10, 5, 10},
    {"k-t", &PHONEME_K_BURST, &PHONEME_T_BURST, 10, 5, 10},
    {"t-ow", &PHONEME_T_BURST, &PHONEME_OW_VOWEL, 10, 5, 10},
    {"ow-b", &PHONEME_OW_VOWEL, &PHONEME_D_BURST, 10, 5, 10},
    {"b-er", &PHONEME_D_BURST, &PHONEME_ER_VOWEL, 10, 5, 10}
};
const int num_diphones_october = sizeof(diphones_october) / sizeof(Diphone);

const Diphone diphones_november[] = {
    {"n-ow", &PHONEME_N_NASAL, &PHONEME_OW_VOWEL, 10, 5, 10},
    {"ow-v", &PHONEME_OW_VOWEL, &PHONEME_V_FRICATIVE, 10, 5, 10},
    {"v-eh", &PHONEME_V_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-m", &PHONEME_EH_VOWEL, &PHONEME_M_NASAL, 10, 5, 10},
    {"m-b", &PHONEME_M_NASAL, &PHONEME_D_BURST, 10, 5, 10},
    {"b-er", &PHONEME_D_BURST, &PHONEME_ER_VOWEL, 10, 5, 10}
};
const int num_diphones_november = sizeof(diphones_november) / sizeof(Diphone);

const Diphone diphones_december[] = {
    {"d-eh", &PHONEME_D_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-s", &PHONEME_EH_VOWEL, &PHONEME_Z_FRICATIVE, 10, 5, 10},
    {"s-eh", &PHONEME_S_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-m", &PHONEME_EH_VOWEL, &PHONEME_M_NASAL, 10, 5, 10},
    {"m-b", &PHONEME_M_NASAL, &PHONEME_D_BURST, 10, 5, 10},
    {"b-er", &PHONEME_D_BURST, &PHONEME_ER_VOWEL, 10, 5, 10}
};
const int num_diphones_december = sizeof(diphones_december) / sizeof(Diphone);

//----------------------------------------------------------------------
//ordinals 1st to 31st
//----------------------------------------------------------------------
const Diphone diphones_first[] = {
    {"f-er", &PHONEME_F_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-s", &PHONEME_ER_VOWEL, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-t", &PHONEME_S_FRICATIVE, &PHONEME_T_BURST, 10, 5, 10},
    {"t-sil", &PHONEME_T_BURST, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_first = sizeof(diphones_first) / sizeof(Diphone);

const Diphone diphones_second[] = {
    {"s-eh", &PHONEME_S_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-k", &PHONEME_EH_VOWEL, &PHONEME_K_BURST, 10, 5, 10},
    {"k-ah", &PHONEME_K_BURST, &PHONEME_AH_VOWEL, 10, 5, 10},
    {"ah-n", &PHONEME_AH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-d", &PHONEME_N_NASAL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-sil", &PHONEME_D_BURST, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_second = sizeof(diphones_second) / sizeof(Diphone);

const Diphone diphones_third[] = {
    {"th-er", &PHONEME_TH_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-d", &PHONEME_ER_VOWEL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-sil", &PHONEME_D_BURST, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_third = sizeof(diphones_third) / sizeof(Diphone);

const Diphone diphones_fourth[] = {
    {"f-ao", &PHONEME_F_FRICATIVE, &PHONEME_AO_VOWEL, 10, 5, 10},
    {"ao-r", &PHONEME_AO_VOWEL, &PHONEME_R_LIQUID, 10, 5, 10},
    {"r-th", &PHONEME_R_LIQUID, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_fourth = sizeof(diphones_fourth) / sizeof(Diphone);

const Diphone diphones_fifth[] = {
    {"f-ih", &PHONEME_F_FRICATIVE, &PHONEME_IH_VOWEL, 10, 5, 10},
    {"ih-f", &PHONEME_IH_VOWEL, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-th", &PHONEME_F_FRICATIVE, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_fifth = sizeof(diphones_fifth) / sizeof(Diphone);

const Diphone diphones_sixth[] = {
    {"s-ih", &PHONEME_S_FRICATIVE, &PHONEME_IH_VOWEL, 10, 5, 10},
    {"ih-k", &PHONEME_IH_VOWEL, &PHONEME_K_BURST, 10, 5, 10},
    {"k-s", &PHONEME_K_BURST, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-th", &PHONEME_S_FRICATIVE, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_sixth = sizeof(diphones_sixth) / sizeof(Diphone);

const Diphone diphones_seventh[] = {
    {"s-eh", &PHONEME_S_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-v", &PHONEME_EH_VOWEL, &PHONEME_V_FRICATIVE, 10, 5, 10},
    {"v-eh", &PHONEME_V_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_seventh = sizeof(diphones_seventh) / sizeof(Diphone);

const Diphone diphones_eighth[] = {
    {"ey-t", &PHONEME_AY_VOWEL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-th", &PHONEME_T_BURST, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_eighth = sizeof(diphones_eighth) / sizeof(Diphone);

const Diphone diphones_ninth[] = {
    {"n-ay", &PHONEME_N_NASAL, &PHONEME_AY_VOWEL, 10, 5, 10},
    {"ay-n", &PHONEME_AY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_ninth = sizeof(diphones_ninth) / sizeof(Diphone);

const Diphone diphones_tenth[] = {
    {"t-eh", &PHONEME_T_BURST, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_tenth = sizeof(diphones_tenth) / sizeof(Diphone);

const Diphone diphones_eleventh[] = {
    {"eh-l", &PHONEME_EH_VOWEL, &PHONEME_L_LIQUID, 10, 5, 10},
    {"l-eh", &PHONEME_L_LIQUID, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-v", &PHONEME_EH_VOWEL, &PHONEME_V_FRICATIVE, 10, 5, 10},
    {"v-eh", &PHONEME_V_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_eleventh = sizeof(diphones_eleventh) / sizeof(Diphone);

const Diphone diphones_twelfth[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-l", &PHONEME_EH_VOWEL, &PHONEME_L_LIQUID, 10, 5, 10},
    {"l-f", &PHONEME_L_LIQUID, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-th", &PHONEME_F_FRICATIVE, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_twelfth = sizeof(diphones_twelfth) / sizeof(Diphone);

const Diphone diphones_thirteenth[] = {
    {"th-er", &PHONEME_TH_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-t", &PHONEME_ER_VOWEL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
};
const int num_diphones_thirteenth = sizeof(diphones_thirteenth) / sizeof(Diphone);

// Diphones for "fourteenth"
const Diphone diphones_fourteenth[] = {
    {"f-or", &PHONEME_F_FRICATIVE, &PHONEME_R_LIQUID, 10, 5, 10},
    {"or-t", &PHONEME_R_LIQUID, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10},
    {"sil-sil", &PHONEME_SILENCE, &PHONEME_SILENCE, 10, 0, 0,}
};
const int num_diphones_fourteenth = sizeof(diphones_fourteenth) / sizeof(Diphone);

// Diphones for "fifteenth"
const Diphone diphones_fifteenth[] = {
    {"f-ih", &PHONEME_F_FRICATIVE, &PHONEME_IH_VOWEL, 10, 5, 10},
    {"ih-f", &PHONEME_IH_VOWEL, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-t", &PHONEME_F_FRICATIVE, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_fifteenth = sizeof(diphones_fifteenth) / sizeof(Diphone);

// Diphones for "sixteenth"
const Diphone diphones_sixteenth[] = {
    {"s-ih", &PHONEME_S_FRICATIVE, &PHONEME_IH_VOWEL, 10, 5, 10},
    {"ih-k", &PHONEME_IH_VOWEL, &PHONEME_K_BURST, 10, 5, 10},
    {"k-s", &PHONEME_K_BURST, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-t", &PHONEME_S_FRICATIVE, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_sixteenth = sizeof(diphones_sixteenth) / sizeof(Diphone);

// Diphones for "seventeenth"
const Diphone diphones_seventeenth[] = {
    {"s-eh", &PHONEME_S_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-v", &PHONEME_EH_VOWEL, &PHONEME_V_FRICATIVE, 10, 5, 10},
    {"v-eh", &PHONEME_V_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_seventeenth = sizeof(diphones_seventeenth) / sizeof(Diphone);

// Diphones for "eighteenth"
const Diphone diphones_eighteenth[] = {
    {"ey-t", &PHONEME_EY_VOWEL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_eighteenth = sizeof(diphones_eighteenth) / sizeof(Diphone);

// Diphones for "nineteenth"
const Diphone diphones_nineteenth[] = {
    {"n-ay", &PHONEME_N_NASAL, &PHONEME_AY_VOWEL, 10, 5, 10},
    {"ay-n", &PHONEME_AY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_nineteenth = sizeof(diphones_nineteenth) / sizeof(Diphone);

// Diphones for "twentieth"
const Diphone diphones_twentieth[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-th", &PHONEME_IY_VOWEL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentieth = sizeof(diphones_twentieth) / sizeof(Diphone);

// Diphones for "twentyfirst"
const Diphone diphones_twentyfirst[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-f", &PHONEME_IY_VOWEL, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-er", &PHONEME_F_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-s", &PHONEME_ER_VOWEL, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-t", &PHONEME_S_FRICATIVE, &PHONEME_T_BURST, 10, 5, 10},
    {"t-sil", &PHONEME_T_BURST, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentyfirst = sizeof(diphones_twentyfirst) / sizeof(Diphone);

// Diphones for "twentysecond"
const Diphone diphones_twentysecond[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-s", &PHONEME_IY_VOWEL, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-eh", &PHONEME_S_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-k", &PHONEME_EH_VOWEL, &PHONEME_K_BURST, 10, 5, 10},
    {"k-ah", &PHONEME_K_BURST, &PHONEME_AX_VOWEL, 10, 5, 10},
    {"ah-n", &PHONEME_AX_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-d", &PHONEME_N_NASAL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-sil", &PHONEME_D_BURST, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentysecond = sizeof(diphones_twentysecond) / sizeof(Diphone);

// Diphones for "twentythird"
const Diphone diphones_twentythird[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-th", &PHONEME_IY_VOWEL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-er", &PHONEME_TH_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-d", &PHONEME_ER_VOWEL, &PHONEME_D_BURST, 10, 5, 10},
    {"d-sil", &PHONEME_D_BURST, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentythird = sizeof(diphones_twentythird) / sizeof(Diphone);

// Diphones for "twentyfourth"
const Diphone diphones_twentyfourth[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-f", &PHONEME_IY_VOWEL, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-or", &PHONEME_F_FRICATIVE, &PHONEME_R_LIQUID, 10, 5, 10},
    {"or-th", &PHONEME_R_LIQUID, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentyfourth = sizeof(diphones_twentyfourth) / sizeof(Diphone);

// Diphones for "twentyfifth"
const Diphone diphones_twentyfifth[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-f", &PHONEME_IY_VOWEL, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-ih", &PHONEME_F_FRICATIVE, &PHONEME_IH_VOWEL, 10, 5, 10},
    {"ih-f", &PHONEME_IH_VOWEL, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-th", &PHONEME_F_FRICATIVE, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentyfifth = sizeof(diphones_twentyfifth) / sizeof(Diphone);

// Diphones for "twentysixth"
const Diphone diphones_twentysixth[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-s", &PHONEME_IY_VOWEL, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-ih", &PHONEME_S_FRICATIVE, &PHONEME_IH_VOWEL, 10, 5, 10},
    {"ih-k", &PHONEME_IH_VOWEL, &PHONEME_K_BURST, 10, 5, 10},
    {"k-s", &PHONEME_K_BURST, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-th", &PHONEME_S_FRICATIVE, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentysixth = sizeof(diphones_twentysixth) / sizeof(Diphone);

// Diphones for "twentyseventh"
const Diphone diphones_twentyseventh[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-s", &PHONEME_IY_VOWEL, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-eh", &PHONEME_S_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-v", &PHONEME_EH_VOWEL, &PHONEME_V_FRICATIVE, 10, 5, 10},
    {"v-eh", &PHONEME_V_FRICATIVE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentyseventh = sizeof(diphones_twentyseventh) / sizeof(Diphone);

// Diphones for "twentyeighth"
const Diphone diphones_twentyeighth[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-ey", &PHONEME_IY_VOWEL, &PHONEME_EY_VOWEL, 10, 5, 10},
    {"ey-t", &PHONEME_EY_VOWEL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-th", &PHONEME_T_BURST, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentyeighth = sizeof(diphones_twentyeighth) / sizeof(Diphone);

// Diphones for "twentyninth"
const Diphone diphones_twentyninth[] = {
    {"t-w", &PHONEME_T_BURST, &PHONEME_W_GLIDE, 10, 5, 10},
    {"w-eh", &PHONEME_W_GLIDE, &PHONEME_EH_VOWEL, 10, 5, 10},
    {"eh-n", &PHONEME_EH_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-t", &PHONEME_N_NASAL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-n", &PHONEME_IY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-ay", &PHONEME_N_NASAL, &PHONEME_AY_VOWEL, 10, 5, 10},
    {"ay-n", &PHONEME_AY_VOWEL, &PHONEME_N_NASAL, 10, 5, 10},
    {"n-th", &PHONEME_N_NASAL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_twentyninth = sizeof(diphones_twentyninth) / sizeof(Diphone);

// Diphones for "thirtieth"
const Diphone diphones_thirtieth[] = {
    {"th-er", &PHONEME_TH_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-t", &PHONEME_ER_VOWEL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-th", &PHONEME_IY_VOWEL, &PHONEME_TH_FRICATIVE, 10, 5, 10},
    {"th-sil", &PHONEME_TH_FRICATIVE, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_thirtieth = sizeof(diphones_thirtieth) / sizeof(Diphone);

// Diphones for "thirtyfirst"
const Diphone diphones_thirtyfirst[] = {
    {"th-er", &PHONEME_TH_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-t", &PHONEME_ER_VOWEL, &PHONEME_T_BURST, 10, 5, 10},
    {"t-iy", &PHONEME_T_BURST, &PHONEME_IY_VOWEL, 10, 5, 10},
    {"iy-f", &PHONEME_IY_VOWEL, &PHONEME_F_FRICATIVE, 10, 5, 10},
    {"f-er", &PHONEME_F_FRICATIVE, &PHONEME_ER_VOWEL, 10, 5, 10},
    {"er-s", &PHONEME_ER_VOWEL, &PHONEME_S_FRICATIVE, 10, 5, 10},
    {"s-t", &PHONEME_S_FRICATIVE, &PHONEME_T_BURST, 10, 5, 10},
    {"t-sil", &PHONEME_T_BURST, &PHONEME_SILENCE, 10, 5, 10}
};
const int num_diphones_thirtyfirst = sizeof(diphones_thirtyfirst) / sizeof(Diphone);
