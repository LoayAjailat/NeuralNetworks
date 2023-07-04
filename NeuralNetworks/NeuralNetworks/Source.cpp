#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "DataManager.h"
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

    trainer.resizeVectors();

	return;
}
int main(int argc, char *argv[]) {
    initialise();

    int counter = 0;
    int epochTraining = 1000;
    int stopTraining = 0;

	for (int epoch = 0; (epoch < epochTraining) && stopTraining != 1; epoch++)
	{
		trainer.train();
		stopTraining = trainer.validate(counter);
        trainer.test();

		counter++;
		cout << "COUNTER: " << counter << "\n";
	}
   
    return 1;
}
