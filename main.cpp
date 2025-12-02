// #include <SFML/Graphics.hpp>
// #include <optional>
// #include <vector>

// int main(){

//     return 0;
// }



#include <iostream>

#include "DataStructures/LinkedList/LinkedList.h"
#include "DataStructures/Queue/Queue.h"
#include "DataStructures/Stack/Stack.h"
#include "DataStructures/Minheap/Minheap.h"
#include "DataStructures/Graph/Graph.h"
#include "Models/RouteData/RouteData.h"
#include "Models/Port/Port.h"
#include "Modules/FilesParser/FilesParser.h"
#include "Graphics/graphics.h"
using namespace std;

int main() {


//     // Create a window
//     sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Shipping Route Visualizer");
//     window.setFramerateLimit(60);

//     // Example: Ports as circles
//     std::vector<sf::CircleShape> ports;

//     // Create a few sample ports
//     for (int i = 0; i < 5; ++i) {
//         sf::CircleShape port(20.f);                  // radius 20
//         port.setFillColor(sf::Color::Blue);
//         port.setPosition({50.f + i*120.f, 300.f});   // spread horizontally
//         ports.push_back(port);
//     }

//     // Example: Route as a line (using VertexArray)
//  sf::VertexArray route(sf::PrimitiveType::Lines, 2);
// route[0].position = {70.f, 320.f};
// route[0].color = sf::Color::Red;
// route[1].position = {190.f, 320.f};
// route[1].color = sf::Color::Red;
//     // Main loop
//     while (window.isOpen()) {
//         // Poll events
//         while (auto eventOpt = window.pollEvent()) {
//             sf::Event& event = *eventOpt;
//             if (event.is<sf::Event::Closed>()) {
//                 window.close();
//             }
//         }

//         window.clear(sf::Color::Black);

//         // Draw ports
//         for (auto& port : ports) {
//             window.draw(port);
//         }

//         // Draw route
//         window.draw(route);

//         window.display();
//     }



    Graph g;

    // Parse your files
    FileParser parser(&g);
    parser.parsePortCharges("public/PortChargers.txt");
    parser.parseRoutes("public/Routes.txt");
    parser.parsePortCoordinates("public/coordinatesInDegree.txt");

    // Run graphics
    Graphics graphics(&g);
    graphics.run();

    g.clear();
    return 0;
}
