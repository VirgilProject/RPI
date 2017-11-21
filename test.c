#include<stdio.h>
#include<stdlib.h>

int main(void){
	int in, out, vol;
	FILE *fp; 
	fp = fopen("1.txt","r");
	fscanf(fp, "%d", &in);
	fscanf(fp, "%d", &out);
	fscanf(fp, "%d", &vol);
	fclose(fp);
	printf("%d \n %d \n %d \n", in, out, vol);
	return 0;
}
	
