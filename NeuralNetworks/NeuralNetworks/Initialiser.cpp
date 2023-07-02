#include "DataManager.h"
#include "Initialiser.h"
#include "ModelConfig.h"

void Initialiser::initialise() {
    DataManager dataManager;
    dataManager.loadData();
    dataManager.normaliseData();
    dataManager.shuffleData();
    dataManager.splitData();

    ModelConfig modelConfig;
    // NOTE: These variables should ideally be read from a config text file
    modelConfig.setShape(9, 3, 2);
    modelConfig.setHyperParameters(0.7, 0.8, 0.05);
    modelConfig.generateWeights();
	return;
}