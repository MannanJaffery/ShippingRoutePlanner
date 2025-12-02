#include "graphics.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include "Models/Port/Port.h"

Graphics::Graphics(Graph* g)
    : graph(g),
      window(nullptr),
      portCount(0),
      routeCount(0)
{
    // Create window dynamically with professional size - larger for better visibility
    window = new sf::RenderWindow(sf::VideoMode({1800u, 1000u}), "OceanRoute Nav - Maritime Logistics Visualization");
    window->setFramerateLimit(60);
    
    mapSprite = nullptr;

    // Load map texture and sprite
    if (!mapTexture.loadFromFile("public/MapImage.png"))
        std::cerr << "Failed to load map image!\n";
    
    mapSprite = new sf::Sprite(mapTexture);
    // Scale map to fit window perfectly
    sf::Vector2u mapSize = mapTexture.getSize();
    mapSprite->setScale(sf::Vector2f(1800.0f / mapSize.x, 1000.0f / mapSize.y));

    // Load font
    if (!font.openFromFile("public/arial.ttf"))
        std::cerr << "Failed to load font!\n";

    // Set port positions from coordinates
    setPortPositionsFromCoordinates();
    calculateLabelPositions();
    prepareRoutes();
}

void Graphics::setPortPositionsFromCoordinates() {
    if (!window) return;
    
    sf::Vector2u windowSize = window->getSize();
    Node* n = graph->getPorts()->begin();
    int count = 0;

    while (n != nullptr && count < MAX_PORTS) {
        Port* p = (Port*)n->data;

        // Convert coordinates (degrees) to pixel positions
        float x = ((p->lon + 180.0f) / 360.0f) * windowSize.x;
        float y = ((90.0f - p->lat) / 180.0f) * windowSize.y;

        portPositions[count] = sf::Vector2f(x, y);
        
        // Initialize label
        if (p->name.length() > 0) {
            for (int i = 0; i < MAX_NAME_LENGTH - 1 && i < (int)p->name.length(); i++) {
                portLabels[count].name[i] = p->name[i];
            }
            portLabels[count].name[p->name.length()] = '\0';
        } else {
            portLabels[count].name[0] = '\0';
        }
        portLabels[count].position = sf::Vector2f(x, y);
        portLabels[count].displayOffset = sf::Vector2f(15.f, 15.f);
        portLabels[count].hasLabel = true;
        
        count++;
        n = n->next;
    }
    portCount = count;
}

void Graphics::calculateLabelPositions() {
    // Smart label positioning to avoid overlaps
    for (int i = 0; i < portCount; i++) {
        if (!portLabels[i].hasLabel) continue;

        float baseX = portLabels[i].position.x;
        float baseY = portLabels[i].position.y;
        
        // Find optimal offset based on neighboring ports
        float minDistance = 10000.f;
        int quadrant = 0; // 0: bottom-right, 1: bottom-left, 2: top-left, 3: top-right

        // Check distance to all other ports
        for (int j = 0; j < portCount; j++) {
            if (i == j) continue;
            
            float dx = portLabels[j].position.x - baseX;
            float dy = portLabels[j].position.y - baseY;
            float dist = sqrt(dx * dx + dy * dy);
            
            if (dist < minDistance) {
                minDistance = dist;
                // Determine quadrant based on relative position
                if (dx > 0 && dy > 0) quadrant = 0;      // bottom-right
                else if (dx < 0 && dy > 0) quadrant = 1; // bottom-left
                else if (dx < 0 && dy < 0) quadrant = 2; // top-left
                else quadrant = 3;                        // top-right
            }
        }

        // Adjust label offset to avoid overlaps
        switch (quadrant) {
            case 0:
                portLabels[i].displayOffset = sf::Vector2f(-70.f, -20.f); // top-left of port
                break;
            case 1:
                portLabels[i].displayOffset = sf::Vector2f(15.f, -20.f);  // top-right of port
                break;
            case 2:
                portLabels[i].displayOffset = sf::Vector2f(15.f, 15.f);   // bottom-right of port
                break;
            case 3:
                portLabels[i].displayOffset = sf::Vector2f(-70.f, 15.f);  // bottom-left of port
                break;
        }
    }
}

void Graphics::prepareRoutes() {
    routeCount = 0;
    Node* n = graph->getPorts()->begin();

    for (int i = 0; i < portCount && n != nullptr; i++, n = n->next) {
        Port* p = (Port*)n->data;
        Node* eNode = p->edges.begin();

        while (eNode != nullptr && routeCount < MAX_ROUTES) {
            GraphEdge* edge = (GraphEdge*)eNode->data;

            int destIdx = -1;
            Node* destNode = graph->getPorts()->begin();
            for (int j = 0; j < portCount && destNode != nullptr; j++, destNode = destNode->next) {
                if ((Port*)destNode->data == edge->destination) {
                    destIdx = j;
                    break;
                }
            }

            if (destIdx != -1) {
                routes[routeCount].start.position = portPositions[i];
                routes[routeCount].start.color = sf::Color(100, 180, 255, 150);  // Semi-transparent blue

                routes[routeCount].end.position = portPositions[destIdx];
                routes[routeCount].end.color = sf::Color(100, 180, 255, 150);

                routes[routeCount].route = edge->route;
                routeCount++;
            }
            eNode = eNode->next;
        }
    }
}

