#ifndef QUEUE_H
#define QUEUE_H

struct QueueNode {
    void* data;
    QueueNode* next;

    QueueNode(void* value) : data(value), next(nullptr) {}
};

class Queue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int length;

public:
    Queue();
    ~Queue();

    void enqueue(void* value);
    bool dequeue();
    void* front() const;
    bool empty() const;
    int size() const;
    void clear();

    QueueNode* begin() const;
};

#endif
