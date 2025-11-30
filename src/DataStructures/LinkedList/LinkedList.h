#ifndef LINKEDLIST_H
#define LINKEDLIST_H




class Node {

    public:
    void* data;
    Node* next;

    Node(void* value) : data(value), next(nullptr) {}
};

class LinkedList {
private:

    Node* head; 
    Node* tail; 
    int length;  

public:
    LinkedList();
    ~LinkedList(); 

    void push_back(void* value);
    void push_front(void* value);
    bool pop_front();

    void* front() const;
    bool empty() const;
    int size() const;

    void clear(); 


    Node* begin() const;
};

#endif
