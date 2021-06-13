#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
SystemInit(){}

float lon[100];
float lat[100];


void redtoarr(float g, float t) {
	int i;
	for (i = 0; i < 100 ; i++) { 
		lon[i] = g;   //basically baoulo hena yakhod el reading mn el gps w yhotha fi array el longitude aw el latitude
		lat[i] = t;   // hnakhod el g wel t de men el input function bta3et el gps, 
		              //ne3adiha ala chartoint we mintodeg we nhotaha hena
	}
	
}

float mintodeg(float x) {
	float minx = x / 100;
	int xint = minx;
	float deg = minx - xint;
	deg = deg / 60 + minx;
	printf("%f", deg);
	return deg;
}

float mult(float x, float y) {
	return (x * y);
}
float chartoint(char a[10], char l) {
	float x = 0;
	int i,j;
	int temp;
	if (l == 'g') { //g for longitude
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
		x += mult(temp, pow(10, (j)));
		j--;
	}
	return(x);
}

float distance(float x, float y) {
	int d = sqrt(( mult(x , x) + mult( y , y)));
	return(d);
}
int main() {
	float y;
	char a[10] = { '1','3','1','4','.','2','3','4','5','7' };
	float x= chartoint(a, 'l');
	//y = mintodeg(x);
	//printf("%f", y);


}