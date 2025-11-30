#include "Queue.h"
#include <iostream>

Queue::Queue() 
    : frontNode(nullptr), rearNode(nullptr), length(0) 
{
}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(void* value) {
    QueueNode* newNode = new QueueNode(value);

    if (!rearNode) { 
        frontNode = rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }

    length++;
}

bool Queue::dequeue() {
    if (!frontNode) return false;

    QueueNode* old = frontNode;
    frontNode = frontNode->next;
    delete old;
    length--;

    if (!frontNode) rearNode = nullptr;
    return true;
}

void* Queue::front() const {
    return frontNode ? frontNode->data : nullptr;
}

bool Queue::empty() const {
    return length == 0;
}

int Queue::size() const {
    return length;
}

void Queue::clear() {
    while (frontNode) {
        QueueNode* next = frontNode->next;
        delete frontNode;
        frontNode = next;
    }
    rearNode = nullptr;
    length = 0;
}

QueueNode* Queue::begin() const {
    return frontNode;
}
