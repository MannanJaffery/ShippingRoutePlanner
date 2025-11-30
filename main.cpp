// #include <SFML/Graphics.hpp>
// #include <optional>
// #include <vector>

// int main() {
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

//     return 0;
// }



#include<iostream>
#include"src/DataStructures/LinkedList/LinkedList.h"
#include"src/DataStructures/Queue/Queue.h"
#include"src/DataStructures/Graph/Graph.h"
#include"src/DataStructures/Stack/Stack.h"
#include"src/DataStructures/Minheap/Minheap.h"
int main() {
 // -------------------------------
    // LinkedList demonstration
    // -------------------------------
    LinkedList list;

    int a = 10, b = 20, c = 30;

    list.push_back(&a);
    list.push_back(&b);
    list.push_front(&c);

    std::cout << "LinkedList contents (size " << list.size() << "): ";
    for (Node* n = list.begin(); n != nullptr; n = n->next) {
        std::cout << *(int*)n->data << " ";
    }
    std::cout << std::endl;

    list.pop_front();
    std::cout << "After pop_front, LinkedList size: " << list.size() << std::endl;
    std::cout << "LinkedList contents now: ";
    for (Node* n = list.begin(); n != nullptr; n = n->next) {
        std::cout << *(int*)n->data << " ";
    }
    std::cout << std::endl;

    // -------------------------------
    // Queue demonstration
    // -------------------------------
    Queue queue;

    int x = 100, y = 200, z = 300;

    queue.enqueue(&x);
    queue.enqueue(&y);
    queue.enqueue(&z);

    std::cout << "Queue contents (size " << queue.size() << "): ";
    for (QueueNode* n = queue.begin(); n != nullptr; n = n->next) {
        std::cout << *(int*)n->data << " ";
    }
    std::cout << std::endl;

    queue.dequeue();
    std::cout << "After dequeue, Queue size: " << queue.size() << std::endl;
    std::cout << "Queue contents now: ";
    for (QueueNode* n = queue.begin(); n != nullptr; n = n->next) {
        std::cout << *(int*)n->data << " ";
    }
    std::cout << std::endl;

    // -------------------------------
    // Stack demonstration
    // -------------------------------
    Stack stack;

    int s1 = 5, s2 = 15, s3 = 25;
    stack.push(&s1);
    stack.push(&s2);
    stack.push(&s3);

    std::cout << "Stack contents (top to bottom, size " << stack.size() << "): ";
    for (StackNode* n = stack.begin(); n != nullptr; n = n->next) {
        std::cout << *(int*)n->data << " ";
    }
    std::cout << std::endl;

    stack.pop();
    std::cout << "After pop, Stack size: " << stack.size() << std::endl;
    std::cout << "Stack contents now: ";
    for (StackNode* n = stack.begin(); n != nullptr; n = n->next) {
        std::cout << *(int*)n->data << " ";
    }
    std::cout << std::endl;

    // -------------------------------
    // MinHeap demonstration
    // -------------------------------
    MinHeap heap;

    int h1 = 50, h2 = 20, h3 = 70;
    heap.insert(&h1, 50);
    heap.insert(&h2, 20);
    heap.insert(&h3, 70);

    std::cout << "MinHeap elements by priority:\n";
    while (!heap.empty()) {
        HeapNode* node = heap.extractMin();
        std::cout << *(int*)node->data << " (key " << node->key << ")\n";
        delete node;  // remember to delete heap nodes to avoid memory leak
    }

    // -------------------------------
    // Graph demonstration
    // -------------------------------
    Graph g;

    // Create ports (vertices)
    Port* portA = new Port("PortA");
    Port* portB = new Port("PortB");
    Port* portC = new Port("PortC");

    g.addPort(portA);
    g.addPort(portB);
    g.addPort(portC);

    // Create edges (routes)
    g.addEdge(portA, portB, 100);
    g.addEdge(portB, portC, 200);
    g.addEdge(portA, portC, 300);

    // Print graph
    std::cout << "\nGraph contents:\n";
    for (Node* n = g.getPorts()->begin(); n != nullptr; n = n->next) {
        Port* p = (Port*)n->data;
        std::cout << p->name << " -> ";
        for (Node* e = p->edges.begin(); e != nullptr; e = e->next) {
            Edge* edge = (Edge*)e->data;
            std::cout << edge->destination->name << "(" << edge->cost << ") ";
        }
        std::cout << std::endl;
    }

    // Clear graph to avoid memory leaks
    g.clear();

    return 0;
}












