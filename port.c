
#include "port.h"



// ay direction aw read aw write m4 h3mlo hena ....................
// el 7aga el h3mlha hena hya el pull up resistors bto3 el switches bta3t PORTF............




void PORTA_INIT()
{
	SYSCTL_RCGCGPIO_R |= 0x01;
	GPIO_PORTF_DEN_R =0xFF;
	//GPIO_PORTA_DIR_R |= 0b00000000;  lw hst3ml PORTA aslun  ..w mtnsa4 el register el b3ml meno read w write....bas dol hktebhom f el main.c m4 hena,,,,,,,,
}

void PORTB_INIT()
{
	SYSCTL_RCGCGPIO_R |= 0x02;
	GPIO_PORTF_DEN_R =0xFF;
	//GPIO_PORTB_DIR_R |= 0b00000000;
	//GPIO_PORTB_DATA_R |= 0X00;
}

void PORTC_INIT()
{
	SYSCTL_RCGCGPIO_R |= 0x04;
	GPIO_PORTF_DEN_R =0xFF;
	//GPIO_PORTC_DIR_R |= 0b00000000;
	//GPIO_PORTC_DATA_R |= 0X00;
}

void PORTD_INIT()
{
	SYSCTL_RCGCGPIO_R |= 0x08;
	GPIO_PORTF_DEN_R =0xFF;
	//GPIO_PORTD_DIR_R |= 0b00000000;
	//GPIO_PORTD_DATA_R |= 0X00;
}

void PORTE_INIT()
{
	SYSCTL_RCGCGPIO_R |= 0x10;
	GPIO_PORTF_DEN_R =0xFF;
	//GPIO_PORTE_DIR_R |= 0b00000000;
	//GPIO_PORTE_DATA_R |= 0X00;
}

void PORTF_INIT()
{
	SYSCTL_RCGCGPIO_R |= 0x20;
	GPIO_PORTF_DEN_R =0xFF;
	GPIO_PORTF_LOCK_R = 0X4C4F434B;
	GPIO_PORTF_CR_R  = 0Xff;
  GPIO_PORTF_PUR_R  = 0x11;      	
	//GPIO_PORTF_DIR_R |= 0b00000000;
	//GPIO_PORTF_DATA_R |= 0X00;
}