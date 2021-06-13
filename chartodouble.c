#include "C:\Users\dinaa\Desktop\Embedded Systems CSE211\Labs\tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

void SystemInit() {}

void UART0_Init(void);
void UART1_Init();
void uart0_write(char c);

void getdata(float* N, float* E);
//float chartonum(char a[10], char l);
//float mintodeg(float x);

double difference(double i, double j);
double distance(double x, double y);


char arrN[];
char arrE[];
int arrE2[10];
int arrN2[9];

int main()
{

	//double lat1, lat2, lngt1, lngt2;
	//int i, j;
	//double d = 0;

	UART0_Init();
	UART1_Init();
	/*
	while(1){

	 //getdata(&N1, &E1);
	 //getdata(&N2, &E2);

	}*/

}




//array of characters into array of integers

void chartoint(char arr[]){
	int i;
	for(i=0;i<9;i++){
		arrN2[i]=arrN[i]-'0';
	}
	for(i=0;i<10;i++){
		arrE2[i]=arrE[i]-'0';
	}
}

//converting array of integers of latitude into a calculatable value

double chartonumN(int arrN2[10]) {
	float var = 10;
	int i;
	double lat;
	for (i=0; i<2; i++){
		arrN2[i]*=var;
		var=var/10;
	}

	var = 100;
	for(i=2;i<9;i++){
		arrN2[i]*=var/60;
		var=var/10;
	}
	for(i=0;i<9;i++){
		lat += arrN2[i];
		return (lat);
	}
}

//converting array of integers of longitude into a calculatable value
double chartonumE(int arrE2[10]) {
	float var = 100;
	int i;
	double lngt;
	for (i=0; i<3; i++){
		arrN2[i]*=var;
		var=var/10;
	}

	var = 100;
	for(i=2;i<10;i++){
		arrN2[i]*=var/60;
		var=var/10;
	}
	for(i=0;i<9;i++){
		lngt += arrE2[i];
		return (lngt);
	}
}

//x=difference(lat2,lat1)
//y=difference(lngt2,lngt1)

double distance(double x, double y) {
	double dist = sqrt((x*x) + (y*y));
	return(dist);
}



void UART0_Init(void) {

	{
		SYSCTL_RCGCUART_R |= 0x00000001;
		SYSCTL_RCGCGPIO_R |= 0x01;
		UART0_CTL_R &= ~0X01;

		UART0_LCRH_R |= 0X0000070;
		UART0_IBRD_R = 104;
		UART0_FBRD_R = 11;
		UART0_CTL_R |= 0X00000301;

		GPIO_PORTA_AFSEL_R |= 0X02;
		GPIO_PORTA_PCTL_R = ((GPIO_PORTA_PCTL_R &= ~0X000000FF) | 0X00000011);
		GPIO_PORTA_DEN_R |= 0X03;

	}
}



void UART1_Init()
{
	SYSCTL_RCGCUART_R |= 0x02;
	while ((SYSCTL_PRUART_R & 0x02) == 0);
	SYSCTL_RCGCGPIO_R |= 0x02;
	while ((SYSCTL_PRGPIO_R & 0x02) == 0);

	GPIO_PORTB_AFSEL_R = 0X03;
	GPIO_PORTB_AMSEL_R = 0X00;
	GPIO_PORTB_PCTL_R = 0X00000000;
	GPIO_PORTB_PCTL_R = 0X00000011;
	GPIO_PORTB_DEN_R |= 0X03;


	UART1_CTL_R &= ~0X01;
	UART1_LCRH_R |= 0X0000070;
	UART1_IBRD_R = 104;
	UART1_FBRD_R = 11;
	UART1_CTL_R |= 0X301;




}


//gps read func

char uart1_read(void)
{
	while ((UART1_FR_R & 0x10) != 0);
	return (UART1_DR_R & 0xFF);

}

/*char uart0_read(void)
{
	while((UART0_FR_R & 0x10)!=0);
	return (UART0_DR_R & 0xFF);
}
*/




void uart0_write(char c)
{
	while ((UART0_FR_R & 0x20) != 0);
	UART0_DR_R = c;

}



void getdata(float* N, float* E) {

	char arr1[26], arrN[10], arrE[11];
	int i, j;



	while (uart1_read() == 'L' && uart1_read() != 'E') {
		for (i = 0; i < 25; i++) {
			arr1[i] = uart1_read();
		}

		for (j = 0; j < 9; j++)
		{
			arrN[j] = arr1[i + 1];
		}
		
		for (j = 0; j < 10; j++)
		{
			arrE[j] = arr1[i + 16];
		}

	}
	
}
