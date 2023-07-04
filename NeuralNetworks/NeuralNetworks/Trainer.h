#ifndef TRAINER_H
#define TRAINER_H

#include <vector>
using namespace std;

class Trainer {
protected:
public:
	// Constructor
	Trainer() {};
	// Destructor
	~Trainer() {};
	// Functions
	vector<double> feedForward(double* inputs);
	void backPropagation(double* inputs, double* outputs);
	double sigmoid(const double v);
	double sigmoidDerivative(const double v);
	vector<double> calcError(double* outputs);
	void train();
	void test();
	int validate(int counter);
	void resizeVectors();
	// Variables

	vector<double> sigmoid_nodes;
	vector<double> sigmoid_output;
	vector<vector<double>> prev_delta_weight_nodes;    
	vector<vector<double>> prev_delta_weight_outputs;  
	vector<double> sum_of_errors;
	double averageRMSE_Validation = 0;

};

#endif // TRAINER_H