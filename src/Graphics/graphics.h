#pragma once
#include <SFML/Graphics.hpp>
#include "../DataStructures/Graph/Graph.h"
#include "../Models/RouteData/RouteData.h"

#define MAX_PORTS 50
#define MAX_ROUTES 200
#define MAX_NAME_LENGTH 128
#define PORT_RADIUS 10.f
#define TEXT_SIZE 14
#define MIN_TEXT_DISTANCE 55.f

struct RouteVisual {
    sf::Vertex start;
    sf::Vertex end;
    RouteData* route;
};

struct PortLabel {
    char name[MAX_NAME_LENGTH];
    sf::Vector2f position;
    sf::Vector2f displayOffset;
    bool hasLabel;
};

class Graphics {
public:
    Graph* graph;
    sf::RenderWindow* window;

    Graphics(Graph* g);
    void run();
    ~Graphics();

private:
    sf::Vector2f portPositions[MAX_PORTS];
    PortLabel portLabels[MAX_PORTS];
    int portCount;

    RouteVisual routes[MAX_ROUTES];
    int routeCount;

    sf::Font font;
    sf::Texture mapTexture;
    sf::Sprite* mapSprite;

    void loadMap();
    void setPortPositionsFromCoordinates();
    void calculateLabelPositions();
    void prepareRoutes();
    void draw();
    void drawRoutes();
    void drawPorts();
    void drawLabels();
};
