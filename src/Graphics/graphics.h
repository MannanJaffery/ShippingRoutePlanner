#pragma once
#include <SFML/Graphics.hpp>
#include "../DataStructures/Graph/Graph.h"
#include "../Models/RouteData/RouteData.h"

#define MAX_PORTS 50
#define MAX_ROUTES 200

struct RouteVisual {
    sf::Vertex start;
    sf::Vertex end;
    RouteData* route; // optional pointer for hover info
};

class Graphics {
public:
    Graph* graph;
    sf::RenderWindow window;

    Graphics(Graph* g);
    void run();

private:
    sf::Vector2f portPositions[MAX_PORTS];
    std::string portNames[MAX_PORTS];
    int portCount;

    RouteVisual routes[MAX_ROUTES];
    int routeCount;

    sf::Font font; // for text

    void setPortPositions();
    void prepareRoutes();
    void draw();
};
