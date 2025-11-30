#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "../LinkedList/LinkedList.h" 

struct Port;

struct Edge {
    Port* destination;
    int cost;
    Edge* next;

    Edge(Port* dest, int c) : destination(dest), cost(c), next(nullptr) {}
};

struct Port {
    std::string name;
    LinkedList edges; 
    
    Port(const std::string& n) : name(n) {}
};


class Graph {
private:
    LinkedList ports; 

public:
    Graph();
    ~Graph();

    void addPort(Port* port);      
    void addEdge(Port* origin, Port* dest, int cost); 
    Port* findPort(const std::string& name) const; 

    LinkedList* getPorts();
    void clear();     
};

#endif
