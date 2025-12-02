#ifndef PORT_H
#define PORT_H

#include "DataStructures/LinkedList/LinkedList.h"
#include <string>

// Forward declaration
class Port;

// Port edge structure
struct PortEdge {
    Port* destination;
    int cost;
    std::string company;

    PortEdge(Port* dest, int c, const std::string& comp)
        : destination(dest), cost(c), company(comp) {}
};

class Port {
public:
    std::string name;
    int charge;
    LinkedList edges; // LinkedList of PortEdge*
    double lat , lon;
    Port(const std::string& n): name(n) , charge(0) , lat(0) , lon(0) {}
};

#endif
