#include "Graphics.h"
#include <iostream>
#include <cmath>

Graphics::Graphics(Graph* g)
    : graph(g), window(sf::VideoMode(sf::Vector2u(1200, 800)), "Shipping Route Visualizer") 
{
    portCount = 0;
    routeCount = 0;

    setPortPositions();
    prepareRoutes();
}

void Graphics::setPortPositions() {
    Node* n = graph->getPorts()->begin();
    int x = 100, y = 100;
    int stepX = 150, stepY = 100;
    int count = 0;

    while (n != nullptr && count < MAX_PORTS) {
        Port* p = (Port*)n->data;
        portPositions[count] = sf::Vector2f(float(x), float(y));
        portNames[count] = p->name;
        count++;

        x += stepX;
        if (x > 1000) {
            x = 100;
            y += stepY;
        }

        n = n->next;
    }
    portCount = count;
}

void Graphics::prepareRoutes() {
    routeCount = 0;
    Node* n = graph->getPorts()->begin();

    for (int i = 0; i < portCount && n != nullptr; i++, n = n->next) {
        Port* p = (Port*)n->data;
        Node* eNode = p->edges.begin();
        while (eNode != nullptr && routeCount < MAX_ROUTES) {
            GraphEdge* edge = (GraphEdge*)eNode->data;

            // Find destination index
            int destIdx = -1;
            Node* destNode = graph->getPorts()->begin();
            for (int j = 0; j < portCount && destNode != nullptr; j++, destNode = destNode->next) {
                if ((Port*)destNode->data == edge->destination) {
                    destIdx = j;
                    break;
                }
            }

            if (destIdx != -1) {
                routes[routeCount].start.position = portPositions[i] + sf::Vector2f(20.f, 20.f);
                routes[routeCount].start.color = sf::Color::Red;

                routes[routeCount].end.position = portPositions[destIdx] + sf::Vector2f(20.f, 20.f);
                routes[routeCount].end.color = sf::Color::Red;

                routes[routeCount].route = nullptr; // edge->routeData removed
                routeCount++;
            }

            eNode = eNode->next;
        }
    }
}

void Graphics::draw() {
    for (int i = 0; i < portCount; i++) {
        sf::CircleShape port(20.f);
        port.setFillColor(sf::Color::Blue);
        port.setPosition(portPositions[i]);
        window.draw(port);

        sf::Text text(font, portNames[i], 14); // SFML 3.x constructor
        text.setFillColor(sf::Color::White);
        text.setPosition(portPositions[i] + sf::Vector2f(0.f, 25.f));
        window.draw(text);
    }

    for (int i = 0; i < routeCount; i++) {
        sf::Vertex line[] = { routes[i].start, routes[i].end };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void Graphics::run() {
    while (window.isOpen()) {
        while (auto eventOpt = window.pollEvent()) {
            sf::Event event = *eventOpt;
            if (event.is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        draw();
        window.display();
    }
}
