#ifndef IR_H
#define IR_H


class IRController
{
	
public:
	// Constants
	static const float COEFF[]; // Coefficients found using linear regression (volts->cm)
	
	// Constructors
	IRController();
	
	// Methods
	float dist_to_wall(char dir); // Returns dist in cm
	
	
protected:
	// Class for the IR Transmitter and Receiver Pair
	class IRPair
	{
		public:
			IRPair();
			float readIR();
			
		private:
			//DigitalOut	TXPin;
			//AnalogIn 	RXPin;
	};
	
	// Constants
	static const short int SIGDELAY = 6; // Wait for firing capacitor signal (usec)
	static const short int NSAMPLES = 5;
	
	// Data Members
	//IRPair IRs[4]; // Order of IR Pairs: {FL, L, R, FR}
	
};


// COEFF = [x^-3, x^-2, x^-1, x^0, x^1, x^2, x^3]
const float IRController::COEFF[] = {0.218, -5.510, 55.011, -229.934, 506.986, -502.862, 177.713};

#endif 