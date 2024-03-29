#ifndef MODEL_H
#define MODEL_H

#include <vector>

using namespace std;

class Model {
protected:
public:
	// Constructor
	Model()
		: nodes(0), inputs(0), outputs(0), lambda(0.0), eta(0.0), alpha(0.0) {}
		// TODO: MUST assert alpha between 0 and 1
	// Destructor
	~Model() {}
	// Functions
	void setShape(int nodes, int inputs, int outputs);
	void setHyperParameters(double lambda, double eta, double alpha);
	double randomNumberGenerator(double a, double b);
	void generateWeights();

    vector<vector<double>> weights_nodes;
    vector<vector<double>> weights_outputs;

	// NOTE: These variables should be available to other files
	// Shape
	int nodes, inputs, outputs;
	// Hyperparameters
	double lambda, eta, alpha;
};

#endif // MODEL_H