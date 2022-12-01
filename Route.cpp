#include "Route.h"

using namespace std;

/*
* getting the route map from the routes.csv file.
*/
unordered_map<string, vector<Route>> Route::routemethod(){

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
            }

        }
        return routeMap;
}
