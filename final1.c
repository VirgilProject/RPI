#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<wiringPi.h>
#include<mcp23017.h>
#include<string.h>

//Global Variables
int input, output, preset, volume;

void pinSetup(){
	int inputs[9] = {0,2,3,4,5,6,7,10,11};
	int outputs[23] = {12,13,14,15,16,21,22,23,25,26,27,28,30,31,100,101,102,103,104,105,106,107,108};
	for(int x = 0; x < 9; x++)
		pinMode(inputs[x], INPUT);
	for(int x = 0; x < 23; x++)
		pinMode(outputs[x], OUTPUT);
}

void setInLed(){
	int inLED[5] = {100,101,102};
	for(int x = 1; x < 4; x++){
		if(x == input)
			digitalWrite(inLED[x-1], HIGH);
		else
			digitalWrite(inLED[x-1], LOW);
	}
}

void setOutLed(){
	int outLED[4] = {105,106,107,108};
	for(int x = 1; x < 5; x++){
		if(x == output)
			digitalWrite(outLED[x-1], HIGH);
		else
			digitalWrite(outLED[x-1], LOW);
	}
}

void set7SD(){
	int set[10][7] = {
		{0,0,0,0,0,0,1},
		{1,0,0,1,1,1,1},
		{0,0,1,0,0,1,0},
		{0,0,0,0,1,1,0},
		{1,0,0,1,1,0,0},
		{0,1,0,0,1,0,0},
		{0,1,0,0,0,0,0},
		{0,0,0,1,1,1,1},
		{0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0}
	};
	int ones7SD[7] = {12,13,14,15,16,21,22};
	int tens7SD[7] = {23,25,26,27,28,30,31};
	for(int x = 0; x < 7; x++){
		digitalWrite(ones7SD[x], set[preset % 10][x]);
		digitalWrite(tens7SD[x], set[preset / 10][x]);
	}
}

void readPreset(){
	char filename[7];
	snprintf(filename, sizeof(filename), "%d", preset);
	strcat(filename,".txt");
	FILE *fp; 
	fp = fopen(filename,"r");
	fscanf(fp, "%d", &input);
	fscanf(fp, "%d", &output);
	fscanf(fp, "%d", &volume);
	fclose(fp);
	setInLed();
	setOutLed();
	setInOut();
}

void storePreset(){
	char filename[7];
	snprintf(filename, sizeof(filename), "%d", preset);
	strcat(filename,".txt");
	FILE *fp; 
	fp = fopen(filename,"w");
	fprintf(fp, "%d %d %d", input, output, volume);
	fclose(fp);
}

