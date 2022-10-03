#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "light_ws2812.h"
#include "USART_lib.h"

/* Cpu settings */
#define F_CPU 11059200
#define BAUD 9600 //9600
#define MYUBRR F_CPU/16/BAUD-1

/* Led settings */
#define MAXPIX 200
#define COLORLENGTH (MAXPIX/2)
#define FADE (256/COLORLENGTH)
#define COLORS 9





struct cRGB led[30];
struct cRGB colors[COLORS];
volatile uint8_t programNumber = 0;



ISR(USART_RXC_vect)
{
	/* Modu� wysy�a dane w postaci: dane, CR(0x0D), LF(0x0A) */
	uint8_t data = UDR;
	USART_Transmit(data);
	if ( (data != 0x0D) && (data != 0x0A) )
	{
		programNumber = data-0x30;

	}

	//UCSRA &= ~(1<<RXC);
}

int main(void)
{

    //Rainbowcolors
    colors[0].r=210; colors[0].g=17; colors[0].b=210;
    colors[1].r=255; colors[1].g=000; colors[1].b=000;//red
    colors[2].r=255; colors[2].g=100; colors[2].b=000;//orange
    colors[3].r=100; colors[3].g=255; colors[3].b=000;//yellow
    colors[4].r=000; colors[4].g=255; colors[4].b=000;//green
    colors[5].r=000; colors[5].g=100; colors[5].b=255;//light blue (t�rkis)
    colors[6].r=000; colors[6].g=000; colors[6].b=255;//blue
    colors[7].r=100; colors[7].g=000; colors[7].b=255;//violet



	DDRB|=_BV(ws2812_pin);

	unsigned int rgbColour[3];
	 // Start off with red.
	 rgbColour[0] = 255;
	 rgbColour[1] = 0;
	 rgbColour[2] = 0;

	 DDRD = 0xff;
	 USART_Init ( MYUBRR );

while(1)
    {
		while (programNumber == 1)
		{
		 // Choose the colours to increment and decrement.
		 for (int decColour = 0; decColour < 3; decColour += 1) {
		   int incColour = decColour == 2 ? 0 : decColour + 1;
		   // cross-fade the two colours.
		   for(int i = 0; i < 255; i += 1) {
		     rgbColour[decColour] -= 1;
		     rgbColour[incColour] += 1;
				for (uint8_t i =0; i < 30; i++)
				{
					led[i].r =rgbColour[0];
					led[i].g = rgbColour[1];
					led[i].b = rgbColour[2];
				}

			 ws2812_setleds(led, 30);
			 _delay_ms(4);

		   }
			// USART_Transmit('A');
			 //USART_Transmit('T');
			 //USART_Transmit((unsigned char) (0x0A));
			 //USART_Transmit((unsigned char) (0x0D));
		 }
		}

		while(programNumber == 2)
		{
			 // Choose the colours to increment and decrement.
			 for (int decColour = 0; decColour < 3; decColour += 1) {

			   int incColour = decColour == 2 ? 0 : decColour + 1;
			   // cross-fade the two colours.
			   for(int i = 0; i < 255; i += 1) {
			     rgbColour[decColour] -= 1;
			     rgbColour[incColour] += 1;
					for (uint8_t i =0; i < 30; i++)
					{
						led[i].r =rgbColour[0];
						led[i].g = rgbColour[1];
						led[i].b = rgbColour[2];
					}

				 ws2812_setleds(led, 30);
				 _delay_ms(40);

			   }
				// USART_Transmit('A');
				 //USART_Transmit('T');
				 //USART_Transmit((unsigned char) (0x0A));
				 //USART_Transmit((unsigned char) (0x0D));
			 }
		}

    }
}



