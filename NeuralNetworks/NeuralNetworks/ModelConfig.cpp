#include "ModelConfig.h"

#include <iostream>

using namespace std;

void ModelConfig::setShape(int nodes, int inputs, int outputs) {
	this->nodes = nodes;
	this->inputs = inputs;
	this->outputs = outputs;
	cout << "Model shape set." << endl;
}

void ModelConfig::setHyperParameters(double lambda, double eta, double alpha) {
	this->lambda = lambda;
	this->eta = eta;
	this->alpha = alpha;
	cout << "Hyperparameters set." << endl;
	cout << "Lambda: " << this->lambda << ", Eta:" << this->eta << ", Alpha: " << this->alpha << endl;

}