void setInOut(){
	/*	char pcsc[48];
		int in, out;
		in = input / 2;
		out = output / 2;
		system("python virgilSwitch.py 0x5");
		system("python virgilSwitch.py 0x25");
		system("python virgilSwitch.py 0x45");
		system("python virgilSwitch.py 0x65");
		strcpy(pcsc, "python virgilSwitch.py 0x");
		switch(out){
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
		switch(in){
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
		system("python virgilSwitch.py 0x05");
		system("python virgilSwitch.py 0x25");
		system("python virgilSwitch.py 0x45");
		system("python virgilSwitch.py 0x65");
	//	printf("%s\n", pcsc);
	system(pcsc);
	if(out != 1)
	system("python virgilSwitch.py 0x5");
	*/
	if(volume == 4){
		if(input == 1){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x20 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x0 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x20 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x0 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x20 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x0 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x40 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x0 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x60 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x0 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 2){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x21 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x21 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x41 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x61 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 3){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x22 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x2 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x22 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x2 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x42 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x2 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x62 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x2 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
	}
	else if(volume == 3){
		if(input == 1){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x28 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x8 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x28 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x8 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x48 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x8 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x68 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x8 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 2){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x29 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x9 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x29 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x9 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x49 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x9 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x69 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x9 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 3){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x2A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0xA 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x2A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0xA 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x4A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0xA 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x6A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0xA 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
	}
	else if(volume == 2){
		if(input == 1){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x30 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x10 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x30 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x10 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x50 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x10 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x70 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x10 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 2){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x31 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x11 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x31 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x11 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x51 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x11 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x71 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x11 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 3){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x32 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x12 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x32 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x12 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x52 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x12 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x72 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x12 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
	}
	else if(volume == 1){
		if(input == 1){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x38 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x18 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x38 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x18 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x58 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x18 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x78 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x18 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 2){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x39 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x19 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x39 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x19 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x59 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x19 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x79 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x19 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
		else if(input == 3){
			if(output == 1){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x3A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x43 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 2){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x3A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x63 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4c");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 3){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x5A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x65 0x4d");
			}
			else if(output == 4){
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x7A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x1A 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x45 0x4d");
				system("python ../home/pi/SDTesting/virgilSwitch.py 0x25 0x4d");
			}
		}
	}

}

PI_THREAD (inDE){
	printf("Thread inDE created successfully \n");
	int pin1, pin2, old1, old2;
	int value = 2;
	pin1 = old1 = digitalRead(0);
	pin2 = old2 = digitalRead(2);
	while(1)
	{
		pin1 = digitalRead(0);
		pin2 = digitalRead(2);
		if(pin1 != old1){
			if(pin1 == pin2 && value != 2){
				value--;
				//				if(input % 2 == 0){
				//					setInLed();					
				//					setInOut();
				//				}
//				printf("Input: %d \n", input);
			}
			else if(pin1 != pin2 && value != 6){
				value++;
				//				if(input % 2 == 0){
				//					setInOut();
				//					setInLed();
				//				}
//				printf("Input: %d \n", input);
			}
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && value != 6){
				value++;
				//				if(input % 2 == 0){
				//					setInLed();
				//					setInOut();
				//				}
				//				printf("Input: %d \n", input);
			}
			else if(pin1 != pin2 && value !=2){
				value--;
				//				if(input % 2 == 0){
				//					setInLed();
				//					setInOut();
				//				}
//				printf("Input: %d \n", input);
			}
		}
		old1 = pin1;
		old2 = pin2;
		if(value / 2 != input){
			input = value / 2;
			setInLed();
			setInOut();
			printf("Input: %d \n", input);
		}
	}
}

PI_THREAD (outDE){
	printf("Thread outDE created successfully \n");
	int pin1, pin2, old1, old2;
	int value = 2;
	pin1 = old1 = digitalRead(3);
	pin2 = old2 = digitalRead(4);
	while(1)
	{
		pin1 = digitalRead(3);
		pin2 = digitalRead(4);
		if(pin1 != old1){
			if(pin1 == pin2 && value != 2){
				value--;
				//				if(output % 2 == 0){
				//					setOutLed();
				//					setInOut();
				//				}
				//				printf("Output: %d \n", output);
			}
			else if(pin1 != pin2 && value != 8){
				value++;
				//				if(output % 2 ==0){
				//					setOutLed();
				//					setInOut();
				//				}
//				printf("Output: %d \n", output);
			}
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && value != 8){
				value++;
				//				if(output % 2 == 0){
				//					setOutLed();
				//					setInOut();
				//				}
//				printf("Output: %d \n", output);
			}
			else if(pin1 != pin2 && value != 2){
				value--;
				//				if(output % 2 == 0){
				//					setOutLed();
				//					setInOut();
				//				}
//				printf("Output: %d \n", output);
			}
		}
		old1 = pin1;
		old2 = pin2;
		if(value / 2 != output){
			output = value / 2;
			setOutLed();
			setInOut();
			printf("Output: %d \n", output);
		}
	}
}

PI_THREAD (presetDE){
	printf("Thread presetDE created successfully \n");
	int pin1, pin2, old1, old2;
	int value = 2;
	pin1 = old1 = digitalRead(5);
	pin2 = old2 = digitalRead(6);
	while(1)
	{
		pin1 = digitalRead(5);
		pin2 = digitalRead(6);
		if(pin1 != old1){
			if(pin1 == pin2 && value != 2){
				value--;
				//			set7SD();
//				printf("Preset: %d \n", preset);
			}
			else if(pin1 != pin2 && value != 198){
				value++;
				//			set7SD();
//				printf("Preset: %d \n", preset);

			}
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && value != 198){
				value++;
				//			set7SD();
//				printf("Preset: %d \n", preset);

			}
			else if(pin1 != pin2 && value !=2){
				value--;
				//			set7SD();
//				printf("Preset: %d \n", preset);
			}
		}
		old1 = pin1;
		old2 = pin2;
		if(preset != value / 2){
			preset = value / 2;
			set7SD();
			printf("Preset: %d \n", preset);
		}
	}
}

PI_THREAD (volumeDE){
	printf("Thread volumeDE created successfully \n");
	int pin1, pin2, old1, old2;
	pin1 = old1 = digitalRead(7);
	pin2 = old2 = digitalRead(10);
	int value = 2;
	while(1)
	{
		pin1 = digitalRead(7);
		pin2 = digitalRead(10);
		if(pin1 != old1){
			if(pin1 == pin2 && value != 2){
				value--;
//				printf("Volume: %d \n", volume);
			}
			else if(pin1 != pin2 && value != 8){
				value++;
//				printf("Volume: %d \n", volume);
			}
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && value != 8){
				value++;
//				printf("Volume: %d \n", volume);
			}
			else if(pin1 != pin2 && value != 2){
				value--;
//				printf("Volume: %d \n", volume);
			}
		}
		old1 = pin1;
		old2 = pin2;
		if(volume != value / 2){
			volume = value / 2;
			setInOut();
			printf("Volume: %d \n", volume);
		}
	}
}

PI_THREAD (button){
	printf("Thread button created successfully \n");
	int start, end, el, x;
	x = 0;
	while(1){
		el = 0;
		while(x == 0){
			x = digitalRead(11);
		}
		start = time(NULL);
		while(x == 1){
			end = time(NULL);
			el = end - start;
			if(el > 2){
				storePreset();
				while(x == 1)
					x = digitalRead(11);
				break;
			}
			x = digitalRead(11);
		}
		if(el < 3)
int main(void){
	wiringPiSetup();
	mcp23017Setup(100,0x20);
	pinSetup();
	int oldIn, oldOut, oldPre, oldVol;
	oldIn = input = 1;
	oldOut = output = 1;
	oldPre = preset = 1;
	oldVol = volume = 1;
	piThreadCreate(inDE);
	piThreadCreate(outDE);
	piThreadCreate(presetDE);
	piThreadCreate(volumeDE);
	piThreadCreate(button);
	setInLed();
	setOutLed();
	set7SD();
	setInOut();
	while(1){
/*		if(input != oldIn || output != oldOut){
			setInLed();
			setOutLed();
			setInOut();
		}
		if(preset != oldPre){
			set7SD();
		}
		if(volume != oldVol){
			setInOut();
		}
		oldIn = input;
		oldOut = output;
		oldVol = volume;
		oldPre = preset;
*/	}
}
