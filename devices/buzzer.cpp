/**
 * Buzzer class implementation. Includes constructor, pause, play, and song functions.
 */

#include "buzzer.hpp"


/* Constructor */
Buzzer::Buzzer(PinName pwmPin)
	: ctrlPwm(pwmPin) { }


/*
 * Sets the appropriate note durations based on the new BPM.
 */
void Buzzer::setBPM(int newBPM) {
    this->BPM = newBPM;
    this->Q = 60000 / this->BPM;    // 60,000 ms in 1 min
    this->W = this->Q * 4;
    this->H = this->Q * 2;
    this->E = this->Q / 2;
    this->S = this->Q / 4;    
    this->P = this->Q / 40;
}

	
/* 
 * Turns off the buzzer to simulate a musician taking
 * a breath between notes or to just stop playing.
 */
void Buzzer::pause(float duration) {
    this->ctrlPwm.period(0);   // Turn off buzzer
    this->ctrlPwm.write(0.5);
    wait(duration/1000);    
}


/* 
 * This function takes in the note the user wants to play 
 * along with the duration of the note.
 */
void Buzzer::play(float note, float duration) {
    this->ctrlPwm.period(note);
    this->ctrlPwm.write(0.5);
    wait(duration/1000);
    pause(P);
}



// Sheet Music Functions

/* Enter Lord Vader  */
void Buzzer::imperialMarch() {
    setBPM(90);

    play(LA3,Q);
    play(LA3,Q);
    play(LA3,Q);
    play(F3,E+S);
    play(C4,S);
    
    play(LA3,Q);
    play(F3,E+S);
    play(C4,S);
    play(LA3,H);
    
    play(E4,Q);
    play(E4,Q);
    play(E4,Q);
    play(F4,E+S);
    play(C4,S);
    
    play(Ab3,Q);
    play(F3,E+S);
    play(C4,S);
    play(LA3,H);
    
    play(LA4,Q);
    play(LA3,E+S);
    play(LA3,S);
    play(LA4,Q);
    play(Ab4,E+S);
    play(G4,S);

    play(Gb4,S);
    play(E4,S);
    play(F4,E);
    
    pause(E); // PAUSE
    
    play(Bb3,E);
    play(Eb4,Q);
    play(D4,E+S);
    play(Db4,S);
    
    play(C4,S);
    play(B3,S);
    play(C4,E);
    
    pause(E); // PAUSE
    
    play(F3,E);
    play(Ab3,Q);
    play(F3,E+S);
    play(LA3,S);
    
    play(C4,Q);
    play(LA3,E+S);
    play(C4,S);
    play(E4,H);
    
    play(LA4,Q);
    play(LA3,E+S);
    play(LA3,S);
    play(LA4,Q);
    play(Ab4,E+S);
    play(G4,S);
    
    play(Gb4,S);
    play(E4,S);
    play(F4,E);
    
    pause(E); // PAUSE
    
    play(Bb3,E);
    play(Eb4,Q);
    play(D4,E+S);
    play(Db4,S);
    
    play(C4,S);
    play(B3,S);
    play(C4,E);
    
    pause(E); // PAUSE
    
    play(F3,E);
    play(Ab3,Q);
    play(F3,E+S);
    play(C4,S);
    
    play(LA3,Q);
    play(F3,E+S);
    play(C4,S);
    play(LA3,H);
    
    pause(E); // END
}


/* Super Mario Level Complete */
void Buzzer::levelComplete() {
    setBPM(180);

    play(G5,E);
    play(C6,E);
    play(E6,E);

    play(G6,E);
    play(C7,E);
    play(E7,E);

    play(G7,Q);
    play(E7,Q);
    

    play(Ab5,E);
    play(C6,E);
    play(Eb6,E);

    play(Ab6,E);
    play(C7,E);
    play(Eb7,E);

    play(Ab7,Q);
    play(E7,Q);


    play(Bb5,E);
    play(D6,E);
    play(F6,E);

    play(Bb6,E);
    play(D7,E);
    play(F7,E);
    
    play(Bb7,Q);
    play(Bb7,E);
    play(Bb7,E);
    play(Bb7,E);

    play(C8,H);
    pause(H); // END  
}


/* Legend of Zelda Treasure Chest */
void Buzzer::startUp() {
}


/* Test the buzzer */
void Buzzer::testSound() {
    setBPM(210);

    float testNote = 0.00083;
    play(testNote, E);
    pause(S);
    play(testNote, E);
}