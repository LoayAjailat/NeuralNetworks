#include "ModelConfig.h"

#include <iostream>
#include <random>

using namespace std;

void ModelConfig::setShape(int nodes, int inputs, int outputs) {
	this->nodes = nodes;
	this->inputs = inputs;
	this->outputs = outputs;

	weights_nodes.resize(this->inputs); // Resize the vector to have 'inputs' number of rows
	weights_outputs.resize(this->outputs); // Resize the vector to have 'outputs' number of rows

    // Resize each row to have 'nodes' number of columns
    for (int i = 0; i < this->inputs; ++i) {
        weights_nodes[i].resize(this->nodes);
    }
	for (int i = 0; i < this->outputs; ++i) {
        weights_outputs[i].resize(this->nodes);
    }

	cout << "Model shape set." << endl;
}

void ModelConfig::setHyperParameters(double lambda, double eta, double alpha) {
	this->lambda = lambda;
	this->eta = eta;
	this->alpha = alpha;
	cout << "Hyperparameters set." << endl;
	cout << "Lambda: " << this->lambda << ", Eta:" << this->eta << ", Alpha: " << this->alpha << endl;
}

double ModelConfig::randomNumberGenerator(double a, double b){
	random_device rd; // Obtain a random seed from the hardware
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<double> dis(a, b); // Define the range

    return dis(gen); // Generate and return a random number
}

void ModelConfig::generateWeights(){
	// Fill the weights vector with random values
    for (int i = 0; i < this->inputs; ++i) {
        for (int j = 0; j < this->nodes; ++j) {
            weights_nodes[i][j] = randomNumberGenerator(0.000001, 1.0);
        }
    }
	for (int i = 0; i < this->outputs; ++i) {
        for (int j = 0; j < this->nodes; ++j) {
            weights_outputs[i][j] = randomNumberGenerator(0.000001, 1.0);
        }
    }
}