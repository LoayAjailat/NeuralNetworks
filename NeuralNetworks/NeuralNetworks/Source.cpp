#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "DataManager.h"
#include "Initialiser.h"
#include "ModelConfig.h"

using namespace std;

int main() {
    Initialiser initialiser;
    initialiser.Initialise();
    return 1;
}