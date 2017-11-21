#include<stdio.h>
#include<wiringPi.h>

int main (void)
{
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

	wiringPiSetup();
	
	for(int x = 0; x < 14; x++){
		pinMode(x, OUTPUT);
	}
		
	int input;
/*	while(1){
		scanf("%2d", &input);
*/
	for(input = 99; input > -1; input--)
	{
		for(int x = 0; x < 7; x++){
			digitalWrite(x, set[input % 10][x]);
		}
		for(int x = 0; x < 7; x++){
			digitalWrite(x + 7, set[input / 10][x]);
		}
		delay(500);
	}

	return 0;
}
