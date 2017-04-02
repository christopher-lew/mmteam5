/**
 * Creates a buzzer class using a PwmOut object.
 * Includes private pause() and play() functions that can be used
 * together to create songs in the form of public functions.
 */

/*
 * NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
 * THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
 * (Ab IS CALLED Ab AND NOT LAb)
 *
 * JAVIER: Notes were defined in frequencies so I added a 1/freq to pass them in as period values.
 * Since the scale of harmonies starts at C,Db,D, I kept this first series as 0, and scaled
 * everything else up by 1. (i.e. Ab0,LA0,Bb0,B0 --> Ab1, LA1, Bb1, B1)
 */

#ifndef BUZZER_H
#define BUZZER_H

#include "mbed.h"
 
 
// Notes
#define C0  1/16.35
#define Db0 1/17.32
#define D0  1/18.35
#define Eb0 1/19.45
#define E0  1/20.60
#define F0  1/21.83
#define Gb0 1/23.12
#define G0  1/24.50
#define Ab0 1/25.96
#define LA0 1/27.50
#define Bb0 1/29.14
#define B0  1/30.87
#define C1  1/32.70
#define Db1 1/34.65
#define D1  1/36.71
#define Eb1 1/38.89
#define E1  1/41.20
#define F1  1/43.65
#define Gb1 1/46.25
#define G1  1/49.00
#define Ab1 1/51.91
#define LA1 1/55.00
#define Bb1 1/58.27
#define B1  1/61.74
#define C2  1/65.41
#define Db2 1/69.30
#define D2  1/73.42
#define Eb2 1/77.78
#define E2  1/82.41
#define F2  1/87.31
#define Gb2 1/92.50
#define G2  1/98.00
#define Ab2 1/103.83
#define LA2 1/110.00
#define Bb2 1/116.54
#define B2  1/123.47
#define C3  1/130.81
#define Db3 1/138.59
#define D3  1/146.83
#define Eb3 1/155.56
#define E3  1/164.81
#define F3  1/174.61
#define Gb3 1/185.00
#define G3  1/196.00
#define Ab3 1/207.65
#define LA3 1/220.00
#define Bb3 1/233.08
#define B3  1/246.94
#define C4  1/261.63
#define Db4 1/277.18
#define D4  1/293.66
#define Eb4 1/311.13
#define E4  1/329.63
#define F4  1/349.23
#define Gb4 1/369.99
#define G4  1/392.00
#define Ab4 1/415.30
#define LA4 1/440.00
#define Bb4 1/466.16
#define B4  1/493.88
#define C5  1/523.25
#define Db5 1/554.37
#define D5  1/587.33
#define Eb5 1/622.25
#define E5  1/659.26
#define F5  1/698.46
#define Gb5 1/739.99
#define G5  1/783.99
#define Ab5 1/830.61
#define LA5 1/880.00
#define Bb5 1/932.33
#define B5  1/987.77
#define C6  1/1046.50
#define Db6 1/1108.73
#define D6  1/1174.66
#define Eb6 1/1244.51
#define E6  1/1318.51
#define F6  1/1396.91
#define Gb6 1/1479.98
#define G6  1/1567.98
#define Ab6 1/1661.22
#define LA6 1/1760.00
#define Bb6 1/1864.66
#define B6  1/1975.53
#define C7  1/2093.00
#define Db7 1/2217.46
#define D7  1/2349.32
#define Eb7 1/2489.02
#define E7  1/2637.02
#define F7  1/2793.83
#define Gb7 1/2959.96
#define G7  1/3135.96
#define Ab7 1/3322.44
#define LA7 1/3520.01
#define Bb7 1/3729.31
#define B7  1/3951.07
#define C8  1/4186.01
#define Db8 1/4434.92
#define D8  1/4698.64
#define Eb8 1/4978.03



class Buzzer
{
public:
	Buzzer(PinName pwmPin);
	void imperialMarch();
	void levelComplete();
	void startUp();
	void testSound();

private:
	PwmOut ctrlPwm;

	// Duration of Notes
	float BPM; // change this to change the pace of the song
	float W; // whole 4/4
	float H; // half 2/4
	float Q; // quarter 1/4
	float E; // eighth 1/8
	float S; // sixteenth 1/16	
	float P; // This variable is used in pause()
	
	void setBPM(int newBPM);
	void pause(float duration);
	void play(float note, float duration);
};

#endif