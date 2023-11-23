#include <avr/io.h>
#include <avr/interrupt.h>

int i=0,j=0;
int n=0;
char portState[4]= {0xEF,0xDF,0xBF,0x7F};
char inputState[4]= {0x01,0x02,0x04,0x08};
int mass2[4][4]={{1,2,3,4},
{5,6,7,8},
{9,10,11,12},
{13,14,15,16}};
ISR(TIMER2_COMP_vect)
{
	for (i=0; i<4; i++)
	{
		PORTA=portState[i];
		for (j=0; j<4; j++)
		{
			if (((PINA&inputState[j])==0))
			{
				while((PINA&inputState[j])!=inputState[j]){};
				n=(mass2[i][j]);
			}
		}
	}
}

int main(void)
{
	PORTA=0xFF;
	DDRA=0xF0;
	
	PORTB=0xFF;
	
	ASSR=0x00;
	TCCR2=0x0F;
	TCNT2=0x00;
	OCR2=0xC3;
	TIMSK=0x80;
	sei();
	while(1)
	{
				switch(n)
				{
					case 1:{PORTB=0x01; break;}
					case 2:{PORTB=0x02; break;}
					case 3:{PORTB=0x04; break;}
					case 4:{PORTB=0x08; break;}
					case 5:{PORTB=0x10; break;}
					case 6:{PORTB=0x20; break;}
					case 7:{PORTB=0x40; break;}
					case 8:{PORTB=0x80; break;}
					case 9:{PORTB=0x100; break;}
				}
	}
}