#ifndef STACK_H
#define STACK_H

struct StackNode {
    void* data;
    StackNode* next;

    StackNode(void* value) : data(value), next(nullptr) {}
};

class Stack {
private:
    StackNode* topNode;
    int length;

public:
    Stack();
    ~Stack();

    void push(void* value);
    bool pop();
    void* top() const; 
    bool empty() const;  
    int size() const;      
    void clear();

    StackNode* begin() const;
};

#endif
