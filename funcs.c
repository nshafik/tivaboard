#include "E:\Embedded\tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

void SystemInit() {}


#define LCD GPIOB   /* Define "LCD" as a symbolic name for GPIOB */
#define RS 0x20 /* PORTB BIT5 mask */
#define RW 0x40 /* PORTB BIT6 mask */
#define EN 0x80 /* PORTB BIT7 mask */
#define HIGH 1
#define LOW 0

/*define useful symbolic names for LCD commands */
#define clear_display     0x01
#define returnHome        0x02
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode        0x06
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80

/* prototypes of LCD functions */
void delay_ms(int n); /* mili second delay function */
void delay_us(int n); /* micro second delay function */
void LCD_init(void);  /* LCD initialization function */
void LCD_Cmd(unsigned char command); /*Used to send commands to LCD */
void LCD_Write_Char(unsigned char data); /* Writes ASCII character */
void LCD_Write_Nibble(unsigned char data, unsigned char control); /* Writes 4-bits */
void LCD_String(char str); /*Send string to LCD function */


void LCD_String(char str);
void LCD_Write_Char(unsigned char data);
void LCD_Write_Nibble(unsigned char data, unsigned char control);
void LCD_Cmd(unsigned char command);
void LCD_init(void);

void delay_us(int n);
void delay_ms(int n);


void UART0_Init(void);
void UART1_Init();
void uart0_write(char c);
char uart1_read(void);

void getdata(float* N, float* E);
float chartonum(char a[10], char l);
float mintodeg(float x);

float difference(float i, float j);
float distance(float x, float y);

void LED_Init(void);






int main()
{

	float N1, N2, E1, E2;
	int i, j;
	float d = 0;

	UART0_Init();
	UART1_Init();
	


	LCD_Write_Char('A');
	delay_ms(500);
	while (1) {

	    getdata(&N1, &E1);
		getdata(&N2, &E2);

		d += distance(difference(N1, N2), difference(E1, E2));

	}

}






void LED_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;
	while ((SYSCTL_PRGPIO_R & 0x20) == 0) {};
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x0E;
	GPIO_PORTF_DIR_R |= 0X0E;
	GPIO_PORTF_DEN_R |= 0x0E;
	GPIO_PORTF_AMSEL_R &= ~0x0E;
	GPIO_PORTF_AFSEL_R &= ~0x0E;
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0;

}




void uart0_write(char c)
{
	while ((UART0_FR_R & 0x20) != 0);
	UART0_DR_R = c;

}



char uart1_read(void)
{
	while ((UART1_FR_R & 0x10) != 0);
	return (UART1_DR_R & 0xFF);

}



float difference(float i, float j) {
	float dif;
	if (i > j) {
		dif = i - j;
	}
	else {
		dif = j - i;
	}

	return dif;



}



float mintodeg(float x) {
	float minx = x / 100;
	int xint = minx;
	float deg = minx - xint;
	deg = deg / 60 + minx;
	printf("%f", deg);
	return deg;
}



float chartonum(char a[10], char l) {
	float x = 0;
	int i, j;
	int temp;
	if (l == 'n') { //g for longitude
		j = 4;
	}
	else {
		j = 3;
	}


	for (i = 0; i < 10; i++) {
		if (a[i] == '.') {
			i++;
		}
		temp = a[i] - '0';
		//x += x ;
		x += (temp * pow(10, (j)));
		j--;
	}
	x = mintodeg(x);
	return(x);
}

float distance(float x, float y) {
	float d = sqrt((x* x) + (y* y));
	return(d);
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

		int i, j;

		char arr[7], arr1[26];
		char arrN[9], arrE[10];

		char ggp[] = { 'G','P','G','L','L','A' };
		char m;

		m = uart1_read();

		if (m == '$') {
			m = uart1_read();

			for (i = 0; i < 6; i++) {
				arr[i] = uart1_read();
				if (arr[i] == ggp[i] & i == 5) {

					for (i = 0; i < 25; i++) {
						arr[i] = uart1_read();
					}

					for (j = 0; j < 8; j++)
					{
						arrN[j] = arr[i + 1];
					}
					for (j = 0; j < 9; j++)
					{
						arrE[j] = arr1[i + 16];
					}




				}
				else {
					break;
				}
			}
		}


	


	*N = chartonum(arrN, 'n');
	*E = chartonum(arrE, 'e');

}







void LCD_init(void)
{

	`SYSCTL_RCGCGPIO_R |= (1 << 1); /* Enable Clock to GPIOB */
	GPIO_PORTB_DIR_R |= 0xFF; /* Set GPIOB all pins a digital output pins */
	GPIO_PORTB_DEN_R |= 0xFF; /* Declare GPIOB pins as digital pins */

	LCD_Cmd(Set5x7FontSize);  /* select 5x7 font size and 2 rows of LCD */
	LCD_Cmd(Function_set_4bit); /* Select 4-bit Mode of LCD */
	LCD_Cmd(moveCursorRight); /* shift cursor right */
	LCD_Cmd(clear_display); /* clear whatever is written on display */
	LCD_Cmd(cursorBlink);  /* Enable Display and cursor blinking */

}


void LCD_Cmd(unsigned char command)
{
	LCD_Write_Nibble(command & 0xF0, 0);   /* Write upper nibble to LCD */
	LCD_Write_Nibble(command << 4, 0);     /* Write lower nibble to LCD */

	if (command < 4)
		delay_ms(2);         /* 2ms delay for commands 1 and 2 */
	else
		delay_us(40);        /* 40us delay for other commands */
}


void LCD_Write_Nibble(unsigned char data, unsigned char control)
{

	data &= 0xF0;       /* Extract upper nibble for data */
	control &= 0x0F;    /* Extract lower nibble for control */
	GPIO_PORTB_DATA_R = data | control;       /* Set RS and R/W to zero for write operation */
	GPIO_PORTB_DATA_R = data | control | EN;  /* Provide Pulse to Enable pin to perform wite operation */
	delay_us(0);
	GPIO_PORTB_DATA_R = data; /*Send data */
	GPIO_PORTB_DATA_R = 0; /* stop writing data to LCD */
}





void LCD_Write_Char(unsigned char data)
{
	LCD_Write_Nibble(data & 0xF0, RS);    /* Write upper nibble to LCD and RS = 1 to write data */
	LCD_Write_Nibble(data << 4, RS);      /* Write lower nibble to LCD and RS = 1 to write data */
	delay_us(40);
}



void LCD_String(char str) /*Send string to LCD function * /
{
	int i;
	for (i = 0; str[i] != 0; i++)  /* Send each char of string till the NULL */
	{
		LCD_Write_Char(str[i]);  /* Call LCD data write */
	}
}

/* Mili seconds delay function */

void delay_ms(int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3180; j++)
		{
		}
}

/* Micro seconds delay function */
void delay_us(int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3; j++)
		{
		}

}
