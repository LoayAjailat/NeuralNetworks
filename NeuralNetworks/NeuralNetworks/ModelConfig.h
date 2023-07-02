#ifndef MODELCONFIG_H
#define MODELCONFIG_H

class ModelConfig {
protected:
	// Shape
	int nodes, inputs, outputs;
	// Hyperparameters
	double lambda, eta, alpha;

public:
	// Constructor
	ModelConfig()
		: nodes(0), inputs(0), outputs(0), lambda(0.0), eta(0.0), alpha(0.0) {}
	// Destructor
	~ModelConfig() {}
	// Functions
	void setShape(int nodes, int inputs, int outputs);
	void setHyperParameters(double lambda, double eta, double alpha);

};

#endif // MODELCONFIG_H