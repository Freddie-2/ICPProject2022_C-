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
void createInputFile(string& city, string &country, string& city2,string& country2){
    cout << "Enter the start city and country <Enter>"; // taking the start city and country
    cin >> city >> country;
    cout << "Enter the destination city and country <Enter>";
    cin >> city2 >> country2;
    cout << "City is " << city << " and country is " << country << endl;
    string input = city + "-" + city2 + ".txt";
    fstream inputfile;
    inputfile.open(input, ios::out);
    if (inputfile.is_open()){
        inputfile << city << "," << country << endl;
        inputfile << city2 << "," << country2 << endl;
        inputfile.close();
    }
}

/*
* function to get the solution path
* routes taken from the start city to destination
*/
string getSolutionPath(RouteNode* goal) {
    string routeTaken = "";
    for(RouteNode* nodeptr = goal; nodeptr != nullptr && nodeptr->parent != nullptr; nodeptr = nodeptr->parent) {
        string tmp = nodeptr->current.airlineCode + " from " + nodeptr->parent->current.srcAirportCode + " to " + nodeptr->current.srcAirportCode + "\n";
        routeTaken = tmp + routeTaken;
    }
    return routeTaken;

}

/*
* function to create the output file and write the solution path(routes) inside
*/
void writeOutputFile(RouteNode* goal, string city, string city2, string country2) {
        string output = getSolutionPath(goal);
        string out_str = city + "-" + city2 + "_output.txt";
        fstream outfile;
        outfile.open(out_str, ios::out);
        if (outfile.is_open()){
            outfile << output;
            outfile.close();

    }
    cout << "Write Successful" << endl;
}

/*
* function to get the possible destinations from a particular airport
*/
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
* function to get the airport codes of the start and destination cities
*/
void getAirportCodes(string city, string country, string city2,string country2, string& sourCode, string& destCode) {

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
        Airport cityCou = it->second;
        if (cityCou.city.compare(city) == 0 && cityCou.country.compare(country) == 0) {
            sourCode = it->first;
        }

        if (cityCou.city.compare(city2) == 0 && cityCou.country.compare(country2) == 0) {
            destCode = it->first;
        }
        // iterator incremented to point next item
        it++;
    }
}

/*
* function to perform the search for routes
*/
int routeSearching(string city, string country, string city2,string country2, unordered_map<string, vector<Route>> routes){
    cout << "Search Started" << endl;

    string destination;
    string source;
    getAirportCodes(city, country, city2, country2, source, destination);

    Route *startPlace = new Route("", source, 0);

    RouteNode *fRouteNodePtr = new RouteNode(*startPlace, nullptr);
    deque<RouteNode> frontier;
    unordered_set<string> explored;
    frontier.push_back(*fRouteNodePtr);
    vector<Route>successor;

    while(!frontier.empty()){
        RouteNode *current = new RouteNode(frontier.front().current, fRouteNodePtr);
        cout << "Current Airport Code: " + frontier.front().current.srcAirportCode << endl;
        frontier.pop_front();
        explored.insert(current->current.srcAirportCode);
        vector<Route> destinations;

        destinations = getRoutes(current->current.srcAirportCode, routes);

        for (auto desti : destinations){
            RouteNode *child = new RouteNode(desti, current);

            if (child->current.srcAirportCode.compare(destination) == 0){
                cout << "Destination Found\n";
                writeOutputFile(child, city, city2, country2);
                return 0;
            }

            auto itr2 = find(frontier.begin(), frontier.end(), *child);
            if(explored.find(child->current.srcAirportCode) == explored.end() && itr2 == frontier.end()) {
                frontier.push_back(*child);
            }
        }
    }

}

/*
* main method
*/
int main(){
    string startCity, startCountry, destinationCity, destinationCountry;
    string destCode;
    string sourCode;
    createInputFile(startCity, startCountry, destinationCity, destinationCountry);

    cout << "Yes" << endl;
    //createInputFile();
    Route newRoute;

    unordered_map<string, vector<Route>> routes = newRoute.routemethod();
    cout <<"The start city: " + startCity << endl;
    routeSearching(startCity, startCountry, destinationCity, destinationCountry, routes);
    return 0;
};
