/*
 * main.c
 *
 *  Created on: 7 gru 2017
 *      Author: Kensaj
 */

//----------------------------------------------------------------------------
//Biblioteki
#include <avr/io.h>
#include <util/delay.h>
#include <dht/dht.c>

//----------------------------------------------------------------------------
//Definicje sta³ych
#define ADCIN PC1
//#define TEMPIN PC5
#define F_CPU 8000000

//----------------------------------------------------------------------------
//Potrzebne zmienne
int8_t temp = 0;
int8_t hum = 0;

int8_t temp_flag = -1;  // -1 - neutral / 1 - heat
int8_t hum_flag = 0;

uint8_t target_temp = 0;
uint8_t target_hum = 0;
int8_t licznik = 0;
//----------------------------------------------------------------------------
//Definicje funkcji
void Init();

int main(void)
{
	Init();

    while(1)
    {
    ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
    while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji

    					target_temp =  20+((ADC)/95);
    					PORTB &= 0b11000000;
    					PORTB |= target_temp;
    					_delay_ms(10);
    					if(licznik==50)
    					{
    						do
    						{
    						_delay_ms(50);
    						}while(dht_gettemperature(&temp)!=0);

    						licznik = 0;
    					}
    					licznik++;

    					if(temp>0 && temp<35)
    						{
    							if(target_temp<temp+temp_flag)
    						    	{
    						    		_delay_ms(50);
    						    		PORTB |= (1<<PB7);
    						    		_delay_ms(300);
    						    	}
    						    else
    						    	{
    						    		_delay_ms(50);
    						    		PORTB &= ~(1<<PB7);
    						    		_delay_ms(300);
    						    	}
    						}




     }
}

//----------------------------------------------------------------------------
//Funkcja w³¹czaj¹ca potrzebne uk³ady
void Init()
{

  //-------------------
  //Konfiguracja portów

	DDRB = 0xff;
	PORTB = 192;

//	DDRD = 0xff;
//	PORTD |= (1<<PD7) | (1<<PD6);




	 ADCSRA =   (1<<ADEN)|(1<<ADPS0); //ADEN: ADC Enable (uruchomienie przetwornika)

	ADMUX  =  (1<<REFS0)|(1<<MUX0);



}



