#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<unordered_map>

using namespace std;

/*
* airport class
* country, city and airport code
*/
class Airport{
public:
    string country;
    string city;
    string airportCode;



    // constructor
    Airport() {}
    Airport(string airportCode, string country, string city) {
        this->airportCode = airportCode;
        this->country = country;
        this->city = city;
    }

};

unordered_map<string, Airport> airportCollections;

    // method for collecting data
unordered_map<string, Airport> collectData(){

    vector<string>words;
    vector<string> value;
    fstream airportsFile;

    airportsFile.open("airports.csv", ios::in);

    if (airportsFile.is_open()) {
        string line, word;
        while (getline(airportsFile, line)) {
            stringstream ss(line);
            while (getline(ss, word, ',')){
                words.push_back(word);
            }
            Airport myAirport(words.at(4), words.at(2), words.at(3));
            airportCollections[words.at(4)] = myAirport;
            words.clear();
        }
        cout << "Files Loaded";
    }

    return airportCollections;

}


