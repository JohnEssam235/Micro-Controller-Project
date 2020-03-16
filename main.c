#include "lcd.h"
#include "port.h"
#include "keypad.h"
// dy el main without flash memory driver  bs feha el bonus bta3 el timer  ..............................................................
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
	// variables .............da el flag bta3 el timer ............
	uint32_t flag;

void systick_init()
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R=0XFFFFFF;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R = 0X00000005;
}	

void systick_wait(uint32_t count)    // lazm a3raf howa fedel dayes 3al button 5 sawany f3lan wla la2 ..... fa lazm a3ed ana 7asabt kam 1 second ......lazm yb2o 5 mn el 1 seconds ..... fa hst3ml el function el etktbt f el section w el mo7adra el hya bt3ed ana sh3'lt el timer kam mara...................
{
	NVIC_ST_RELOAD_R = count-1;
	NVIC_ST_CURRENT_R=0;
	while((NVIC_ST_CTRL_R & 00010000)==0)
	{}
}
void systick_wait_1sec(uint32_t delay)
{
	flag = 0;
	while((flag<delay) && (GPIO_PORTF_DATA_R & 0X00000001) == 1) 
	{
		systick_wait(400000000);  // 7asabt el counts tel3et 4*(10^8)...........cross mult. 
		flag++;
	}
}


int main()
{
	// ana hst3ml el led bta3t portf.....W EL BUTTONS bta3tha  .... led1 el hya PF1(red) w button2 PF0 W PF4 ( switch1 -> PF0)..
	LCD_init();
	LCD_clearScreen();
	systick_init();
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
		
		while((GPIO_PORTF_DATA_R & 0x01) == 1)
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
		 
		while((GPIO_PORTF_DATA_R & 0X01) != 1)
		{}  // lazm astnah yedos enter...............
				
			
		// lw el password sa7 yfta7 el lock y3ny ynwr el led w y2olo en el safebox is opening w el 3aks bardo.....
		if((num1 == num5) && (num2 == num6) && (num3 == num7) && (num4 == num8))  
		{
			LCD_clearScreen();
			LCD_displayString("pass is correct");
			SET_BIT(GPIO_PORTF_DATA_R,2);
			LCD_clearScreen();
			LCD_displayString("safebox is open");
			// howa dlw2ty fata7 el box tamam ......mmkn b2a ye7eb y3ml reset ll password .....fa howa lazem yedos 3ala push button l modet 5 seconds ....fa howa lw das 3al enter push button l modet 5 seconds h5leh y3ml reset ..................
			if((GPIO_PORTF_DATA_R & 0X00000001) == 1)  // lw das 3al enter push button haro7 a3ml el timer........ 
 			{	
			    systick_wait_1sec(5);    // 5 marat y3ny 5 mn el 1 second y3ny 5 seconds.............
				  if(flag == 5)  // lw fedel 5 seconds f3lan dayes 3al button .......
						main();
			}
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
