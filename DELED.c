#include<stdio.h>
#include<wiringPi.h>

#define Read1 0
#define Read2 1

int main (void)
{
	wiringPiSetup();
	pinMode(Read1, INPUT);
	pinMode(Read2, INPUT);
	for(int x = 2; x < 6; x++)
		pinMode(x, OUTPUT);
	int pin1, pin2, old1, old2;
	int value = 2;
	pin1 = old1 = digitalRead(Read1);
	pin2 = old2 = digitalRead(Read2);
	digitalWrite(2, HIGH);
	while(1)
	{
		pin1 = digitalRead(Read1);
		pin2 = digitalRead(Read2);
		if(pin1 != old1){
			if(pin1 == pin2 && value != 2)
				value--;
			else if(pin1 != pin2 && value != 8)
				value++;
		}
		else if(pin2 != old2){
			if(pin1 == pin2 && value != 8)
				value++;
			else if(pin1 != pin2 && value !=2)
				value--;
			printf("Value: %d \n", value);
		}
		old1 = pin1;
		old2 = pin2;
		for(int x = 1; x < 5; x++){
			if(value / 2 == x)
				digitalWrite(x+1, HIGH);
			else
				digitalWrite(x+1, LOW);
		}

	}
}
