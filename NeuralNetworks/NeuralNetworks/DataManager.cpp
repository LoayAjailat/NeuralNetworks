#include "DataManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>  // For random number generation

using namespace std;

void DataManager::LoadData() {
    ifstream file;
    string filename;
    cout << "Please enter a string: ";
    getline(cin, filename);
    file.open(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        int column = 0;

        while (getline(iss, token, ',')) {
            switch (column) {
            case 0:
                sensor1.push_back(stod(token));
                break;
            case 1:
                sensor2.push_back(stod(token));
                break;
            case 2:
                speed_left.push_back(stod(token));
                break;
            case 3:
                speed_right.push_back(stod(token));
                break;
            }
            column++;
        }
    }
    file.close();

    // Processed data
    cout << "Number of values read: " << sensor1.size() << endl;
    return;
}

void DataManager::NormalizeData() {
    int max_distance = 5000;
    int max_speed = 300;
    int minValue = 0;

    // Normalize the values in the vectors
    for (size_t i = 0; i < sensor1.size(); ++i) {
        sensor1[i] = (sensor1[i] - minValue) / (max_distance - minValue);
        sensor2[i] = (sensor2[i] - minValue) / (max_distance - minValue);

        speed_left[i] = (speed_left[i] - minValue) / (max_speed - minValue);
        speed_right[i] = (speed_right[i] - minValue) / (max_speed - minValue);
    }

    cout << "Data normalised." << endl;
}


void DataManager::ShuffleData() {
    // Create a random number generator
    random_device rd;
    mt19937 generator(rd());

    // Shuffle the vectors using the random number generator
    shuffle(sensor1.begin(), sensor1.end(), generator);
    shuffle(sensor2.begin(), sensor2.end(), generator);
    shuffle(speed_left.begin(), speed_left.end(), generator);
    shuffle(speed_right.begin(), speed_right.end(), generator);

    cout << "Data shuffled." << endl;
}

void DataManager::SplitData() {
    // Calculate the sizes of the training, testing, and validation sets
    size_t totalSize = sensor1.size();
    size_t trainingSize = static_cast<size_t>(totalSize * 0.7);
    size_t testingSize = static_cast<size_t>(totalSize * 0.15);
    size_t validationSize = totalSize - trainingSize - testingSize;

    // Create new vectors for the training, testing, and validation sets
    vector<double> training_sensor1(sensor1.begin(), sensor1.begin() + trainingSize);
    vector<double> training_sensor2(sensor2.begin(), sensor2.begin() + trainingSize);
    vector<double> training_speed_left(speed_left.begin(), speed_left.begin() + trainingSize);
    vector<double> training_speed_right(speed_right.begin(), speed_right.begin() + trainingSize);

    vector<double> testing_sensor1(sensor1.begin() + trainingSize, sensor1.begin() + trainingSize + testingSize);
    vector<double> testing_sensor2(sensor2.begin() + trainingSize, sensor2.begin() + trainingSize + testingSize);
    vector<double> testing_speed_left(speed_left.begin() + trainingSize, speed_left.begin() + trainingSize + testingSize);
    vector<double> testing_speed_right(speed_right.begin() + trainingSize, speed_right.begin() + trainingSize + testingSize);

    vector<double> validation_sensor1(sensor1.begin() + trainingSize + testingSize, sensor1.end());
    vector<double> validation_sensor2(sensor2.begin() + trainingSize + testingSize, sensor2.end());
    vector<double> validation_speed_left(speed_left.begin() + trainingSize + testingSize, speed_left.end());
    vector<double> validation_speed_right(speed_right.begin() + trainingSize + testingSize, speed_right.end());

    // Print the sizes of the training, testing, and validation sets
    cout << "Training set size: " << trainingSize << endl;
    cout << "Testing set size: " << testingSize << endl;
    cout << "Validation set size: " << validationSize << endl;

    // Use the training, testing, and validation sets as needed
    // For example, you can assign them to member variables of the class or use them in other functions
    // E.g., this->training_sensor1 = training_sensor1; (if you have corresponding member variables)

    // Rest of your code...
}
