#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
	int pre = 1;
	char filename[100] = "../home/pi/SDTesting/";
	char preName[10];
	int in, out, vol;
	snprintf(preName, sizeof(preName), "%d", pre);
	strcat(filename, preName);
	strcat(filename,".txt");
	printf("%s\n", filename);
	in = 1;
	out = 2;
	vol = 3;
	FILE *fp; 
	fp = fopen(filename,"w");
	fprintf(fp, "%d %d %d", in, out, vol);
	fclose(fp);
	return 0;
}
	
