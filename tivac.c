#include "E:\Embedded/tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "math.h"


double PI = 3.142857;

void SystemInit() {}

void UART0_Init(void);
void UART1_Init();
void uart0_write(char c);
char uart1_read(void);

void getdata(double* N, double* E);
double chartonum(char a[10], char l);
double mintodeg(double x);

double difference(double i, double j);
double distance(double lat1, double lon1, double lat2, double lon2);
double deg2rad(double deg);

void LED_Init(void);
void LedFunc(double x);
void seg_Init(void);


















int main()
{

    double N[3] = { 0 };
    double E[3] = { 0 };
    int n = 0;
    double d = 0;
    
    UART0_Init();
    UART1_Init();
    while (1) {



        if (n == 2) {

            N[n] = N[n - 1];
            E[n] = E[n - 1];

            N[n - 1] = N[n - 2];
            E[n - 1] = E[n - 2];

            n--;

        }
        getdata(&N[n], &E[n]);
        d += distance(N[n], N[n - 1],E[n], E[n - 1]);
        LedFunc(d);
        n++;



    }

}
void seg_Init(void)
{
    SYSCTL_RCGCGPIO_R = 0x08;
    while ((SYSCTL_PRGPIO_R & 0X08) == 0) {};

    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R |= 0xFF;
    GPIO_PORTD_DEN_R |= 0XFF;
    GPIO_PORTD_DIR_R |= 0XFF;
    GPIO_PORTD_AMSEL_R &= ~0XFF;
    GPIO_PORTD_AFSEL_R &= ~0XFF;
    GPIO_PORTD_PCTL_R &= ~0XFFFFFFFF;
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



double difference(double i, double j) {
    double dif;
    if (i > j) {
        dif = i - j;
    }
    else {
        dif = j - i;
    }

    return dif;



}

double mintodeg(double x) {
    double minx = x / 100;
    int xint = minx;
    double deg = minx - xint;
    deg = deg / 60 + minx;
    return deg;
}


double distance(double lat1, double lon1, double lat2, double lon2) {

    double R = 6371; // Radius of the earth in km
    double dLat = deg2rad(difference(mintodeg(lat2), mintodeg(lat1)));  // deg2rad below
    double dLon = deg2rad(difference(mintodeg(lon2) , mintodeg(lon1)));
    double a =
        sin(dLat / 2) * sin(dLat / 2) +
        cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
        sin(dLon / 2) * sin(dLon / 2)
        ;
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c *1000; // Distance in m
    return d;
}

double deg2rad(double deg) {
    deg = mintodeg(deg);
    return deg * (PI / 180);
}














double chartonum(char a[10], char l) {
    double x = 0;
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
    SYSCTL_RCGCGPIO_R |= 0x3F;
    SYSCTL_RCGCUART_R |= 0x02;

    while ((SYSCTL_PRGPIO_R & 0x3F) == 0) {};

    GPIO_PORTB_DIR_R |= 0XFC;

    UART1_CTL_R &= ~0x00000001;
    UART1_IBRD_R = 104;
    UART1_FBRD_R = 11;
    UART1_LCRH_R = 0x00000070;
    UART1_CTL_R |= 0x00000301;

    GPIO_PORTB_DEN_R |= 0xFF;
    GPIO_PORTB_AMSEL_R &= ~0xFF;

    GPIO_PORTB_AFSEL_R |= 0x03;
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) + 0x00000011;



}




void LedFunc(double x) {

    if (x < 25) {
        GPIO_PORTF_DATA_R = 0X00;
        GPIO_PORTD_DATA_R |= 0X00; //sevenseg
    }
    else {
        GPIO_PORTD_DATA_R = 0X99; //middle sevenseg
        GPIO_PORTF_DATA_R = 0X02;
    }
}







void getdata(double* N, double* E) {

    int i, j;

    char arr[7], arr1[26];
    char arrN[9], arrE[10];

    char ggp[6] = { 'G','P','G','L','L','A' };
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
