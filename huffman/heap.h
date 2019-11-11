#pragma once
#include "node.h"

class Heap //classes naturally private, but still being explicit
{
private:
    int capacity;
    node::Node ** array;

    Heap(); //default constructor
    Heap(int capacity); //custom constructor
    void heapify(Heap * heap, int index);

public:
    int size;
    node::Node * extractMin(Heap * heap);
    void insertHeap(Heap * heap, Node * node);
    void buildHeap(Heap * heap); //going to be overwritten by constructor
    void printArray(int array[], int n);
    //Heap * combineHeap(char letter[], int frequency[], int size);
    //needs to be altered to not return a heap object, but edit the instance of the heap class.
};

#include "heap.cpp" //include implementation for import into huff.h