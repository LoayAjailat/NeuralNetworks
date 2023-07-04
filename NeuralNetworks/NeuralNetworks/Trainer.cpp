#include "Trainer.h"
#include "Model.h"
#include "DataManager.h"

#include <iostream>
#include <vector>
#include <numeric>  // for std::inner_product

#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
extern Model model;
extern DataManager dataManager;

// TODO: The Neural Network should accept sigmoid function as its activation and do the calculations accordingly rather than hardcode it all

ofstream RMSE_Training("");

double Trainer::sigmoid(const double v){
    return 1.0 / (1.0 + exp(-model.lambda * v));
}

double Trainer::sigmoidDerivative(const double v){
    return model.lambda * sigmoid(v) * (1 - sigmoid(v));
}

void Trainer::resizeVectors(){
    sigmoid_nodes.resize(model.nodes); // Resize the vector to have size 'nodes'
    sigmoid_output.resize(model.outputs); // Resize the vector to have size 'outputs'
    sum_of_errors.resize(model.outputs);
    prev_delta_weight_nodes.resize(model.inputs);
	prev_delta_weight_outputs.resize(model.outputs);
    for (int i = 0; i < model.inputs; ++i) {
        prev_delta_weight_nodes[i].resize(model.nodes);
    }
    for (int i = 0; i < model.outputs; ++i) {
        prev_delta_weight_outputs[i].resize(model.nodes);
    }
}

vector<double> Trainer::feedForward(double* inputs) {
    vector<double> v_nodes;
	vector<double> v_output;
    v_nodes.resize(model.nodes); // Resize the vector to have size 'nodes'
    v_output.resize(model.outputs); // Resize the vector to have size 'outputs'

    // sigmoid_nodes.resize(model.nodes); // Resize the vector to have size 'nodes'
    // sigmoid_output.resize(model.outputs); // Resize the vector to have size 'outputs'
    
    // cout << "-- Feed forward: " << endl;

    //Find h (sigmoid) = weight of hidden neurons
	for (int n = 0; n < model.nodes; n++)
	{
	    //Find v initial between the inputs and the hidden neurons
		for (int i = 0; i < model.inputs; i++)
		{
            // cout << "V = " << inputs[i] << " * " << model.weights_nodes[i][n] << " = ";
			v_nodes[n] += inputs[i] * model.weights_nodes[i][n];
            // cout << v_nodes[n] << endl;
		}
        sigmoid_nodes[n] = sigmoid(v_nodes[n]); 
		// cout << "Sigmoid = " << sigmoid_nodes[n] << endl;
	}
	sigmoid_nodes[0] = 1; //This is the hidden bias weight

	//Find final h (sigmoid) = output
	for (int o = 0; o < model.outputs; o++)
	{
	    //Find v final between the hidden neurons and the outputs
		for (int n = 0; n < model.nodes; n++)
		{
            // cout << "V = " << sigmoid_nodes[n] << " * " << model.weights_outputs[o][n] << " = ";
			v_output[o] += sigmoid_nodes[n] * model.weights_outputs[o][n];
            // cout << v_output[o] << endl;
		}
		sigmoid_output[o] = sigmoid(v_output[o]);
        // cout << "Sigmoid = " << sigmoid_nodes[o];
	}
    return sigmoid_output;
}

vector<double> Trainer::calcError(double* outputs){
	vector<double> errors;
    errors.resize(model.outputs);
    

	for (int j = 0; j < model.outputs; j++)
	{
		errors[j] = outputs[j] - sigmoid_output[j];
        sum_of_errors[j] += pow(errors[j], 2);
	}
	return errors;
} 

