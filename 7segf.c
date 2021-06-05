#include "stdint.h"
#include "stdio.h"
#include "C:\Users\dinaa\Desktop\Embedded Systems CSE211\Labs\tm4c123gh6pm.h"
void SystemInit(){}
void led_seg_Init(void)
{
	
	// PORTB Initialisation
	SYSCTL_RCGCGPIO_R = 0x02;   
	while ((SYSCTL_PRGPIO_R&0X02) == 0){};
		GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |= 0xFF;
		GPIO_PORTB_DEN_R |= 0XFF;
		GPIO_PORTB_DIR_R |= 0XFF;
		GPIO_PORTB_AMSEL_R &= ~0XFF;
		GPIO_PORTB_AFSEL_R &= ~0XFF;
		GPIO_PORTB_PCTL_R &= ~0XFFFFFFFF;
	
	// PORTE Initialisation
	SYSCTL_RCGCGPIO_R = 0x10;    
	while ((SYSCTL_PRGPIO_R&0x10) == 0){};
    GPIO_PORTE_LOCK_R = 0x4C4F434B;
	  GPIO_PORTE_CR_R |= 0x0F;
		GPIO_PORTE_DIR_R |= 0X0F;
		GPIO_PORTE_DEN_R |= 0x0F;
		GPIO_PORTE_AMSEL_R &= ~0x0F;
		GPIO_PORTE_AFSEL_R &=~0x0F;
		GPIO_PORTE_PCTL_R &= ~0xFFFFFFFF;
	
	// PORTF Initialisation
	SYSCTL_RCGCGPIO_R = 0x20;   
	while ((SYSCTL_PRGPIO_R&0x20) == 0){};
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
	  GPIO_PORTF_CR_R |= 0x0F;
		GPIO_PORTF_DIR_R |= 0X0F;
		GPIO_PORTF_DEN_R |= 0x0F;
		GPIO_PORTF_AMSEL_R &= ~0x0F;
		GPIO_PORTF_AFSEL_R &=~0x0F;
		GPIO_PORTF_PCTL_R &= ~0xFFFFFFFF;

	

}


		int main()
		{
			SystemInit();
			while(1)
			{
				
				led_seg_Init(); 
				
				GPIO_PORTB_DATA_R |= 0X01;
				
				
		
			}
			return 0;
		}
