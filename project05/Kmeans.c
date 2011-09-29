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
	return dist;
}

double* Kmeans(double data[][150], int k, int datapoints, int count, double groups[]){
	int i, j, l;
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
	//initalize the kpoint
	// datapoints is 4 for iris dataset
	double k_points[datapoints+1][k];
	srand((unsigned)time(NULL));
	for (i = 0; i < k ; i ++){
		for( j = 0 ; j < datapoints; j ++){
			l = rand()%count;
			k_points[j][i] = data[j][l];
		}
	}
	int rounds;
	for(rounds = 0; rounds < 100; rounds ++){
		// find which group each point belongs
		for(i = 0; i < count; i ++){
			double min_length = 10000;
			int k_val=0;
			for( j = 0; j < k; j ++){
				double a[datapoints], b[datapoints];
				for(l = 0; l < datapoints;l++){
					a[l] = data[l][i];
					b[l] = k_points[l][j];
				} 
				double length = Euclidean(a,b,4);
				if(length < min_length){
					min_length = length;
					k_val = j;
				}
			}
			data[datapoints+1][i] = k_val;	
		}
		// clear the datapoints in k_points
		for(i = 0; i < k ; i ++){
			for(j = 0 ; j <= datapoints; j++){
				k_points[j][i] = 0;
			}
		}
		//generate new k_points
		//add up all values assiciated with point k
		for(i = 0; i < count; i++){
			j = data[datapoints+1][i];
			for( l = 0; l < datapoints; l ++){
				k_points[l][j] += data[l][i];
			}
			k_points[datapoints][j] += 1;
		}
		//devide by the number of points
		for(j = 0; j < k; j++){
			for( l = 0; l < datapoints; l ++){
				if(k_points[datapoints][j] >= 1){k_points[l][j] /= k_points[datapoints][j];}
			}
		}
		//start over again
	}
	// translate into groups
	for(i = 0; i < count; i ++){
		groups[i] = data[datapoints +1][i];
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
	int i;
	for (i = 0 ; i < 150; i ++){
		printf("plant %d is in group %d\n", i ,(int) groups[i]);
	}
	printf("These are the results for my k-means clustering algorithm\nusing the iris dataset looking for 3 groups\ngroups are 0,1, and 2");
	return;
	
	
}

int main(){
	test();
	return 0;
}