void Trainer::backPropagation(double* inputs, double* outputs) {
	vector<double> local_gradient_nodes(model.outputs); // Direction is output to nodes
	vector<double> local_gradient_inputs(model.nodes); // Direction is nodes to inputs
	vector<double> local_weight(model.nodes);
	vector<vector<double>> delta_weight_nodes(model.inputs, vector<double>(model.nodes)); // Direction is input to nodes
	vector<vector<double>> delta_weight_outputs(model.outputs, vector<double>(model.nodes)); // Direction is nodes to outputs
    
    // cout << "-- Back propagation: " << endl;
   
    // Compute the error
	vector<double> errors = calcError(outputs);

	//Find local gradients of the nodes from outputs to hidden neurons
	for (int o = 0; o < model.outputs; o++)
	{
        // local gradient = errors * sigmoidDerivative
		local_gradient_nodes[o] = sigmoidDerivative(sigmoid_output[o]) * errors[o];
	}

	//Local weight
	for (int n = 0; n < model.nodes; n++) {
		for (int o = 0; o < model.outputs; o++)
		{
			local_weight[n] += local_gradient_nodes[o] * model.weights_outputs[o][n];
		}
	}

	//Find local gradients of nodes from hidden neuros to inputs
	for (int n = 0; n < model.nodes; n++)
	{
		local_gradient_inputs[n] = sigmoidDerivative(sigmoid_nodes[n]) * (local_weight[n]);
	}

	//Update weights of nodes from hidden neurons to outputs
	for (int o = 0; o < model.outputs; o++)
	{
		for (int n = 0; n < model.nodes; n++)
		{
            delta_weight_outputs[o][n] = model.eta * local_gradient_nodes[o] * sigmoid_nodes[n];
            model.weights_outputs[o][n] += delta_weight_outputs[o][n] + model.alpha * prev_delta_weight_outputs[o][n];
            prev_delta_weight_outputs[o][n] = delta_weight_outputs[o][n];

			// delta_weight_nodes[o][n] = model.eta * local_gradient_nodes[o] * sigmoid_nodes[n];
			// model.weights_nodes[o][n] += delta_weight_nodes[o][n] + model.alpha * prev_delta_weight_nodes[o][n];
			
            // prev_delta_weight_nodes[o][n] = delta_weight_nodes[o][n];
		}
	}

	//Update weights of nodes from hidden neurons to inputs
	for (int i = 0; i < model.inputs; i++)
	{
		for (int n = 0; n < model.nodes; n++)
		{
			delta_weight_nodes[i][n] = model.eta * local_gradient_inputs[n] * inputs[i];
			model.weights_nodes[i][n] += delta_weight_nodes[i][n] + model.alpha * prev_delta_weight_nodes[i][n];
			
            prev_delta_weight_nodes[i][n] = delta_weight_nodes[i][n];
		}
	}
}

void Trainer::train() {
    // vector<double> sum_of_errors;
    // sum_of_errors.resize(model.outputs);		
    sum_of_errors.assign(sum_of_errors.size(), 0.0); // Reset all elements to zero
    
    double inputs[3], outputs[2];
    inputs[0] = 1;
    for (size_t i = 0; i < dataManager.train_sensor1.size(); ++i) {
        inputs[1] = dataManager.train_sensor1[i];
        inputs[2] = dataManager.train_sensor2[i];
        outputs[0] = dataManager.train_speed_left[i];
        outputs[1] = dataManager.train_speed_right[i];
        
        feedForward(inputs);
        backPropagation(inputs, outputs);
    }

    vector<double> RMSE;
    RMSE.resize(model.outputs);
    //Calculate the RMSE
	for (int m = 0; m < model.outputs; m++)
	{
		RMSE[m] = sqrt(sum_of_errors[m]) / dataManager.train_sensor1.size();
	}
	cout << "RMSE: " << (RMSE[0] + RMSE[1]) / 2 << endl;
    RMSE_Training << (RMSE[0] + RMSE[1]) / 2;
}

void Trainer::test() {
    sum_of_errors.assign(sum_of_errors.size(), 0.0); // Reset all elements to zero

    double inputs[3], outputs[2];
    inputs[0] = 1;
    for (size_t i = 0; i < dataManager.test_sensor1.size(); ++i) {
        inputs[1] = dataManager.test_sensor1[i];
        inputs[2] = dataManager.test_sensor2[i];
        outputs[0] = dataManager.test_speed_left[i];
        outputs[1] = dataManager.test_speed_right[i];
        feedForward(inputs);
        calcError(outputs);
    }

    vector<double> RMSE;
    RMSE.resize(model.outputs);
    //Calculate the RMSE
	for (int m = 0; m < model.outputs; m++)
	{
		RMSE[m] = sqrt(sum_of_errors[m]) / dataManager.test_sensor1.size();
	}
	cout << "RMSE: " << (RMSE[0] + RMSE[1]) / 2 << endl;
    RMSE_Training << "," << (RMSE[0] + RMSE[1]) / 2;
	RMSE_Training << "\n";
}

int Trainer::validate(int counter) {
    sum_of_errors.assign(sum_of_errors.size(), 0.0); // Reset all elements to zero

    double inputs[3], outputs[2];
    inputs[0] = 1;
    for (size_t i = 0; i < dataManager.validate_sensor1.size(); ++i) {
        inputs[1] = dataManager.validate_sensor1[i];
        inputs[2] = dataManager.validate_sensor2[i];
        outputs[0] = dataManager.validate_speed_left[i];
        outputs[1] = dataManager.validate_speed_right[i];
        feedForward(inputs);
        calcError(outputs);
    }

    vector<double> RMSE;
    RMSE.resize(model.outputs);
    //Calculate the RMSE
	for (int m = 0; m < model.outputs; m++)
	{
		RMSE[m] = sqrt(sum_of_errors[m]) / dataManager.validate_sensor1.size();
	}
    double prevRMSE = averageRMSE_Validation;
    averageRMSE_Validation = (RMSE[0] + RMSE[1]) / 2;
	cout << "RMSE: " << (RMSE[0] + RMSE[1]) / 2 << endl;
    if ((averageRMSE_Validation > prevRMSE) && counter != 0) {
		return 1;
	}
    RMSE_Training << "," << (RMSE[0] + RMSE[1]) / 2;
    return 0;
}