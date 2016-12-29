#include "buzzer.hpp"


Buzzer::Buzzer(PinName pwmPin)
	: PwmCtrl(pwmPin) { }

	
/* 
 * This sets turns off the buzzer to simulate a musician 
 * taking a breath between notes or to just stop playing 
 */
void Buzzer::pause(float duration) {
    this->PwmCtrl.period(0);   // Turn off buzzer
    this->PwmCtrl.write(0.5);
    wait(duration/1000);    
}


/* 
 * This function takes in the note the user wants to play 
 * along with the duration of the note 
 */
void Buzzer::play(float note, float duration) {
    this->PwmCtrl.period(note);
    this->PwmCtrl.write(0.5);
    wait(duration/1000);
    pause(P);
}

// Music

/* Enter Lord Vader  */
void Buzzer::imperialMarch() {   
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