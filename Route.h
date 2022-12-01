/*
* @author Fredrick Kiarie Njoki
*/

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include<unordered_map>
#include <vector>
#include <sstream>


using namespace std;

/*
* route class
*/

class Route {
public:
    Route() {};
    Route(string ac, string sa, int stops) {
        this->airlineCode = ac;
        this->srcAirportCode = sa;
        this->stops = stops;
    }
    string airlineCode;
    string srcAirportCode;
    string destAirportCode;
    int stops;


    string getSrcAirportCode(){return srcAirportCode;}
    string getDestAirportCode(){return destAirportCode;}
    string getAirlineCode(){return airlineCode;}
    int getStops(){return stops;}

   unordered_map<string, vector<Route>> routemethod();

};
