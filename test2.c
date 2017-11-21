#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
	int input, output;
	input = atoi(argv[1]);
	output = atoi(argv[2]);
	char pcsc[48];
	system("python virgilSwitch.py 0x5");
	system("python virgilSwitch.py 0x25");
	system("python virgilSwitch.py 0x45");
	system("python virgilSwitch.py 0x65");
	strcpy(pcsc, "python virgilSwitch.py 0x");
	switch(output){
		case 1:
			break;
		case 2:
			strcat(pcsc, "2");
			break;
		case 3:
			strcat(pcsc, "4");
			break;
		case 4:
			strcat(pcsc, "6");
	}
	switch(input){
		case 1:
			strcat(pcsc, "0");
			break;
		case 2:
			strcat(pcsc, "1");
			break;
		case 3:
			strcat(pcsc, "2");
			break;
		case 4:
			strcat(pcsc, "3");
	}	
	printf("%s\n", pcsc);
	system(pcsc);	
	return 0;
}
