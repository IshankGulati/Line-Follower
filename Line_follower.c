/*
 * Line_follower.c
 *
 * Created: 09-07-2014 15:24:30
 *  Author: Ishank
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "motors.h" 
#define MAXSPEED 250
#define ROTATESPEED 150

int main(void)
{
	DDRA = 0X00;
	DDRB = 0XFF;
	init_motors();
	char sensors=0;
	char line_break=0;
    while(1)
    {
		PORTB=PINA;
		sensors = PINA;
		//straight
		if((sensors == 0b11100111)||(sensors == 0b11101111)||(sensors == 0b11110111))
		{
			set_motors(MAXSPEED,MAXSPEED);
		}
		//right drift
		else if((sensors == 0b11110011)||(sensors == 0b11100011))
		{
			set_motors((0.5*MAXSPEED),MAXSPEED);
		}
		else if((sensors == 0b11111001)||(sensors == 0b11110001))
		{
			set_motors(0,MAXSPEED);
		}
		else if((sensors == 0b11111100)||(sensors == 0b11111110))
		{
			set_motors(-(0.5*MAXSPEED),MAXSPEED);
		}
		else if(sensors == 0b11111000)
		{
			set_motors(-(0.25*MAXSPEED),MAXSPEED);
		}
		//left drift
		else if((sensors == 0b11001111)||(sensors == 0b11000111))
		{
			set_motors(MAXSPEED,(0.5 * MAXSPEED));
		}
		else if((sensors == 0b10011111)||(sensors == 0b10001111))
		{
			set_motors(MAXSPEED,0);
		}
		else if((sensors == 0b00111111)||(sensors == 0b01111111))
		{
			set_motors(MAXSPEED,-(0.5*MAXSPEED));
		}
		else if(sensors == 0b00011111)
		{
			set_motors(MAXSPEED,-(0.25*MAXSPEED));
		}
		//right angle turns
		else if((sensors == 0b11100000)||(sensors == 0b11110000))
		{
			set_motors(ROTATESPEED,-ROTATESPEED);
		}
		else if((sensors == 0b00000111)||(sensors == 0b00001111))
		{
			set_motors(-ROTATESPEED,ROTATESPEED);
		}
		//acute turns
		else if((sensors == 0b01100111)||(sensors == 0b00100111)||(sensors == 0b00110011))
		{
			set_motors(-ROTATESPEED,ROTATESPEED);
		}
		else if((sensors == 0b11100110)||(sensors == 0b11100100)||(sensors == 0b11001100))
		{
			set_motors(ROTATESPEED,-ROTATESPEED);
		}		
		//no path
		else if((sensors == 0b11111111) && line_break ==0)
		{
			set_motors(MAXSPEED,MAXSPEED);
			_delay_ms(750);
			line_break=1;
			continue;
		}
		else if((sensors == 0b11111111) && line_break ==1)
		{
			set_motors(ROTATESPEED,-ROTATESPEED);
		}
		else
		{
			set_motors(ROTATESPEED,-ROTATESPEED);
		}
	}
}