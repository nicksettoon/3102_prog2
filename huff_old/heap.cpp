#pragma once
#include "heap.h" //includes heap and node

heap::Heap() //default constructor
    : size(0), capacity(1), *array(node::Node()){}

heap::Heap(int capacity) //custom constructor
{
    this->size = 0;
    this->capacity = capacity;
    this->*array = new node::Node[capacity];

    int n = this->size - 1;
    for(int i = (n - 1)/2; i >= 0; i--)
    {
        Heap->heapify(this, i);
    }
}


/* 
Old, manual heap constructors
Node * newHeap(int capacity)
{
    Node * temp;
    //struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp = new Node();
    temp->size = 0;
    temp->capacity = capacity;
    //temp->array = (struct Node**)malloc(Heap->capacity * sizeof(struct Node*));
    return temp;
}

Heap* newHeap(int capacity)
{
    Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct Node**)malloc(heap->capacity * sizeof(struct Node*));
    return heap;
}
*/

void heap::heapify(Heap * heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if(left < heap->size && heap->array[left]->frequency < heap->array[smallest]->frequency)
    {
        smallest = left;
    }
    if(right < heap->size && heap->array[right]->frequency < heap->array[smallest]->frequency)
    {
        smallest = right;
    }
    if(smallest != index)
    {
        swap(heap->array[smallest], heap->array[index]);
        heapify(heap, smallest);
    }
}

Node * heap::extractMin(Heap * heap)
{
    Node * temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size = heap->size - 1;
    heapify(heap, 0);
    return temp;
}

void heap::insertHeap(Heap * heap, Node * node)
{
    heap->size = heap->size + 1;
    int i = heap->size - 1;
    while(i < heap->array[(i - 1) / 2]->frequency && node->frequency < heap->array[(i - 1) / 2]->frequency)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i-1)/2;
    }
    heap->array[i] = node;
}

void heap::buildHeap(Heap * heap)
{
    int n = heap->size - 1;
    for(int i = (n - 1)/2; i >= 0; i--)
    {
        heapify(heap, i);
    }
}


void heap::printArray(int array[], int n)
{
    ofstream output;
    ifstream input;
    output.open("encoded.txt", std::ios_base::app);
    int i;
    for (i = 0; i < n; i++)
    {
        cout << array[i];
        output << array[i];
    }
    cout << endl;
    output << endl;
    output.close();
}

Heap * heap::combineHeap(char letter[], int frequency[], int size)
{
    Heap * heap = newHeap(size);
    for(int i = 0; i < size; i++)
    {
        heap->array[i] = newNode(letter[i], frequency[i]);
    }
    heap->size = size;
    buildHeap(heap);
    return heap;
}

/*
Old, depreciated heap functions?
void heapify(Node *FrequencyTable[], int Flength, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < Flength && FrequencyTable[left]->frequency < FrequencyTable[smallest]->frequency)
    {
        smallest = left;
    }
    if(right < Flength && FrequencyTable[right]->frequency < FrequencyTable[smallest]->frequency)
    {
        smallest = right;
    }
    if(smallest != i)
    {
        Node * temp = FrequencyTable[i];
        FrequencyTable[i] = FrequencyTable[smallest];
        FrequencyTable[smallest] = temp;
        heapify(FrequencyTable, Flength, smallest);
    }
}

Node * extractMin(Node * FrequencyTable[], int &Flength)
{
    Node * temp;
    temp = FrequencyTable[0];
    FrequencyTable[0] = FrequencyTable[Flength - 1];
    FrequencyTable[Flength - 1] = temp;
    Flength--;
    heapify(FrequencyTable, Flength, 0);
    return temp;
}

void insertNode(Node * FrequencyTable[], Node * node, int &Flength)
{
    Flength++;
    FrequencyTable[Flength - 1] = node;
    int parent = ((Flength -1 ) - 1)/2;
    while(FrequencyTable[Flength - 1]->frequency < FrequencyTable[parent]->frequency)
    {
        Node * temp = FrequencyTable[Flength - 1];
        FrequencyTable[Flength - 1] = FrequencyTable[parent];
        FrequencyTable[parent] = temp;
        Flength = parent + 1;
    }
}


void createHeap(Node *FrequencyTable[], int Flength)
{
    for(int i = (Flength / 2) - 1; i >= 0; i--)
    {
        heapify(heap, i);
    }
}

*/
