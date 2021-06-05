#include <stdint.h>
#include "E:\Embedded/tm4c123gh6pm.h"
void SystemInit(){}
void led_seg_Init(void)
{
SYSCTL_RCGCGPIO_R = 0x01;    //init port A
while ((SYSCTL_PRGPIO_R&0x20) == 0){};
	
	
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
	  GPIO_PORTA_CR_R |= 0x0F;
		GPIO_PORTA_DIR_R |= 0X0F;
		GPIO_PORTA_DEN_R |= 0x0F;
		GPIO_PORTA_AMSEL_R &= ~0x0F;
		GPIO_PORTA_AFSEL_R &=~0x0F;
		GPIO_PORTA_PCTL_R &= ~0xFFFFFFFF;
	
	
SYSCTL_RCGCGPIO_R = 0x02;   //init port B
while ((SYSCTL_PRGPIO_R&0X02) == 0){};
	
	
		GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |= 0x0F;
		GPIO_PORTB_DEN_R |= 0X0F;
		GPIO_PORTB_DIR_R |= 0X0F;
		GPIO_PORTB_AMSEL_R &= ~0XFF;
		GPIO_PORTB_AFSEL_R &= ~0XFF;
		GPIO_PORTB_PCTL_R &= ~0XFFFFFFFF;
	
SYSCTL_RCGCGPIO_R = 0x10;    //init port E
while ((SYSCTL_PRGPIO_R&0x20) == 0){};
	
	
    GPIO_PORTE_LOCK_R = 0x4C4F434B;
	  GPIO_PORTE_CR_R |= 0x0F;
		GPIO_PORTE_DIR_R |= 0X0F;
		GPIO_PORTE_DEN_R |= 0x0F;
		GPIO_PORTE_AMSEL_R &= ~0x0F;
		GPIO_PORTE_AFSEL_R &=~0x0F;
		GPIO_PORTE_PCTL_R &= ~0xFFFFFFFF;
	
	
SYSCTL_RCGCGPIO_R = 0x20;   //init port F
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
			while(1)
			{
			led_seg_Init();
		
			GPIO_PORTB_DATA_R |= 0X01;
				
				
		
			}
			return 0;
		}