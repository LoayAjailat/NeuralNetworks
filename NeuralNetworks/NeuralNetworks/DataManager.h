#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>

using namespace std;

class DataManager {
protected:
public:
	// Constructor
	DataManager() {};
	// Destructor
	~DataManager() {};
	// Functions
	void LoadData();
	void NormalizeData();
	void ShuffleData();

	void SplitData();

	// TODO: Encapsulate the important ones?
	// TODO: Shouldn't these specific variables be in a different file so that the DataManager is OOP?
	vector<double> sensor1;
	vector<double> sensor2;
	vector<double> speed_left;
	vector<double> speed_right;

	vector<double> train_sensor1;
	vector<double> train_sensor2;
	vector<double> train_speed_left;
	vector<double> train_speed_right;

	vector<double> test_sensor1;
	vector<double> test_sensor2;
	vector<double> test_speed_left;
	vector<double> test_speed_right;

	vector<double> validate_sensor1;
	vector<double> validate_sensor2;
	vector<double> validate_speed_left;
	vector<double> validate_speed_right;

};

#endif  // DATAMANAGER_H

