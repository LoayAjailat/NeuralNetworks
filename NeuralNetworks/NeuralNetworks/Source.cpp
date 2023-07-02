#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "DataManager.h"
#include "Initialiser.h"
#include "ModelConfig.h"
#include "Trainer.h"

using namespace std;

int main() {
    Initialiser initialiser;
    initialiser.initialise();
    return 1;
}