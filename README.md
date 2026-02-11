# Klatt Synthesizer

A Klatt speech synthesizer designed by Dennis Klatt in 1980 is a type a formant speech syntheiszer which replicates speech using [formants](https://www.youtube.com/watch?v=QS0iAyXWs5I). Formant synthesizers aim to model the vocal tract as a series of digital resonators (filters) shaping a sound from a noise source. This code repository has example code to show how I implemented a very simple Klatt sysnthesizer for speaking dates in the form:

```
<day of week> <ordinal number> <month>
```
This Klatt sythesizer code example is functional but unfortunately the speech quality is very poor especially compared to other formant synthesizers such as [espeak](https://espeak.sourceforge.net/) and more work is need to improve this.  However, it does provide a code example of a simple formant sythesizer which I have built from scratch which may be useful for educational purposes. The code has been developed as a Linux console application using C.

## Code

The project is composed of the following files: main.c, phonemes.h, phonemes.c, synthesizer.h,  synthesizer.c and a Makefile for compiling the project.

## phonemes.h and phonemes.c 

Two structures are defined in phonemes.h. The first structure called PhonemeParams  contains all the necessary parameters to define a phoneme's acoustic characteristics including formant frequencies, bandwidths, fundamental frequency, and amplitude parameters.

```
typedef struct {
    double F0;  /**< Fundamental frequency (pitch) in Hz */
    double F1;  /**< First formant frequency in Hz */
    double B1;  /**< First formant bandwidth in Hz */
    double F2;  /**< Second formant frequency in Hz */
    double B2;  /**< Second formant bandwidth in Hz */
    double F3;  /**< Third formant frequency in Hz */
    double B3;  /**< Third formant bandwidth in Hz */
    double F4;  /**< Fourth formant frequency in Hz */
    double B4;  /**< Fourth formant bandwidth in Hz */
    double F5;  /**< Fifth formant frequency in Hz */
    double B5;  /**< Fifth formant bandwidth in Hz */
    double F6;  /**< Sixth formant frequency in Hz */
    double B6;  /**< Sixth formant bandwidth in Hz */
    double FN;  /**< Nasal filter frequency in Hz */
    double BN;  /**< Nasal filter bandwidth in Hz */
    double AF;  /**< Voiced amplitude (relative to max) */
    double AN;  /**< Unvoiced amplitude (relative to max) */
} PhonemeParams;
```
The second structure is called Diphone represents the transition between two phonemes and includes the timing parameters for each stage of the transition.
```
typedef struct {
    const char* name;           /**< Name for debugging/clarity */
    const PhonemeParams *p1;    /**< Start phoneme */
    const PhonemeParams *p2;    /**< End phoneme */
    int start_frames;           /**< Number of frames in start phase */
    int transition_frames;      /**< Number of frames in transition phase */
    int end_frames;             /**< Number of frames in end phase */
} Diphone;
```
In phoneme.c the specific sound parameters (formant frequencies, bandwidth) are defined for each phoneme. An example is:
```
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
```
Each word is a sequence of diphones, which represent transitions between phonemes as defined in the Diphone structure. For example, the diphones for the word “hello” are shown below. 
```
const Diphone diphones_hello[] = {
    {"sil-h", &PHONEME_SILENCE, &PHONEME_H_FRICATIVE, 5, 10, 5},
    {"h-eh", &PHONEME_H_FRICATIVE, &PHONEME_EH_VOWEL, 5, 10, 5},
    {"eh-l", &PHONEME_EH_VOWEL, &PHONEME_L_LIQUID, 5, 10, 5},
    {"l-ow", &PHONEME_L_LIQUID, &PHONEME_OW_VOWEL, 5, 10, 5},
    {"ow-sil", &PHONEME_OW_VOWEL, &PHONEME_SILENCE, 5, 10, 5}
};
```
Each word is a sequence of diphones, which represent transitions between phonemes.  The diphone name e.g. “h-eh” is used is for debugging and clarity. The start_frames  transition_frames and end_frames parameters control the timing of each part of the sound.

## synthesizer.h and synthesizer.c

The code synthesizer.h and synthesizer.c is my attempt to implement a simple Klatt formant speech synthesiser. Formant speech synthesis takes noise as an input which is passed through a set of filters (resonators) to shape a sound. Klatt filters (resonators) can be configured in either a cascade or parallel configuration.

In synthesizer.h a structure called KlattFilter is defined as shown below.
```
typedef struct {
    double a1, a2;  	/**< First and second filter coefficients */
    double y1, y2;		/**< Previous output samples */
    double frequency;	/**< Filter center frequency in Hz */
    double gain; 		/**< Filter gain */
} KlattFilter;
```
This structure defines the state and coefficients for a second-order digital filter used in the Klatt speech synthesis model.

The core functions  in synthesizer.c are:

***initialize_filter()** which initialises a Klatt filter to a condition of inactivity. 

***update_filter_coefficients()*** which updates a Klatt filter's coefficients.

***generate_noise_source()*** to produce a wide frequency bandwidth non-periodic signal.

***generate_glottal_pulse_derivative()***  to simulate the sounds produced by the human vocal cords vibrating.

***process_filter()*** applies a Klatt filter to an input sample and returns the output.

***process_high_pass_filter()*** applies a high-pass filter  to an input sample to remove DC offset and returns the output.

***initialize_high_pass_filter()*** initialises the high-pass filter.

***cubic_interpolate_params***  takes two phoneme parameters and  applies cubic interpolation to produce new phoneme parameter. Cubic interpolation estimates the new value between two known phoneme parameter values by using a curve  and is said to be better to speech generation than linear interpolation.

***synthesize_frame()*** synthesizes a single frame (small segment of audio data) of speech. The core line of code is the weighted sum of the formants.
```
double out = process_filter(&f1, source) * 0.8;
out += process_filter(&f2, source) * 0.5;
out += process_filter(&f3, source) * 0.3;
out += process_filter(&f4, source) * 0.2;
out += process_filter(&f5, source) * 0.1;
```

***synthesize_diphone()***  Synthesizes a single diphone and adds the output to an audio buffer which is one of the function parameters ( double *audio). There are three stages.  Stage 1:  Synthesize frame of  initial phoneme (p1) of the diphone.  Stage 2: Synthesize frame  of the transition from p1 to p2 using the interpolate_params() function. Stage 3: Synthesize frame  of the end phoneme (p2).

***normalize_and_write_to_file () and  write_wav_header()*** functions  normalizes the audio buffer and writes it to a WAV file using the write_wav_header() function to write the WAV header. This allows the audio produced from the Klatt filter to be be saved and then played. 

## Source 

The source code is found in the src directory and is released with a GPL 3.0 license. It is being developed and tested using Debian 13 Trixie.

You need to install the build and  C compiler and make packages as shown below.

```
sudo apt-get update
sudo apt install build-essential
```

## Compile

Use the Makefile to compile. The target is "synthesizer"

```
make
./synthesizer
```

You should hear the  speech synthesizer saying the current date.

## Summary

The code has been developed from scratch and is not dependent on any other audio processing libraries and provides a working example of a formant speech synthesizer. It compiles and runs and reads out a date. Unfortunately the audio quality of the output very poor and the Klatt synthesizer sounds like a buzzing robot. Maybe audio quality would be improved using pitch contours (trying to make F0 of the first syllable slightly higher than the last) and using amplitude envelopes to make  stressed syllables slightly louder than the unstressed ones.

The Klatt synthesizer simulates the human vocal cords  and throat. It is extremely sensitive to small errors and  a tiny mismatch in a filter can turn a voice into a screeching noise. An alternative approach is to concatenate recorded diphones effectively stitching together small pieces of real recordings to create word. My [diphone talker](https://github.com/crispinprojects/diphone-talker) project took this approach but the joins between the diphone recording often sounded jumpy and voice prosody needed further work.

Now that computers and server have more memory word sampling synthesizers are now being used. The goal is to store recordings of actual word and play them back in sequence to say a phrase. Voice prosody, emotion and clarity can all be preserved. However, I have found you need to use heavy compression to keep the digitisation and storage of words as small as possible. One technique that is used for doing this is ADPCM (Adaptive Differential Pulse Code Modulation). I now use a simple ADPCM synthesizer for my [Talk Calendar](https://github.com/crispinprojects/talkcalendar) project. Since Talk Calendar only uses a few hundred specific words "limited vocabulary"  this approach is a manageable design choice.

## Author

* **Alan Crispin** [Github](https://github.com/crispinprojects)

## Project Status

Under development.

## Acknowledgements

* [Debian](https://www.debian.org/)
* [Formants](https://www.youtube.com/watch?v=QS0iAyXWs5I). If you plot amplitude verses frequency of a typical speaker then formants are the resonance points or spectral peaks in the spectral envelop. They are the harmonics that are accentuated more than the other frequencies. Formant is a word derived from the Latin formare, meaning "to shape" in this case the sounds of vocal track.
* [Peter Millers](https://en.wikipedia.org/wiki/Peter_Miller_(software_engineer)) Recite project defines Klatt parameters
* Klatt Cascade-Parallel Formant Speech Synthesizer developed by Reece H. Dunn and found [here on github](https://github.com/rhdunn/klatt).
