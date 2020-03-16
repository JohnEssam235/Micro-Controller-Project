#include "lcd.h"
#include "port.h"
#include "keypad.h"
// dy el main without flash memory driver w bonus el timer ..............................................................
void SystemInit() {}
// variables...................................	dol el ha5od feh el password lama y3ml set ....
uint32_t num1=0;
uint32_t num2=0;
uint32_t num3=0;
uint32_t num4=0;
	// variables ..................dol el hyd5lhom 34an yfta7 el lock b2a .................
	uint32_t num5=0;
	uint32_t num6=0;
	uint32_t num7=0;
	uint32_t num8=0;
	
int main()
{
	// ana hst3ml el led bta3t portf.....W EL BUTTONS bta3tha  .... led1 el hya PF1(red) w button2 PF0 W PF4 ( switch1 -> PF0)..
	LCD_init();
	LCD_clearScreen();
	PORTB_INIT();  // H43'L EL PORTB EL 3LEH EL LCD_DATA
	PORTC_INIT();  //3leh el LCD_control
	PORTD_INIT(); // KEYPAD
	PORTF_INIT();
	SET_BIT(GPIO_PORTF_DIR_R,1);  // 3mlt pf1 b output
	SET_BIT(GPIO_PORTF_DATA_R,1); // EL AWL 3LEH one ..... el awl el lock mfto7....
	CLEAR_BIT(GPIO_PORTF_DIR_R,0);  // PF0 b input
	CLEAR_BIT(GPIO_PORTF_DIR_R,4);   // PF4 b input
	
	
	while(1)
	{
		LCD_goToRowColumn(0,0);
		LCD_displayString("set password");
		LCD_goToRowColumn(1,0);
		
	  // hbda2 a5od el password.........

		
		num1 = KeyPad_getPressedKey();
		LCD_intgerToString(num1);
		
		num2 = KeyPad_getPressedKey();
		LCD_intgerToString(num2);
		
		num3 = KeyPad_getPressedKey();
		LCD_intgerToString(num3);
		
		num4 = KeyPad_getPressedKey();
		LCD_intgerToString(num4);
		
		while((GPIO_PORTF_DATA_R & 0x01) != 1)
		{
			// dy loop fadya hstnah bs yedos 3ala enter el howa el push button ...  
		}
		// lazem bas el password myb2a4 b 0000 ...............
		if((num1 == 0) && (num2 == 0) && (num3 ==0) && (num4 ==0))
		{
			LCD_clearScreen();
			LCD_displayString("password cant be");
			LCD_goToRowColumn(1,0);
			LCD_displayString("0000");
			LCD_clearScreen();
			LCD_displayString("enter pass again");
			main();
		}
		while((GPIO_PORTF_DATA_R & 0x10) != 1)
		{
			// hstnah yedos 3ala button2 ...keda howa 2afal el lock ..fa h2fel el led y3ny ...
			CLEAR_BIT(GPIO_PORTF_DATA_R,1);   
		}
		LCD_clearScreen();
		LCD_displayString("enter password");
		LCD_goToRowColumn(1,0);
	   
    num5 = KeyPad_getPressedKey();
    LCD_intgerToString(num5);	

    num6 = KeyPad_getPressedKey();
    LCD_intgerToString(num6);	

    num7 = KeyPad_getPressedKey();
    LCD_intgerToString(num7);	

    num8 = KeyPad_getPressedKey();
    LCD_intgerToString(num8);			
		 
		while((GPIO_PORTF_DATA_R & 0X01) == 1)
		{}  // lazm astnah yedos enter...............
			
			
		// lw el password sa7 yfta7 el lock y3ny ynwr el led w y2olo en el safebox is opening w el 3aks bardo.....
		if((num1 == num5) && (num2 == num6) && (num3 == num7) && (num4 == num8))  
		{
			LCD_clearScreen();
			LCD_displayString("pass is correct");
			SET_BIT(GPIO_PORTF_DATA_R,2);
			LCD_clearScreen();
			LCD_displayString("safebox is open");
		}
		else
		{
			LCD_clearScreen();
			LCD_displayString("pass is wrong");
			LCD_clearScreen();
			LCD_displayString("safebox is ");
			LCD_goToRowColumn(1,0);
			LCD_displayString("closed");
		}
			
	}
	
}
