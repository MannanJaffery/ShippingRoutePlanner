#include "MinHeap.h"
#include <iostream>

MinHeap::MinHeap(int cap) : capacity(cap), length(0) {
    heap = new HeapNode*[capacity];
}

MinHeap::~MinHeap() {
    clear();
    delete[] heap;
}

void MinHeap::resize() {
    int newCap = capacity * 2;
    HeapNode** newHeap = new HeapNode*[newCap];
    for (int i = 0; i < length; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCap;
}

void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index]->key < heap[parent]->key) {
            HeapNode* tmp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = tmp;
            index = parent;
        } else {
            break;
        }
    }
}

void MinHeap::heapifyDown(int index) {
    int smallest = index;
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < length && heap[left]->key < heap[smallest]->key)
            smallest = left;
        if (right < length && heap[right]->key < heap[smallest]->key)
            smallest = right;

        if (smallest != index) {
            HeapNode* tmp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = tmp;
            index = smallest;
        } else {
            break;
        }
    }
}

void MinHeap::insert(void* data, int key) {
    if (length >= capacity) resize();
    heap[length] = new HeapNode(data, key);
    heapifyUp(length);
    length++;
}

HeapNode* MinHeap::extractMin() {
    if (length == 0) return nullptr;

    HeapNode* minNode = heap[0];
    heap[0] = heap[length - 1];
    length--;
    heapifyDown(0);

    return minNode;
}

HeapNode* MinHeap::peek() const {
    return (length > 0) ? heap[0] : nullptr;
}

int MinHeap::size() const {
    return length;
}

bool MinHeap::empty() const {
    return length == 0;
}

void MinHeap::clear() {
    for (int i = 0; i < length; i++) {
        delete heap[i];
    }
    length = 0;
}
