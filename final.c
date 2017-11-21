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
	int inLED[5] = {100,101,102,103,104};
	int value = input / 2;
	for(int x = 1; x < 6; x++){
		if(x == value)
			digitalWrite(inLED[x-1], HIGH);
		else
			digitalWrite(inLED[x-1], LOW);
	}
}

void setOutLed(){
	int outLED[4] = {105,106,107,108};
	int value = output / 2;
	for(int x = 1; x < 5; x++){
		if(x == value)
			digitalWrite(outLED[x-1], HIGH);
		else
			digitalWrite(outLED[x-1], LOW);
	}
}

void set7SD(){
	int value = preset / 2;
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
		digitalWrite(ones7SD[x], set[value % 10][x]);
		digitalWrite(tens7SD[x], set[value / 10][x]);
	}
}

void readPreset(){
	int pre = preset / 2;
	char filename[7];
	snprintf(filename, sizeof(filename), "%d", pre);
	strcat(filename,".txt");
	FILE *fp; 
	fp = fopen(filename,"r");
	fscanf(fp, "%d", &input);
	fscanf(fp, "%d", &output);
	fscanf(fp, "%d", &volume);
	fclose(fp);
	setInLed();
	setOutLed();
}

void storePreset(){
	int pre = preset / 2;
	char filename[7];
	snprintf(filename, sizeof(filename), "%d", pre);
	strcat(filename,".txt");
	FILE *fp; 
	fp = fopen(filename,"w");
	fprintf(fp, "%d %d %d", input, output, volume);
	fclose(fp);
}

void setInOut(){
	char pcsc[48];
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
}

PI_THREAD (inDE){
	printf("Thread inDE created successfully \n");
	int pin1, pin2, old1, old2;
	pin1 = old1 = digitalRead(0);
	pin2 = old2 = digitalRead(2);
	while(1)
	{
		pin1 = digitalRead(0);
		pin2 = digitalRead(2);
		if(pin1 != old1){
			if(pin1 == pin2 && input != 2){
				input--;
				if(input % 2 == 0){
					setInLed();					
					setInOut();
				}
//				printf("Input: %d \n", input);
		}
			else if(pin1 != pin2 && input != 8){
				input++;
				if(input % 2 == 0){
					setInOut();
					setInLed();
				}
//				printf("Input: %d \n", input);
		}
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && input != 8){
				input++;
				if(input % 2 == 0){
					setInLed();
					setInOut();
				}
//				printf("Input: %d \n", input);
		}
			else if(pin1 != pin2 && input !=2){
				input--;
				if(input % 2 == 0){
					setInLed();
					setInOut();
				}
//				printf("Input: %d \n", input);
		}
		}
		old1 = pin1;
		old2 = pin2;
	}
}

PI_THREAD (outDE){
	printf("Thread outDE created successfully \n");
	int pin1, pin2, old1, old2;
	pin1 = old1 = digitalRead(3);
	pin2 = old2 = digitalRead(4);
	while(1)
	{
		pin1 = digitalRead(3);
		pin2 = digitalRead(4);
		if(pin1 != old1){
			if(pin1 == pin2 && output != 2){
				output--;
				if(output % 2 == 0){
					setOutLed();
					setInOut();
				}
//				printf("Output: %d \n", output);
			}
			else if(pin1 != pin2 && output != 8){
				output++;
				if(output % 2 ==0){
					setOutLed();
					setInOut();
				}
//				printf("Output: %d \n", output);
			}
	}
		else if(pin2 != old2){
			if(pin1 == pin2 && output != 8){
				output++;
				if(output % 2 == 0){
					setOutLed();
					setInOut();
				}
//				printf("Output: %d \n", output);
			}
			else if(pin1 != pin2 && output != 2){
				output--;
				if(output % 2 == 0){
					setOutLed();
					setInOut();
				}
//				printf("Output: %d \n", output);
			}
		}
		old1 = pin1;
		old2 = pin2;
	}
}

PI_THREAD (presetDE){
	printf("Thread presetDE created successfully \n");
	int pin1, pin2, old1, old2;
	pin1 = old1 = digitalRead(5);
	pin2 = old2 = digitalRead(6);
	while(1)
	{
		pin1 = digitalRead(5);
		pin2 = digitalRead(6);
		if(pin1 != old1){
			if(pin1 == pin2 && preset != 2){
				preset--;
				set7SD();
				printf("Preset: %d \n", preset);
			}
			else if(pin1 != pin2 && preset != 198){
				preset++;
				set7SD();
				printf("Preset: %d \n", preset);

			}
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && preset != 198){
				preset++;
				set7SD();
				printf("Preset: %d \n", preset);

			}
			else if(pin1 != pin2 && preset !=2){
				preset--;
				set7SD();
				printf("Preset: %d \n", preset);
			}
		}
		old1 = pin1;
		old2 = pin2;
	}
}

PI_THREAD (volumeDE){
	printf("Thread volumeDE created successfully \n");
	int pin1, pin2, old1, old2;
	pin1 = old1 = digitalRead(7);
	pin2 = old2 = digitalRead(10);
	while(1)
	{
		pin1 = digitalRead(7);
		pin2 = digitalRead(10);
		if(pin1 != old1){
			if(pin1 == pin2 && volume != 2){
				volume--;
				printf("Volume: %d \n", volume);
			}
			else if(pin1 != pin2 && volume != 64){
				volume++;
				printf("Volume: %d \n", volume);
			}
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && volume != 10){
				volume++;
				printf("Volume: %d \n", volume);
			}
			else if(pin1 != pin2 && volume != 64){
				volume--;
				printf("Volume: %d \n", volume);
			}
		}
		old1 = pin1;
		old2 = pin2;
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
		       readPreset();
	}
}	
			

int main(void){
	wiringPiSetup();
	mcp23017Setup(100,0x20);
	pinSetup();
//	readPreset();
	int oldIn, oldOut, oldPre, oldVol;
	oldIn = input = 2;
	oldOut = output = 2;
	oldPre = preset = 2;
	oldVol = volume = 2;
	piThreadCreate(inDE);
	piThreadCreate(outDE);
//	piThreadCreate(presetDE);
//	piThreadCreate(volumeDE);
//	piThreadCreate(button);
	setInLed();
	setOutLed();
	set7SD();
	while(1){
/*		if(input != oldIn){
			setInLed();
			printf("input : %d \n", input);
			//I2C
			//I2S
		}
		if(output != oldOut){
			setOutLed();
			//I2C
			//I2S
		}
		if(preset != oldPre){
			set7SD();
		}
		if(volume != oldVol){
			//I2C
		}
		oldIn = input;
		oldOut = output;
		oldVol = volume;
		oldPre = preset;
*/	}
}
