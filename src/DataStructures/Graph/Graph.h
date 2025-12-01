#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "DataStructures/LinkedList/LinkedList.h"
#include "Models/Port/Port.h"
#include "Models/RouteData/RouteData.h"

// Forward declaration
struct Port;

// Graph edge structure
struct GraphEdge {
    Port* destination;
    int cost;
    RouteData* route;
    GraphEdge* next;

    GraphEdge(Port* dest, int c, RouteData* r) 
        : destination(dest), cost(c), route(r), next(nullptr) {}
};

class Graph {
private:
    LinkedList ports; // List of Port*

public:
    Graph();
    ~Graph();

    void addPort(Port* port);      
    void addEdge(Port* origin, Port* dest, int cost, RouteData* route);

    Port* getPortByName(const std::string& name);

    LinkedList* getPorts();
    void clear();     
};

#endif
