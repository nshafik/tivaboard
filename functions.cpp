#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

float mintodeg(float x) {
	int xint = x/100;
	float deg = x / 100 - xint;
	deg = deg / 60;
	return deg;
}

float mult(float x, float y) {
	return (x * y);
}
float ChartoInt(char a[10], char l) {
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

	char a[10] = { '1','3','1','4','.','2','3','4','5','7' };
	float x= ChartoInt(a, 'g');
	printf("%f", x);

}
