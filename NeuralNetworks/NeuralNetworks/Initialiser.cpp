#include "DataManager.h"
#include "Initialiser.h"
#include "ModelConfig.h"

void Initialiser::Initialise() {
    DataManager dataManager;
    dataManager.LoadData();
    dataManager.NormalizeData();
    dataManager.ShuffleData();
    dataManager.SplitData();

    ModelConfig modelConfig;
    // NOTE: These variables should ideally be read from a config text file
    modelConfig.setShape(9, 3, 2);
    modelConfig.setHyperParameters(0.7, 0.8, 0.05);
	return;
}