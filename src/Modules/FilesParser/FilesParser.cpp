


#include "FilesParser.h"
#include <fstream>
#include <iostream>
using namespace std;

FileParser::FileParser(Graph* g) : graph(g) {}

void FileParser::addPortIfNotExists(const std::string& portName){
    if (!graph->getPortByName(portName)) {
        Port* port = new Port(portName);
        graph->addPort(port);
    }
}

void FileParser::parseRoutes(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string origin, destination, date, depTime, arrTime, costStr, company;
        size_t pos = 0;

        // Extract origin
        pos = line.find(' ');
        origin = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract destination
        pos = line.find(' ');
        destination = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract date
        pos = line.find(' ');
        date = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract departure time
        pos = line.find(' ');
        depTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract arrival time
        pos = line.find(' ');
        arrTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract cost
        pos = line.find(' ');
        costStr = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Remaining is company
        company = line;

        int cost = stoi(costStr);

        addPortIfNotExists(origin);
        addPortIfNotExists(destination);

        RouteData* route = new RouteData(origin, destination, date, depTime, arrTime, cost, company);
        Port* originPort = graph->getPortByName(origin);
        Port* destPort = graph->getPortByName(destination);

        graph->addEdge(originPort, destPort, cost, route);
    }

    file.close();
}

void FileParser::parsePortCharges(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find(' ');
        if (pos == string::npos) continue;

        string portName = line.substr(0, pos);
        string chargeStr = line.substr(pos + 1);

        int charge = stoi(chargeStr);

        addPortIfNotExists(portName);
        Port* port = graph->getPortByName(portName);
        port->charge = charge;
    }

    file.close();
}
