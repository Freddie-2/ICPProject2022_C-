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

   routemethod(){

        unordered_map<string, vector<Route>> routeMap;

        vector<string>words;
        vector<Route> temp;
        fstream routesFile;

        routesFile.open("routes.csv", ios::in);

        if (routesFile.is_open()) {
            string line, word;
            while (getline(routesFile, line)) {

                stringstream ss(line);

                while (getline(ss, word, ',')){
                    words.push_back(word);
                    //cout << word << ", ";
                }
                string source = words[2];
                Route myRoute(words.at(0), words.at(4), stoi(words.at(7)));
                if (routeMap.find(source) == routeMap.end()) {
                    temp.push_back(myRoute);
                    routeMap[source] =  temp;
                } else {
                    auto it = routeMap.find(source);
                    temp = it->second;
                    temp.push_back(myRoute);
                    routeMap[source] = temp;
                }
                words.clear();
                //cout << endl;
            }
            for (auto i = routeMap.begin(); i != routeMap.end(); i++)
                cout << i->first << "      "
                     << endl;
            cout << "Files Loaded";
            }
        }


};
