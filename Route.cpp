#include "Route.h"

using namespace std;

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
                cout << routeMap.size() << endl;
                //cout << endl;
            }
            /*for (auto i = routeMap.begin(); i != routeMap.end(); i++)
                cout << i->first << "      "
                     << endl;
            cout << "Files Loaded";
            } */
            }
            return routeMap;
        }
