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

void trash() {
	ifstream inputFile;
	string htmlOutput;
	string indexName[25][2] = {
		//errors here
	{ "lon","" },
	{ "lat","" },
	{ "main","" },
	{ "description","" },
	{ "icon","" },
	{ "base","" },
	{ "temp","" },
	{ "pressure","" },
	{ "humidity","" },
	{ "temp_min","" },
	{ "temp_max","" },
	{ "visibility","" },
	{ "speed","" },
	{ "deg","" },
	{ "all","" },
	{ "dt","" },
	{ "type","" },
	{ "id","" },
	{ "message","" },
	{ "country","" },
	{ "sunrise","" },
	{ "sunset","" },
	{ "id","" },
	{ "name","" },
	{ "cod","" },
	};
	inputFile.open("weather.txt");
	if (inputFile.is_open()) {
		getline(inputFile, htmlOutput);
		inputFile.close();
	}
	cout << htmlOutput << endl;
	for (int i = 0; i < htmlOutput.length(); i++) {
		switch (htmlOutput.at(i)) {
		case '\"':
			htmlOutput.replace(i, 1, " ");
			break;
		case '}':
			htmlOutput.erase(htmlOutput.begin() + i);
			break;
		}
	}
	htmlOutput += ',';
	cout << endl;
	cout << htmlOutput << endl;
	int i, j = 0;
	for (int x = 0; x < 25; x++) {
		i = htmlOutput.find(indexName[x][0]);
		if (i != string::npos) {
			j = i + indexName[x][0].length() + 2;
			while (htmlOutput.at(j) != ',') {
				indexName[x][1] += htmlOutput.at(j);
				j++;
			}
		}
		i, j = 0;
	}

	for (int x = 0; x < 25; x++) {
		cout << indexName[x][1] << endl;
	}
	//int i = 0;
	//i = htmlOutput.find("coord");
	//if (i != string::npos) {
	//	cout << i << endl;
	//	int x = i;
	//	while (htmlOutput.at(x) != ',') {
	//		cout << htmlOutput.at(x);
	//		x++;
	//	}
	//}
	//else {
	//	cout << "could not find" << endl;
	//}
	sf::Http http;
	sf::Http::Request request;
	sf::Http::Response response;
	string responseString;
	string copyString;
	request.setMethod(sf::Http::Request::Get);
	request.setUri("/data/2.5/weather?q=Arcadia,US&forecast?id=524901&APPID=42f0392b596e390244350db0a06c836f");
	http.setHost("http://api.openweathermap.org");
	response = http.sendRequest(request);

	if (response.getStatus() == sf::Http::Response::Ok) {
		cout << response.getBody() << endl;
	}
	else {
		cout << "request failed" << endl;
	}
}