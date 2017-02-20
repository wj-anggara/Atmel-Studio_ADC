/*
 * ADC.c
 *
 * Created: 17/02/2017 8:11:00
 * Author : Anggara Wijaya
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>						//This lib is where the itoa function is located

char bufferADC[5];
uint16_t adc_value;						//Variable used to store the value read from the ADC
uint16_t read_adc(uint8_t channel);		//Function to read an arbitrary analogic channel/pin

void adc_init(void);

int main(void)
{
	adc_init();
	while (1)
	{
		adc_value = read_adc(0);        //Read one ADC channel
		//itoa(adc_value, bufferADC, 10);    //Convert the read value to an ascii string
		//USART_putstring(bufferADC);        //Send the converted value to the terminal
	}
}

void adc_init(void)
{	
	//ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));   //16Mhz/128 = 125Khz the ADC reference clock
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1));				//8Mhz/64=125 Khz
	ADMUX |= (1<<REFS0);							//Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN);							//Turn on ADC
	ADCSRA |= (1<<ADSC);							//Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}

uint16_t read_adc(uint8_t channel)
{
	ADMUX &= 0xF0;						//Clear the older channel that was read
	ADMUX |= channel;					//Defines the new ADC channel to be read
	ADCSRA |= (1<<ADSC);                //Starts a new conversion
	while(ADCSRA & (1<<ADSC));          //Wait until the conversion is done
	return ADCW;						//Returns the ADC value of the chosen channel
}