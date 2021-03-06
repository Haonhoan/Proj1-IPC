#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define length 100000
//X is size of list each process is assigned
#define X 1000000

//method to search for keys
int search(int num[], FILE *fpn, FILE *fpr){
	int count = 0; 
	int check = length;  

        if (length < X) {
            	count++;
            	check = check / 2;
        } 
	else {
        	while (check > X) {
            		count++;
            		check = check / 2;
		}
        }

        int numberPro = (int)pow(2, count) - 1;
        int k ;
        int c ;
        int rootNode = getpid();
        int pid;
        int child[numberPro];

        for (k = 0 ; k < numberPro ; k++) {

        	child[k] = fork();
            	if (child[k] == 0) {
              		int ind = (getpid() % (numberPro)) ;
              		fprintf(fpn,"Hi I am process %d and my parent is %d\n",getpid(), getppid());

                	for (c= ind * check ; c< (check * (ind + 1)) ; c++) {
                   		if (num[c] == -50) {
                    			fprintf(fpr, "Hi I am process %d and I found the hidden key in position A[%d]\n", getpid(), c);
                    			exit(c - (ind * c));
                   		}
                	}
                	exit(-1);
            	}
        }

        if (length % 2 == 0) {
            	for (c = (length - c) ; c < length ; c++) {
                	if (num[c] == -50) {
                  		fprintf(fpr,"Hi I am process %d and I found the hidden key in position A[%d]\n", getpid(), c);
                  		return c;
                	}
            	}
        } 
	else {
		for (c = (length - check - (count - 1)); c < length ; c++) {
                	if (num[c] == -50) {
				fprintf(fpr, "Hi I am process %d and I found the hidden key in position A[%d]\n", getpid(), c);
                    		return c;
                	}
            	}
	}
	
	for (k = 0; k < numberPro; k++) {
		int status ;
		waitpid(child[k], &status, 0);

         	if (WIFEXITED(status)) {

                	if (WEXITSTATUS(status) <= X) {
                    		return WEXITSTATUS(status) + (check * (child[k] % numberPro));
                	}
            	}
        }

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
	
	//put text file integers into numay
	int num[length+1];
	for(int k = 0; k < length; k++){
		fscanf(fp, "%d", &num[k]);
	}
	num[length] = '\0';
	fclose(fp);
	//search method for the keys
	
	FILE *fpr, *fpn, *result;
	
	fpn = fopen("results0.txt", "w");
	fpr = fopen("results1.txt", "w");
	
	clock_t begin = clock();

	search(num, fpn, fpr);

	int i, max = 0;

	while(i < length-1){
		if(num[i] > max){
			max = num[i];
		}
		i++;
	}
	fprintf(fpn, "Max='%d'\n\n", max);

	clock_t end = clock();
	double time = (double)(end-begin);
	printf("Time to run %f\n", time);

	fclose(fpn);
	fclose(fpr);
	
	fpn = fopen("results0.txt", "r");
	fpr = fopen("results1.txt", "r");
	result = fopen("result.txt", "w");

	char z;

	while((z = fgetc(fpn)) != EOF){
		fputc(z, result);
	}
	while((z = fgetc(fpr)) != EOF){
		fputc(z, result);
	}

	fclose(fpn);
	fclose(fpr);
	fclose(result);

	remove("results0.txt");
	remove("results1.txt");

	
	return 0;
}
