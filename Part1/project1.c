#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#define length 1000000

//method to search for keys
int search(int num[]){
	FILE *fpr;

	fpr = fopen("results.txt", "w");
	
	int max = 0;
	int i = 0;

	clock_t begin = clock();
	while(i < length-1){
		if(num[i] > max){
			max = num[i];
		}
		i++;
	}
	fprintf(fpr, "Max='%d'\n\n", max);
	
	i = 0;

	while(i < length){
		if(num[i] == -50){
			fprintf(fpr, "Hi! I am process 1 and I found the hidden key in position A['%d']\n", i);
		}
		i++;	
	}
	
	clock_t end = clock();
	double time = (double)(end-begin);
	printf("Time to run %f\n", time);

	fclose(fpr);

	return 0;
}	

int main(){
	FILE *fp;
	
	//Random integer text file generator
	fp = fopen("test.txt", "w");

	for(int i = 0; i < length; i++){
		//End file with null terminator
		if(i == length-1){
			fprintf(fp, "%c", '\0');
			continue;
		}
		//insert keys
		if(i == length/4 || i == length/2 || i == (length * 3)/4){
			fprintf(fp, "%d\n", -50);
			continue;
		}
		//random number generator
		fprintf(fp, "%d\n", rand() % length);
	}

	fclose(fp);
	
	//Problem2 code
		
	fp = fopen("test.txt", "r");
	
	//put text file integers into array
	int num[length+1];
	for(int k = 0; k < length; k++){
		fscanf(fp, "%d", &num[k]);
	}
	num[length] = '\0';
	
	//search method for the keys
	search(num);

	fclose(fp);

	
	return 0;
}
