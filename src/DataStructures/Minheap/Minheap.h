#ifndef MINHEAP_H
#define MINHEAP_H

struct HeapNode {
    void* data;
    int key;  

    HeapNode(void* d = nullptr, int k = 0) : data(d), key(k) {}
};

class MinHeap {
private:
    HeapNode** heap; 
    int capacity; 
    int length; 

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MinHeap(int cap = 10);
    ~MinHeap();

    void insert(void* data, int key);
    HeapNode* extractMin(); 
    HeapNode* peek() const; 
    int size() const;
    bool empty() const;
    void clear();
};

#endif 
