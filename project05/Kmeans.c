#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>

double Euclidean(double a[], double b[], int size){
	double squareSum = 0;
	int i;
	for(i = 0; i < size; i ++){
		squareSum = squareSum + (a[i] - b[i])*(a[i] - b[i]);
	}
	double dist = sqrt(squareSum);
	return dist;
}

double* Kmeans(double data[][150], int k, int datapoints, int count, double groups[]){
	int i;
	for(i=0; i<=count;i ++){
		groups[i] = 0;
	}
	if( k < 1 || k > 150){ return groups; }
	if( k == 1 ){
		for (i = 0; i < count; i ++){
			groups[i] = 1;
		}
		return groups;
	}
	double k_points[datapoints][k];
	for (i = 0; i < k ; i ++){
		int j;
		for( j = 0 ; j < datapoints; j ++){
			k_points[i][j] = data[i][j];
		}
	}



	return groups;	
}

void test(){
	FILE *file;
	file = fopen("iris.txt","r");
	//data[0-3] are data points data[4] is it's number data[5] is it's cluster
	double data[6][150];
	char s[30];
	int count = 0;
	while(fscanf(file,"%lf,%lf,%lf,%lf,%s",&data[0][count],
		&data[1][count],&data[2][count],&data[3][count], s) != EOF){
		data[4][count] = count;
		data[5][count] = 0;
		count ++;
	}
	fclose(file);
	double temp[150];
	double * groups = Kmeans(data,3,4,count,temp);

	
	
}

int main(){
	test();
	return 0;
}
