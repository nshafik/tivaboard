#include "stdint.h"
#include "stdio.h"
#include "C:\Users\dinaa\Desktop\Embedded Systems CSE211\Labs\tm4c123gh6pm.h"

void SystemInit(){}
int distance;
void RGBLED_Init(void)
	
{
	SYSCTL_RCGCGPIO_R |= 0X02;
	while ((SYSCTL_PRGPIO_R &0X02)==0){}
		GPIO_PORTB_DEN_R |= 0XFF;
		GPIO_PORTB_DIR_R |= 0XFF;
		GPIO_PORTB_AMSEL_R &= ~0XFF;
		GPIO_PORTB_AFSEL_R &= ~0XFF;
		GPIO_PORTB_PCTL_R &= ~0XFFFFFFFF;
		
		
	SYSCTL_RCGCGPIO_R |= 0X20;
	while((SYSCTL_PRGPIO_R&0X20)==0){}
		GPIO_PORTF_LOCK_R = 0X4C4F434B;
		GPIO_PORTF_CR_R |= 0X0E;
		GPIO_PORTF_DIR_R |= 0X0E;
		GPIO_PORTF_DEN_R |= 0X0E;
		GPIO_PORTF_AMSEL_R &= ~0X0E;
		GPIO_PORTF_AFSEL_R &= ~0X0E;
		GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
		}

int main(){
	
	SystemInit();
	RGBLED_Init();
	GPIO_PORTF_DATA_R = 0X08;
	//GPIO_PORTF_DATA_R = 0X02;
	distance = 0X65;
	if (distance >= 0X64){
		GPIO_PORTF_DATA_R |= 0X02;
	}
}	
	/*return 0*/