void Graphics::drawRoutes() {
    if (!window) return;

    // Routes are currently hidden for cleaner visualization
    // To enable routes, uncomment the code below:
    /*
    for (int i = 0; i < routeCount; i++) {
        sf::Vertex line[] = {
            routes[i].start,
            routes[i].end
        };
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }
    */
}

void Graphics::drawPorts() {
    if (!window) return;

    // Draw ports with professional styling and increased visibility
    for (int i = 0; i < portCount; i++) {
        // Outer glow circle - larger and more visible
        sf::CircleShape glow(PORT_RADIUS + 5.f);
        glow.setFillColor(sf::Color(80, 150, 200, 100));
        glow.setPosition(sf::Vector2f(portPositions[i].x - (PORT_RADIUS + 5.f), 
                                      portPositions[i].y - (PORT_RADIUS + 5.f)));
        window->draw(glow);

        // Main port circle - larger size for professional appearance
        sf::CircleShape port(PORT_RADIUS + 2.f);
        port.setFillColor(sf::Color(30, 120, 220));  // Professional ocean blue
        port.setOutlineColor(sf::Color(255, 255, 255));
        port.setOutlineThickness(2.5f);
        port.setPosition(sf::Vector2f(portPositions[i].x - (PORT_RADIUS + 2.f), 
                                      portPositions[i].y - (PORT_RADIUS + 2.f)));
        window->draw(port);

        // Center dot for port reference point
        sf::CircleShape center(3.f);
        center.setFillColor(sf::Color::White);
        center.setPosition(sf::Vector2f(portPositions[i].x - 3.f, portPositions[i].y - 3.f));
        window->draw(center);
    }
}

void Graphics::drawLabels() {
    if (!window) return;

    // Draw port labels with improved visibility
    for (int i = 0; i < portCount; i++) {
        if (!portLabels[i].hasLabel) continue;

        sf::Vector2f labelPos = portLabels[i].position + portLabels[i].displayOffset;

        // Draw semi-transparent background box for text
        sf::Text tempText(font, portLabels[i].name, TEXT_SIZE);
        sf::FloatRect textBounds = tempText.getLocalBounds();
        
        sf::RectangleShape background(sf::Vector2f(textBounds.size.x + 6.f, textBounds.size.y + 4.f));
        background.setPosition(sf::Vector2f(labelPos.x - 3.f, labelPos.y - 2.f));
        background.setFillColor(sf::Color(20, 20, 40, 200));  // Dark semi-transparent
        background.setOutlineColor(sf::Color(100, 180, 255));
        background.setOutlineThickness(1.f);
        window->draw(background);

        // Draw port name with bright yellow color for high visibility
        sf::Text text(font, portLabels[i].name, TEXT_SIZE);
        text.setFillColor(sf::Color(255, 220, 0));  // Bright yellow
        text.setPosition(labelPos);
        window->draw(text);

        // Draw connection line from port to label
        sf::Vertex connectionLine[2];
        connectionLine[0].position = portPositions[i];
        connectionLine[0].color = sf::Color(100, 180, 255, 100);
        connectionLine[1].position = labelPos + sf::Vector2f(textBounds.size.x / 2.f, 0.f);
        connectionLine[1].color = sf::Color(100, 180, 255, 100);
        window->draw(connectionLine, 2, sf::PrimitiveType::Lines);
    }
}

void Graphics::draw() {
    if (!window) return;
    
    // Clear with gradient-like dark blue background
    window->clear(sf::Color(15, 25, 45));
    
    // Draw map background
    if (mapSprite) {
        window->draw(*mapSprite);
    }

    // Draw all route lines first (background layer)
    drawRoutes();
    
    // Draw all ports (middle layer)
    drawPorts();
    
    // Draw all labels (foreground layer)
    drawLabels();

    // Draw UI information
    sf::Text infoText(font, "OceanRoute Nav - Maritime Logistics System", 14);
    infoText.setFillColor(sf::Color(100, 180, 255));
    infoText.setPosition(sf::Vector2f(10.f, 10.f));
    window->draw(infoText);

    sf::Text statsText(font, "Ports: " + std::to_string(portCount) + " | Routes: " + std::to_string(routeCount), 12);
    statsText.setFillColor(sf::Color(150, 150, 150));
    statsText.setPosition(sf::Vector2f(10.f, window->getSize().y - 25.f));
    window->draw(statsText);
    
    window->display();
}

void Graphics::run() {
    if (!window) return;
    
    while (window->isOpen()) {
        auto eventOpt = window->pollEvent();
        if (eventOpt) {
            sf::Event& event = *eventOpt;
            if (event.is<sf::Event::Closed>()) {
                window->close();
            }
        }

        draw();
    }
}

Graphics::~Graphics() {
    if (mapSprite) {
        delete mapSprite;
        mapSprite = nullptr;
    }
    if (window) {
        delete window;
        window = nullptr;
    }
}
