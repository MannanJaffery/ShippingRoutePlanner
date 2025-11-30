#include "Graph.h"
#include <iostream>

Graph::Graph() {}

Graph::~Graph() {
    clear();
}

void Graph::addPort(Port* port) {
    ports.push_back(port);
}

void Graph::addEdge(Port* origin, Port* dest, int cost) {
    if (!origin || !dest) return;

    Edge* newEdge = new Edge(dest, cost);
    origin->edges.push_back(newEdge);
}

Port* Graph::findPort(const std::string& name) const {
    for (Node* n = ports.begin(); n != nullptr; n = n->next) {
        Port* port = (Port*)n->data;
        if (port->name == name) return port;
    }
    return nullptr;
}

LinkedList* Graph::getPorts() {
    return &ports;
}

void Graph::clear() {
  
    for (Node* n = ports.begin(); n != nullptr; n = n->next) {
        Port* port = (Port*)n->data;

        for (Node* e = port->edges.begin(); e != nullptr; e = e->next) {
            Edge* edge = (Edge*)e->data;
            delete edge;
        }
        port->edges.clear();
        delete port;
    }
    ports.clear();
}
