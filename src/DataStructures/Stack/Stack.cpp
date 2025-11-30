#include "Stack.h"
#include <iostream>

Stack::Stack() : topNode(nullptr), length(0) {}

Stack::~Stack() {
    clear();
}

void Stack::push(void* value) {
    StackNode* newNode = new StackNode(value);
    newNode->next = topNode;
    topNode = newNode;
    length++;
}

bool Stack::pop() {
    if (!topNode) return false;

    StackNode* old = topNode;
    topNode = topNode->next;
    delete old;
    length--;
    return true;
}

void* Stack::top() const {
    return topNode ? topNode->data : nullptr;
}

bool Stack::empty() const {
    return length == 0;
}

int Stack::size() const {
    return length;
}

void Stack::clear() {
    while (topNode) {
        StackNode* next = topNode->next;
        delete topNode;
        topNode = next;
    }
    length = 0;
}

StackNode* Stack::begin() const {
    return topNode;
}
