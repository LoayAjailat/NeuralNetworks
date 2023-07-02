#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "DataManager.h"
#include "Initialiser.h"
#include "Model.h"
#include "Trainer.h"

using namespace std;

DataManager dataManager;
Model model;
Trainer trainer;

void initialise() {
    dataManager.loadData();
    dataManager.normaliseData();
    dataManager.shuffleData();
    dataManager.splitData();

    // NOTE: These variables should ideally be read from a config text file
    model.setShape(9, 3, 2);
    model.setHyperParameters(0.7, 0.8, 0.05);

    model.generateWeights();
	return;
}
int main() {
    // Initialiser initialiser;
    // initialiser.initialise();
    initialise();
    return 1;
}