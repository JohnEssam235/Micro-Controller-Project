#include "lcd.h"
#include "port.h"
#include "keypad.h"
#include "flash.h"
void SystemInit() {}

int main()
{
	// ana hst3ml el led bta3t portf.....W EL BUTTONS bta3tha  .... led1 el hya PF1(red) w button2 PF0 W PF4 ( switch1 -> PF0)..
	LCD_init();
	Flash_Enable();
	LCD_clearScreen();
	PORTB_INIT();  // H43'L EL PORTB EL 3LEH EL LCD_DATA
	PORTC_INIT();  //3leh el LCD_control
	PORTD_INIT(); // KEYPAD
	PORTF_INIT();
	SET_BIT(GPIO_PORTF_DIR_R,1);  // 3mlt pf1 b output
	SET_BIT(GPIO_PORTF_DATA_R,0); // EL AWL 3LEH one ..... el awl el lock mfto7....
	CLEAR_BIT(GPIO_PORTF_DIR_R,0);  // PF0 b input
	CLEAR_BIT(GPIO_PORTF_DIR_R,4);   // PF4 b input
	
	// variables ........................
	uint8 get_keypad;
	uint8 get_keypad2;
	while(1)
	{
		LCD_goToRowColumn(0,0);
		LCD_displayString("set password");
		LCD_goToRowColumn(1,0);
		for(int i=0;i<5;i++)
		{
		  get_keypad = KeyPad_getPressedKey();
			// 5azen f el memory ..............
			LCD_displayCharacter(get_keypad);
		}
		while((GPIO_PORTF_DATA_R & 0x01) == 1)
		{
			// dy loop fadya hstnah bs yedos 3ala enter el howa el push button ...  
		}
		// lazem bas el password myb2a4 b 0000 ...............
		if(//el password b 0000)
		{
			LCD_clearScreen();
			LCD_displayString("password cant be");
			LCD_goToRowColumn(1,0);
			LCD_displayString("0000");
			LCD_clearScreen();
			LCD_displayString("enter pass again");
			main();
		}
		while((GPIO_PORTF_DATA_R & 0x10) == 1)
		{
			// hstnah yedos 3ala button2 ...keda howa 2afal el lock ..fa h2fel el led y3ny ...
			CLEAR_BIT(GPIO_PORTF_DATA_R,1);   
		}
		LCD_clearScreen();
		LCD_displayString("enter password");
		LCD_goToRowColumn(1,0);
		for(int i=0;i<5;i++)
		{                   // momken a5odhom 3ala kaza for loop ..................b 5 variables......
			get_keypad2 = KeyPad_getPressedKey();
			// hakaren bl password bta3ty b2a ................ kol rakam byd5lo b kol rakam mktob abl kda ....
			LCD_displayCharacter(get_keypad2);
		}
		while((GPIO_PORTF_DATA_R & 0X01) == 1)
		{}  // lazm astnah yedos enter...............
			
			
		// lw el password sa7 yfta7 el lock y3ny ynwr el led w y2olo en el safebox is opening w el 3aks bardo.....
		if(// true condition)  
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
