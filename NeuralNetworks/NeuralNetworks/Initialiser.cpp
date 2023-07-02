#include "DataManager.h"
#include "Initialiser.h"
#include "Model.h"

void Initialiser::initialise() {
    DataManager dataManager;
    dataManager.loadData();
    dataManager.normaliseData();
    dataManager.shuffleData();
    dataManager.splitData();

    Model model;
    // NOTE: These variables should ideally be read from a config text file
    model.setShape(9, 3, 2);
    model.setHyperParameters(0.7, 0.8, 0.05);
    model.generateWeights();
	return;
}