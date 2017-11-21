#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
	int input, output;
	input = 2;
	output = 3;
	char pcsc[48];
	strcat(pcsc, "python virgilSwitch.py 0x1");
	system(pcsc);
//	strcat(	
	return 0;
}
