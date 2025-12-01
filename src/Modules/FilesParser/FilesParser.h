#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <string>
#include "DataStructures/Graph/Graph.h"
#include "Models/Port/Port.h"
#include "Models/RouteData/RouteData.h"

class FileParser {
public:
    FileParser(Graph* g);

    void parseRoutes(const std::string& filename);
    void parsePortCharges(const std::string& filename);

private:
    Graph* graph;

    void addPortIfNotExists(const std::string& portName);
};

#endif
