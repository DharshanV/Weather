#pragma once
#include <SFML\Network.hpp>
#include <iostream>
using namespace std;
const int MAX_SIZE = 27;
const std::string mAPI_ID = "42f0392b596e390244350db0a06c836f";

class Weather {
public:
	Weather();
	Weather(std::string city);
	Weather(std::string city, std::string country);
	Weather(int ZIP_Code, std::string country);
	Weather(int city_ID);
	Weather(double latitude, double longitude);

	void startRequest();
	std::string getResponseString()const;
	void setCity(std::string city);
	void setCoord(double lat, double lon);
	string getInfo(int index);
	void printAll();
	enum lookUpIndex {
		cod,message,lat,lon,
		main,description,icon,
		base,temp,pressure,
		humidity,temp_min,
		temp_max,visibility,
		speed,deg,all,dt,type,
		id,message2,country,sunrise,
		sunset,id2,name,cod2
	};
private:
	sf::Http http;
	sf::Http::Request request;
	sf::Http::Response response;
	std::string information[MAX_SIZE][2] = {
	{"cod",""},
	{"message",""},
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
	std::string _city, _country;
	std::string responseString;
	std::string hostLink;
	std::string URI;

	double _latitude, _lonitude = 0;
	int _city_ID, _ZIP_Code = 0;
	bool coordSearch = false;
	bool cityIDSearch = false;
	int searchIndex = 0;

	void initilizeRequest(std::string first, std::string second);
	void storeRequested(std::string HTML_String);
	string deleteZeros(string modifyString);
	void modHTMLString(std::string& HTML_String);
	void clearSearch();
};