#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<wiringPi.h>

int main(void){
	wiringPiSetup();
	pinMode(0, INPUT);
	int start, end, el, x;
	x = 0;
	while(1){
		el = 0;
		while(x == 0){
			x = digitalRead(0);
		}
		start = time(NULL);
		while(x == 1){
			end = time(NULL);
			el = end - start;
			if(el > 2){
				printf("storePreset()\n");
				while(x == 1)
					x = digitalRead(0);
				break;
			}
			x = digitalRead(0);
		}
		if(el < 3)
		       printf("readPreset()\n");
	}
}	

