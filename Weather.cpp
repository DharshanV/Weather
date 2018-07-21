#include "Weather.h"
Weather::Weather() {
	_city = "New York";
	_country = "US";
	initilizeRequest(_city, _country);
}

Weather::Weather(std::string city) {
	_city = city;
	initilizeRequest(_city, "-1");
}

Weather::Weather(std::string city, std::string country) {
	_city = city;
	_country = country;
	initilizeRequest(_city,_country);
}

Weather::Weather(int ZIP_Code, std::string country) {
	_ZIP_Code = ZIP_Code;
	_country = country;
	initilizeRequest(std::to_string(_ZIP_Code), _country);
}

Weather::Weather(int city_ID) {
	cityIDSearch = true;
	_city_ID = city_ID;
	initilizeRequest(std::to_string(_city_ID), "-1");
}

Weather::Weather(double latitude, double longitude) {
	coordSearch = true;
	_latitude = latitude;
	_lonitude = longitude;
	initilizeRequest(deleteZeros(std::to_string(_latitude)), 
		deleteZeros(std::to_string(_lonitude)));
}

void Weather::initilizeRequest(std::string first,std::string second) {
	URI += "/data/2.5/weather?";
	if (coordSearch) {
		URI += "lat=";
		URI += first;
		URI += "&lon=";
		URI += second;
	}
	else if (cityIDSearch) {
		URI += "id=";
		URI += first;
	}
	else {
		URI += "q=";
		URI += first;
		if (second != "-1") {
			URI += ",";
			URI += second;
		}
	}
	URI += "&forecast?id=524901&APPID=";
	URI += mAPI_ID;
	coordSearch, cityIDSearch = false;
}

string Weather::deleteZeros(string modifyString) {
	string newString = modifyString;
	int x = newString.length() - 1;
	int deleteLength = 0;
	while (newString.at(x) == '0') {
		newString.erase(x);
		x--;
	}
	return newString;
}

void Weather::startRequest() {
	hostLink = "http://api.openweathermap.org";
	request.setMethod(sf::Http::Request::Get);
	request.setUri(URI);
	http.setHost(hostLink);
	response = http.sendRequest(request);
	cout << hostLink << URI << endl;
	if (response.getStatus() == sf::Http::Response::Ok) {
		responseString = response.getBody();
		storeRequested(responseString);
	}
	else {
		std::cout << "Error code " << response.getStatus() << std::endl;
	}
}

void Weather::storeRequested(std::string HTML_String) {
	modHTMLString(HTML_String);
	int i, j = 0;
	for (int x = 0; x < MAX_SIZE; x++) {
		i = HTML_String.find(information[x][0]);
		if (i != string::npos) {
			j = i + information[x][0].length() + 2;
			while (HTML_String.at(j) != ',') {
				information[x][1] += HTML_String.at(j);
				j++;
			}
		}
		i, j = 0;
	}
}

void Weather::modHTMLString(std::string& HTML_String) {
	for (int i = 0; i < HTML_String.length(); i++) {
		switch (HTML_String.at(i)) {
		case '\"':
			HTML_String.replace(i, 1, " ");
			break;
		case '}':
			HTML_String.erase(HTML_String.begin() + i);
			break;
		}
	}
	HTML_String += ',';
}

void Weather::clearSearch() {
	_latitude = 0;
	_lonitude = 0;
	_city_ID = 0;
	_ZIP_Code = 0;
	_city = "";
	_country = "";
	coordSearch = false;
	cityIDSearch = false;
	URI.clear();
}

std::string Weather::getResponseString() const {
	return responseString;
}

void Weather::setCity(std::string city) {
	clearSearch();
	_city = city;
	initilizeRequest(city, "-1");
}

void Weather::setCoord(double lat, double lon) {
	clearSearch();
	_latitude = lat;
	_lonitude = lon;
	coordSearch = true;
	initilizeRequest(deleteZeros(std::to_string(_latitude)), deleteZeros(std::to_string(_lonitude)));
}

string Weather::getInfo(int index) {
	return information[index][1];
}

void Weather::printAll() {
	for (int x = 0; x < MAX_SIZE; x++) {
		cout << information[x][0] << " : " << information[x][1] << endl;
	}
}
