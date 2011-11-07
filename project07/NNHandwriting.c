#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define numb_hidden_nodes 2
#define numb_in_nodes 3
#define numb_out_nodes 3
#define numb_test 1
#define n (double) .05

typedef struct {
double step;
double hidden_weights[numb_hidden_nodes];
} input_node;

typedef struct {
double out_weights[numb_out_nodes];
double value;
double step;
double error;
} hidden_node;

typedef struct {
double value;
double step;
double error;
} output_node;

typedef struct {
	double exp_input[numb_in_nodes];
	double exp_output[numb_out_nodes];
} train_case;

input_node in_nodes[numb_in_nodes];
hidden_node hide_nodes[numb_hidden_nodes];
output_node out_nodes[numb_out_nodes];
train_case test[numb_test] = { { { 1.0, 0.25, -0.5}, { 1.0, -1.0, 0.0} } };


void create_weights(){
	int i, j, k;
	for( i = 0; i < numb_in_nodes; i ++){
		for(j = 0; j < numb_hidden_nodes; j ++){
			in_nodes[i].hidden_weights[j] = pow( -1.0, (rand() % 2)) * (rand() % 10 + 1) / 100.0 ;
		}
	}
	for( j = 0; j < numb_hidden_nodes; j ++){
		for(k = 0; k < numb_out_nodes; k ++){
			hide_nodes[j].out_weights[k] = pow( -1.0, (rand() % 2)) * (rand() % 10 + 1) / 100.0 ;
		}
	}
}

double sigmoid(double a){
	return (2.0/(1+exp(0-a)) - 1);
}

double sigmoid_d(double a){
	double b = sigmoid(a);
	return b*(1 - b);

}

void train(){
	create_weights();
	int i, j, k;
	double mse = 1, temp;
	do {
		//get what test to do
		int test_num = rand() % numb_test;
		//clear hidden and output node values
		for( j = 0; j < numb_hidden_nodes; j ++){
			hide_nodes[j].value = 0;
		}
		for( k = 0; k < numb_out_nodes; k ++){
			out_nodes[k].value = 0;
		}
		//feed forward to hidden layer
		for(i = 0; i < numb_in_nodes; i ++){
			in_nodes[i].step = test[test_num].exp_input[i];
			for( j = 0; j < numb_hidden_nodes; j ++){
				hide_nodes[j].value += in_nodes[i].hidden_weights[j] * in_nodes[i].step;
			}
		}
		//get hidden layer steps
		//feed forward to output layer
		for( j = 0; j < numb_hidden_nodes; j ++){
			hide_nodes[j].step = sigmoid(hide_nodes[j].value);
			for( k = 0; k < numb_out_nodes; k ++){
				out_nodes[k].value += hide_nodes[j].out_weights[k] * hide_nodes[j].step;
			}
		}
		//get output layer steps
		for( k = 0; k < numb_out_nodes; k ++){
			out_nodes[k].step = sigmoid(out_nodes[k].value);
		}

		//calc error in out_nodes
		for( k = 0; k < numb_out_nodes; k ++){
			out_nodes[k].error = test[test_num].exp_output[k] - out_nodes[k].step * sigmoid_d(out_nodes[k].step);	
		}
		//calc error in hide_nodes
		for( j = 0; j < numb_hidden_nodes; j ++){
				hide_nodes[j].error = 0;
			for( k = 0; k < numb_out_nodes; k ++){
				hide_nodes[j].error += hide_nodes[j].out_weights[k] * out_nodes[k].error;
			}
				hide_nodes[j].error *= sigmoid_d(hide_nodes[j].step);
		}
		//update the weights
		for( j = 0; j < numb_hidden_nodes; j ++){
			for( k = 0; k < numb_out_nodes; k ++){
				hide_nodes[j].out_weights[k] += n * out_nodes[k].error * hide_nodes[j].step;
			}
		}
		for ( i = 0; i < numb_in_nodes; i ++){
			for( j = 0; j < numb_hidden_nodes; j ++){
				in_nodes[i].hidden_weights[j] += n * hide_nodes[j].error * in_nodes[i].step;
			}
		}
		//calcuate mean standard error
		mse = 0.0;
		for (k = 0; k < numb_out_nodes; k ++){
			temp = test[test_num].exp_output[k] - out_nodes[k].step;
			mse += temp*temp;
		}
		mse /= (double) numb_in_nodes;
	// try again
	} while (mse > 0.001);
	return;
}

void printFinalOutput(){
	int i, j, k;
	//get what test to do
	int test_num = 0;
	//clear hidden and output node values
	for( j = 0; j < numb_hidden_nodes; j ++){
		hide_nodes[j].value = 0;
	}
	for( k = 0; k < numb_out_nodes; k ++){
		out_nodes[k].value = 0;
	}
	//feed forward to hidden layer
	for(i = 0; i < numb_in_nodes; i ++){
		in_nodes[i].step = test[test_num].exp_input[i];
		for( j = 0; j < numb_hidden_nodes; j ++){
			hide_nodes[j].value += in_nodes[i].hidden_weights[j] * in_nodes[i].step;
		}
	}
	//get hidden layer steps
	//feed forward to output layer
	for( j = 0; j < numb_hidden_nodes; j ++){
		hide_nodes[j].step = sigmoid(hide_nodes[j].value);
		for( k = 0; k < numb_out_nodes; k ++){
			out_nodes[k].value += hide_nodes[j].out_weights[k] * hide_nodes[j].step;
		}
	}
	//get output layer steps
	for( k = 0; k < numb_out_nodes; k ++){
		out_nodes[k].step = sigmoid(out_nodes[k].value);
	printf("output node: %d val: %lf\n", k, out_nodes[k].step);
	}
}

main(){
	srand ( time(NULL) );
	printf("training\n");
	train();
	printf("done training\n");
	printFinalOutput();
	return 0;
}
