#include<stdint.h>
#include"ADC.h"
#include"RCC.h"
#include"GPIO.h"

void ADC01_CH01_Init(void){
	// Enable GPIOA and ADC1 clocks
	RCC->APB2ENR.BITS.IOPAEN = 1;
	RCC->APB2ENR.BITS.ADC1EN = 1;

	// Configure PA0 as analog input (ADC channel 0)
	GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT_ANALOG);

	// Configure sample time for channel 0 (SMPR2 bits [2:0]) -> maximum sampling
	ADC_SMPR2 &= ~(0x7 << (3 * 0));
	ADC_SMPR2 |=  (0x7 << (3 * 0));

	// Regular sequence length = 1 conversion
	ADC_SQR1 &= ~(0xF << 20);

	// First conversion in regular sequence = channel 0
	ADC_SQR3 &= ~(0x1F << 0);
	ADC_SQR3 |=  (0 << 0);

	// Turn on ADC
	ADC_CR2 |= 1;

	// Small delay to let ADC power up
	for(volatile int i = 0; i < 1000; ++i);
}

uint16_t ADC01_CH0_Read(void){
	// Start conversion by software
	ADC_CR2 |= (1 << 22); // SWSTART (software start)

	// Wait for end of conversion (EOC)
	while(!(ADC_SR & (1 << 1)));

	// Read and return result
	return (uint16_t)(ADC_DR & 0xFFFF);
}

