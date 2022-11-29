#include <iostream>
#include <string>
#include <fstream>
#include<unordered_map>
#include <vector>
#include <sstream>
#include "Route.h"


using namespace std;

class RouteNode{
public:
    Route current;
    RouteNode *parent;
    int stops;

    bool operator==(const RouteNode& name) const {
        return this -> current == name.current;
    }
    RouteNode(Route rte, RouteNode* rn){
        this -> current = rte;
        this -> parent = rn;
    }
    RouteNode(Route rte){
        this -> rte;
        this -> parent = nullptr;
    }
};
