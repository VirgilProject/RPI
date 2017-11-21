#include<stdio.h>
#include<wiringPi.h>

#define Read1 0
#define Read2 1

int main (void)
{
	wiringPiSetup();
	pinMode(Read1, INPUT);
	pinMode(Read2, INPUT);
	int pin1, pin2, old1, old2;
	pin1 = old1 = digitalRead(Read1);
	pin2 = old2 = digitalRead(Read2);
	while(1)
	{
		pin1 = digitalRead(Read1);
		pin2 = digitalRead(Read2);
		if(pin1 != old1 || pin2 != old2){
			printf("pin1: %d, pin2: %d\n", pin1, pin2);
		}
		old1 = pin1;
		old2 = pin2;
	}
}
