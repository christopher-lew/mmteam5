/**
 * Quadrature Encoders implementation.
 */

#include "QEI_HW.hpp"


/* Constructor */
QEI_HW::QEI_HW(int TIM_choice)
	: TIM_X(TIM_choice) 
{
	if (this->TIM_X == 2) {
		EncoderInitTIM2();
	}
	else if (this->TIM_X == 5) {
		EncoderInitTIM5();
	}
}


unsigned int QEI_HW::read()
{
	unsigned int count;
	if (this->TIM_X == 2) {
		count = TIM2->CNT;
	}
	else if (this->TIM_X == 5) {
		count = TIM5->CNT;
	}
	return count;
}


void QEI_HW::reset()
{
	if (this->TIM_X == 2) {
		TIM2->CNT = 0;
	}
	else if (this->TIM_X == 5) {
		TIM5->CNT = 0;
	}
}


// ----- ----- ----- ----- Encoder Timer Initialization ----- ----- ----- ----- -----
/* Left Encoder = {PB_10, PA_5} */
void EncoderInitTIM2()
{
	
}

/* Right Encoder = {PA_0, PA_1} */
void EncoderInitTIM5()
{	
	// configure GPIO PA0 & PA1 aka A0 & A1 as inputs for Encoder
    // Enable clock for GPIOA
    __GPIOA_CLK_ENABLE(); //equivalent from hal_rcc.h
	
    //stm32f4xx.h 
    GPIOA->MODER   |= GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1 ;           //PA0 & PA1 as Alternate Function   /*!< GPIO port mode register,               Address offset: 0x00      */
    GPIOA->OTYPER  |= GPIO_OTYPER_OT_0 | GPIO_OTYPER_OT_1 ;                 //PA0 & PA1 as Inputs               /*!< GPIO port output type register,        Address offset: 0x04      */
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0 | GPIO_OSPEEDER_OSPEEDR1 ;     //Low speed                         /*!< GPIO port output speed register,       Address offset: 0x08      */
    GPIOA->PUPDR   |= GPIO_PUPDR_PUPDR0_1 | GPIO_PUPDR_PUPDR1_1 ;           //Pull Down                         /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    GPIOA->AFR[0]  |= 0x00000011 ;                                          //AF01 for PA0 & PA1                /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    GPIOA->AFR[1]  |= 0x00000000 ;                                          //nibbles here refer to gpio8..15   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
	
    // configure TIM5 as Encoder input
    // Enable clock for TIM5
    __TIM5_CLK_ENABLE();
	
    TIM5->CR1   = 0x0001;     // CEN(Counter ENable)='1'     < TIM control register 1
    //TIM5->SMCR  = TIM_ENCODERMODE_TI12;     // SMS='011' (Encoder mode 3)  < TIM slave mode control register
    TIM5->CCMR1 = 0xF1F1;     // CC1S='01' CC2S='01'         < TIM capture/compare mode register 1
    TIM5->CCMR2 = 0x0000;     //                             < TIM capture/compare mode register 2
    TIM5->CCER  = 0x0011;     // CC1P CC2P                   < TIM capture/compare enable register
    TIM5->PSC   = 0x0000;     // Prescaler = (0+1)           < TIM prescaler
    TIM5->ARR   = 0xffffffff; // reload at 0xfffffff         < TIM auto-reload register
  
    TIM5->CNT = 0;  // reset the counter before we use it
}