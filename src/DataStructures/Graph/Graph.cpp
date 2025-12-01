#include "Graph.h"

Graph::Graph() {}

Graph::~Graph() {
    clear();
}

void Graph::addPort(Port* port) {
    ports.push_back(port);
}

void Graph::addEdge(Port* origin, Port* dest, int cost, RouteData* route) {
    if (!origin || !dest || !route) return;
    GraphEdge* e = new GraphEdge(dest, cost, route);
    origin->edges.push_back(e);
}

Port* Graph::getPortByName(const std::string& name) {
    for (Node* n = ports.begin(); n != nullptr; n = n->next) {
        Port* p = (Port*)n->data;
        if (p->name == name) return p;
    }
    return nullptr;
}


LinkedList* Graph::getPorts() {
    return &ports;
}

void Graph::clear() {
    for (Node* n = ports.begin(); n != nullptr; n = n->next) {
        Port* p = (Port*)n->data;
        // delete edges
        for (Node* eNode = p->edges.begin(); eNode != nullptr; eNode = eNode->next) {
            delete (GraphEdge*)eNode->data;
        }
        p->edges.clear();
        delete p;
    }
    ports.clear();
}
