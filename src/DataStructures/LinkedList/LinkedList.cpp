#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() 
    : head(nullptr), tail(nullptr), length(0)
{
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::push_back(void* value) {
    Node* newNode = new Node(value);

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    length++;
}

void LinkedList::push_front(void* value) {
    Node* newNode = new Node(value); // pass value to constructor
    newNode->next = head;

    head = newNode;
    if (!tail) {
        tail = newNode;
    }

    length++;
}

bool LinkedList::pop_front() {
    if (!head) return false;

    Node* old = head;
    head = head->next;
    delete old;
    length--;

    if (!head) tail = nullptr;

    return true;
}

void* LinkedList::front() const {
    return head ? head->data : nullptr;
}

bool LinkedList::empty() const {
    return length == 0;
}

int LinkedList::size() const {
    return length;
}

void LinkedList::clear() {
    Node* current = head;

    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = tail = nullptr;
    length = 0;
}

Node* LinkedList::begin() const {
    return head;
}
