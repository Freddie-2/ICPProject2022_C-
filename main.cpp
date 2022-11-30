#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<deque>
#include <algorithm>
#include "Airport.h"
#include "Route.h"
#include "RouteNode.h"

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

vector<Route>getRoutes(string airportCode, unordered_map<string, vector<Route>> routes) {
    vector<Route> destAirports;
    for (auto hgf : routes){
        if (hgf.first.compare(airportCode) == 0){
            destAirports = hgf.second;
        }
    }
    if (destAirports.size() == 0){
        cout << "No airport code exist like: " + airportCode << endl;
    }
    return destAirports;
}
/*
* performing the search for routes
*/
int routeSearching(string source, string destination, unordered_map<string, vector<Route>> routes){
    cout << "Search Started" << endl;

    cout << routes.size() << endl;

    Route *startPlace = new Route("", source, 0);
    /*startPlace.srcAirportCode = source;
    startPlace.airlineCode = "";
    startPlace.stops = 0;*/

    RouteNode *fRouteNodePtr = new RouteNode(*startPlace, nullptr);
    deque<RouteNode> frontier;
    unordered_set<string> explored;
    frontier.push_back(*fRouteNodePtr);
    vector<Route>successor;

    while(!frontier.empty()){
        RouteNode *current = new RouteNode(frontier.front().current, fRouteNodePtr);
        cout << "Airport Code: " + frontier.front().current.airlineCode << endl;
        frontier.pop_front();
        explored.insert(current->current.srcAirportCode);
        vector<Route> destinations;
        //auto itr = routes.find(startPlace.srcAirportCode);
        //destinations = itr->second;

        //vector<Route> destinations;
        destinations = getRoutes(current->current.srcAirportCode, routes);
        cout << "Size is: " << destinations.size() << endl;

        for (auto desti : destinations){
            RouteNode *child = new RouteNode(desti, fRouteNodePtr);
            if (child->current.srcAirportCode.compare(destination) == 0){
                cout << "Destination Found";
                return 0;
                //return solutionPath;
            }

            auto itr2 = find(frontier.begin(), frontier.end(), *child);
            if(explored.find(child->current.srcAirportCode) == explored.end() && itr2 == frontier.end()) {
                frontier.push_back(*child);
            }
        }
    }

}

int main(){

    //createInputFile();
    unordered_map<string, Airport> airports = collectData();
       // map iterator created
    // iterator pointing to start of map

    unordered_map<string, Airport>::iterator it = airports.begin();

    // Iterating over the map using Iterator till map end.
    /*
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
    cout << "Yes" << endl; */

    //createInputFile();
    Route newRoute;

    unordered_map<string, vector<Route>> routes = newRoute.routemethod();
    routeSearching("ACC", "HRE", routes);
    return 0;
};
