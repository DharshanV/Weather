# Weather
A C++ real time weather class by using SFML.

-Required files-

SFML\Network.hpp

sfml-network.lib

sfml-network-d.lib

Properly include the SFML files above and the network files. It should work.
The class uses API offered by OpenWeatherMap.
By default the class uses my API key, you can change it under class .h file.
Also by default, the weather class uses New York, US at the start.

You can change the location of search by 5 ways.
1. Weather weather(); //New York, US.
2. Weather weather("{City}"); //any city, if its valid.
3. Weather weather("{City}","{Country}"); //enhance the search.
4. Weather weather({City ID}); //a int value of the city ID.
5. Weather weather({latitude},{longitude}); //a double value for lat and lon.

Up until this point, you have only set the values. To send the values for 
request process, its best to call "weather.startRequest();" after 
modifing the search.

For example:

Weather weather("New York");

weather.setCoord(34.0522, -118.2437); //changes from New York to Los Angles.

{....}

weather.startRequest();

After the request (if its valid) you can gather weather information.

1. weather.getInfo(weather.lat); // returns 34.0522

2. weather.getInfo(weather.lon); // returns -118.2437

3. weather.getInfo(weather.temp); //returns 300.98 in kelvin at the time of writing this.

...

and many others.
