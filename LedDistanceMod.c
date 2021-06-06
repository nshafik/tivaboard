#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#include "E:\Embedded/tm4c123gh6pm.h"

void SystemInit(){}
void led_Init(void);              //Initializes ports used in 7 segments and led
void LedFunc(int start,int end);      //calculates distance and sends signals to 7 seg and led accordingly 




int main()
{
		SystemInit();
			
		led_Init(); 
				
		while(1){
			LedFunc(0x55,0x54);
			LedFunc(0x6,0x100);
			GPIO_PORTB_DATA_R |= 0X01;				
		
		}
return 0;
}





void led_Init(void)
{
  SYSCTL_RCGCGPIO_R = 0x20;

	                     
	while ((SYSCTL_PRGPIO_R&0X20) == 0){};

		
		
		GPIO_PORTF_LOCK_R = 0x4C4F434B;               // PORTF Initialisation
    GPIO_PORTF_CR_R |= 0x0F;                      //Using only 4 pins in port F    
		GPIO_PORTF_DIR_R |= 0X0F;
		GPIO_PORTF_DEN_R |= 0x0F;
		GPIO_PORTF_AMSEL_R &= ~0x0F;
		GPIO_PORTF_AFSEL_R &=~0x0F;
		GPIO_PORTF_PCTL_R &= ~0xFFFFFFFF;
	}


	
void LedFunc(start, end){
		int distance = abs( end - start);
		if (distance < 100){
			GPIO_PORTF_DATA_R = 0X00;
		}
		else{
			GPIO_PORTF_DATA_R |= 0X02;                   //turn on RED\sevenseg
		}
	

}