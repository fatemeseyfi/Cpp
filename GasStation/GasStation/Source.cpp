#include <iostream>
using namespace std;
#include <vector>

int path(vector<int> gas, vector<int> cost, int n) {

	int fuelLeft = 0;
	bool ok = true;

	int stationIndex;

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {

			// move forward
			stationIndex = (i + j) % n;

			fuelLeft = fuelLeft + gas[stationIndex];
			fuelLeft = fuelLeft - cost[stationIndex];

			if (fuelLeft < 0) {
				fuelLeft = 0;
				ok = false;
				break;
			}

		}

		if (ok) {
			return i;
		}
		else {
			ok = true;
		}
	}
	return -1;
}

vector<int> inputGas(int n) {
	vector<int> stations;
	stations.resize(n);
	int temp;
	for (int i = 0; i < n; i++) {

		cout << endl << "enter gas amount for station " << i << endl;
		cin >> temp;
		while (temp < 0) {
			cout << endl << "invalid amount" << endl;
			cin >> temp;
		}
		stations[i] = temp;
	}
	return stations;
}

vector<int> inputCost(int n) {
	vector<int> pathCost;
	pathCost.resize(n);
	int temp;
	for (int i = 0; i < n; i++) {
		cout << endl << "enter gas amount needed for path " << i << endl;
		cin >> temp;
		while (temp < 0) {
			cout << endl << "invalid amount" << endl;
			cin >> temp;
		}
		pathCost[i] = temp;
	}
	return pathCost;
}

int main() {
	int n;
	cout << "enter num of stations: " << endl;
	cin >> n;

	vector<int> stations;
	stations.resize(n);
	stations = inputGas(n);

	vector<int> pathCost;
	pathCost.resize(n);
	pathCost = inputCost(n);

	if (path(stations, pathCost, n) == -1) {
		cout << "there is no valid path";
	}
	else {
		cout << "first proper gas station is : ";
		cout<<path(stations, pathCost, n);

	}

}