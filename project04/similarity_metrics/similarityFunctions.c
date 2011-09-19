#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double Euclidean(double a[], double b[], int size){
	double squareSum = 0;
	int i;
	for(i = 0; i < size; i ++){
		squareSum = squareSum + (a[i] - b[i])*(a[i] - b[i]);
	}
	double dist = sqrt(squareSum);
	dist = 1/(1+dist);
	return dist;
}
double SMC(double a[], double b[], int size){
	int i;
	double count = 0.0;
	for(i = 0; i < size; i ++){
		if(a[i] == b[i]){count++;}
	}
	return count / size;
}
double Jaccard(double a[], double b[], int size){
	int i;
	double count = 0.0;
	for(i = 0; i < size; i ++){
		if(b[i] != 0&&a[i] != 0){count++;}
	}
	return count / size;
}
double Pearson(double a[], double b[], int size){
	if(size == 0){return 0;}
	int i;
	double aMean, bMean, cov, asdv, bsdv, val;
	for(i = 0; i < size; i ++){
		aMean += a[i];
		bMean += b[i];
	}
	aMean /= size;
	bMean /= size;
	for(i = 0; i < size; i ++){
		cov += (a[i] - aMean)*(b[i] - bMean);
		asdv += (a[i] - aMean)*(a[i] - aMean);
		bsdv += (b[i] - bMean)*(b[i] - bMean);
	}
	cov /= (size - 1);
	asdv = sqrt(asdv/(size-1));
	bsdv = sqrt(bsdv/(size-1));
	val = cov / asdv / bsdv;
	return val;
}
double Cosine(double a[], double b[], int size){
	int i;
	double val, n = 0, d1 = 0, d2 = 0;
	for(i = 0; i < size; i ++){
		n += a[i] * b[i];
		d1 += a[i] * a[i];
		d2 += b[i] * b[i];
	}
	d1 = sqrt(d1);
	d2 = sqrt(d2);
	val = n/(d1*d2);
	return val;
}
int test(){
	int size = 6;
	double a[6] = {1,0,1,0,1,0};
	double b[6] = {1,1,0,0,1,0};
	if(Euclidean(a,b,size) != 1/(sqrt(3)+1)){return 0;}
	if(SMC(a,b,size) != .5){return 0;}
	if(Jaccard(a,b,size) != .25){return 0;}
	if(Pearson(a,b,size) != 0){return 0;}
	if(Cosine(a,b,size) != 1/sqrt(2)/2){return 0;}
	return 1;
}
int main(){
	//printf %lf is for double
	int size = 6;
	double a[6] = {1,0,1,0,1,0};
	double b[6] = {1,1,0,0,1,0};
	if(!test){printf("The test failed");}
	printf("The arrays to be passed into the functions\nA        B\n");
	int i;
	for(i = 0; i < size; i ++){
		printf("%lf %lf\n", a[i], b[i]);
	}
	printf("The functions responses\n");
	printf("Euclidean distance: %lf\n", Euclidean(a,b,size));
	printf("Simple Matching Coefficient: %lf\n", SMC(a,b,size));
	printf("Jaccard Similarity: %lf\n", Jaccard(a,b,size));
	printf("Pearson Correlation Coefficient: %lf\n", Pearson(a,b,size));
	printf("Cosine Similarity: %lf\n", Cosine(a,b,size));
	return 0;
}


