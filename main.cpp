#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include "Airport.h"
#include "Route.h"

using namespace std;

/*
* function to create the input file
* with the start city and country, and destination city and country
*/
void createInputFile(){
    string city, city2, country, country2;
    cout << "Enter the start city and country <Enter>"; // taking the start city and country
    cin >> city >> country;
    cout << "Enter the destination city and country <Enter>";
    cin >> city2 >> country2;
    cout << "City is " << city << "and country is " << country << endl;
    string input = city + "-" + country + ".txt";
    fstream inputfile;
    inputfile.open(input, ios::out);
    if (inputfile.is_open()){
        inputfile << city << "," << country << endl;
        inputfile << city2 << "," << country2 << endl;
        inputfile.close();
    }
}


int main(){

    createInputFile();
    unordered_map<string, Airport> airports = collectData();
       // map iterator created
    // iterator pointing to start of map

    unordered_map<string, Airport>::iterator it = airports.begin();

    // Iterating over the map using Iterator till map end.
    while (it != airports.end())
    {
        // Accessing the key
        string word = it->first;
        // Accessing the value
        Airport count_ = it->second;
        cout << word << " " << count_.airportCode << endl;
        // iterator incremented to point next item
        it++;
    }
    cout << "Yes" << endl;

    //createInputFile();
    //Route newRoute;

    //newRoute.routemethod();
    return 0;
};
