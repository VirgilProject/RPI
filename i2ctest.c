#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<stdio.h>

int main(void){
	wiringPiI2CSetup(0x4d);
	int x;
	x = wiringPiI2CWrite(0x4d, 0x20);
	if(x < 0)
		printf("error sending data %d \n", x);
	while(1)
	{

	}
	return 0;
}
