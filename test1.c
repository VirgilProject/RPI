#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
	int pre = 50;
	char filename[7];
	int in, out, vol;
	snprintf(filename, 10, "%d", pre);
	strcat(filename,".txt");
	printf("%s\n", filename);
	in = 10;
	out = 4;
	vol = 16;
	FILE *fp; 
	fp = fopen(filename,"w");
	fprintf(fp, "%d %d %d", in, out, vol);
	fclose(fp);
	return 0;
}
	
