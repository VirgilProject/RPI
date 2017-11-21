#include<stdio.h>
#include<wiringPi.h>
#include<mcp23017.h>

#define Read1 100
#define Read2 101

PI_THREAD (DEread)
{
	int pin1, pin2, old1, old2;
	int value = 0;
	pin1 = old1 = digitalRead(Read1);
	pin2 = old2 = digitalRead(Read2);
	while(1)
	{
		pin1 = digitalRead(Read1);
		pin2 = digitalRead(Read2);
		if(pin1 != old1){
			if(pin1 == pin2)
				value--;
			else if(pin1 != pin2)
				value++;
			printf("Value: %d \n", value);
		}
		else if(pin2 != old2){
			if(pin1 == pin2)
				value++;
			else if(pin1 != pin2)
				value--;
			printf("Value: %d \n", value);
		}
		old1 = pin1;
		old2 = pin2;
	}
}

int main (void)
{
	wiringPiSetup();
	mcp23017Setup(100, 0x20);
	pinMode(Read1, INPUT);
	pinMode(Read2, INPUT);
	piThreadCreate(DEread);
	while(1){
	
	}
}
