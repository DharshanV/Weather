#include <SFML\Network.hpp>
#include <iostream>
#include <fstream>
#include "Weather.h"
using namespace std;
int main() {
	Weather weather("New York");
	weather.setCoord(34.0522, -118.2437);
	weather.startRequest();
	cout << weather.getResponseString() << endl;

	cout << weather.getInfo(weather.lat) << endl;
	cout << weather.getInfo(weather.lon) << endl;
	cout << weather.getInfo(weather.temp) << endl;
	cout << weather.getInfo(weather.pressure) << endl;
	return 0;
}
