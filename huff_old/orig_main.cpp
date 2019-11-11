#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct Node
{
    char letter;
    int frequency;
    Node * left;
    Node * right;
};

struct Heap
{
    int size;
    int capacity;
    Node ** array;
    Heap(int capacity)
    {
        size = 0;
        capacity = capacity;
        *array = new Node[capacity];
    }
};


Node * newNode(char c, int frequency)
{
    Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->letter = c;
    temp->frequency = frequency;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}


/*
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
*/


Heap* newHeap(int capacity)
{
    Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct Node**)malloc(heap->capacity * sizeof(struct Node*));
    return heap;
}

void heapify(Heap * heap, int index)
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

Node * extractMin(Heap * heap)
{
    Node * temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size = heap->size - 1;
    heapify(heap, 0);
    return temp;
}

void insertHeap(Heap * heap, Node * node)
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

void buildHeap(Heap * heap)
{
    int n = heap->size - 1;
    for(int i = (n - 1)/2; i >= 0; i--)
    {
        heapify(heap, i);
    }
}


void printArray(int array[], int n)
{
    ofstream out;
    ifstream in;
    out.open("encoded.txt", std::ios_base::app);
    int i;
    for (i = 0; i < n; i++)
    {
        cout << array[i];
        out << array[i];
    }
    cout << endl;
    out << endl;
    out.close();
}

Heap * combineHeap(char letter[], int frequency[], int size)
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

Node * buildHuffman(char letter[], int frequency[], int size)
{
    Node * left;
    Node * right;
    Node * top;
    int freq;
    Heap * heap = combineHeap(letter, frequency, size);

    while(heap->size != 1)
    {
        left = extractMin(heap);
        right = extractMin(heap);
        freq = left->frequency + right->frequency;
        top = newNode('$', freq);

        top->left = left;
        top->right = right;
        insertHeap(heap, top);
    }
    return extractMin(heap);
}

void printHuffman(Node * root, int array[], int top)
{
    ofstream out;
    out.open("characters.txt", std::ios_base::app);
    if(root->left)
    {
        array[top] = 0;
        printHuffman(root->left, array, top + 1);
    }
    if(root->right)
    {
        array[top] = 1;
        printHuffman(root->right, array, top + 1);
    }
    if(!(root->left) && !(root->right))
    {
        cout << root->letter << ": ";
        out << root->letter << endl;
        printArray(array, top);
    }
    out.close();
}

Node * HuffmanTree(char letter[], int frequency[], int size)
{
    Node * root = buildHuffman(letter, frequency, size);
    int array[500];
    int top = 0;
    printHuffman(root, array, top);
    return root;
}

void frequencyCount(string text, char letter[], int frequency[], int numchar)
{
    cout << "Entering frequency function" << endl;
    char current = letter[0];
    int freq = 0;
    for(int k = 0; k < numchar; k++)
    {
        freq = 0;
        current = letter[k];
        for(int i = 0; i < text.length(); i++)
        {
            if(text[i] == current)
            {
                freq++;
            }
        }
        frequency[k] = freq;
    }
  //  FrequencyTable[Flength] = newNode(text[textlength - 1], frequency, nullptr, nullptr);
    //size++;
}


/*

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

void getCode(Node *root,int A[], int top, ofstream &out, ifstream &in)
{
    int i = 0;
    int encodedtext[600];
    int encodearray[600];
    int sizeofarray = 0;
    if(root->left)
    {
        A[top] = 0;
        getCode(root->left, A, top + 1, out, in);
    }

    if(root->right)
    {
        A[top] = 1;
        getCode(root->right, A, top+1, out, in);
    }

    if(!(root->left) && !(root->right)) //LeafNode
    {
        cout << "Character: " << root->letter << "  ";
        cout << "Code: ";
        for(int i=0;i<top;i++)
        {
            cout << A[i];
        }
        //int encodearray[i] = A[i];
        cout << endl;
    }
}

void HuffmanTree(Node * FrequencyTable[], int &Flength)
{
    Node *left=extractMin(FrequencyTable,Flength);
    Node *right=extractMin(FrequencyTable,Flength);
    int sum = left->frequency + right->frequency;
  //  insertNode(FrequencyTable, newNode('\0',sum,left,right),Flength);
}

void selectionSort(string & text, unsigned int length)
{
    char tempChar= ' ';
    for(unsigned int i=0;i<length;i++)
    {
        char minVal=text[i];
        for(unsigned int j=i+1;j<length;j++)
        {
            if(text[j]<minVal)
            {
                //swap values
                tempChar=text[j];
                text[j]=minVal;
                text[i]=tempChar;
                minVal=tempChar;
            }
        }
    }
}
*/

void sanitize(string &text)
{
     for(unsigned int i=0;i<text.length();i++)
    {
        if(int(text[i])<32 || (int(text[i])>32 && int(text[i])<48) || (int(text[i])>57 && int(text[i])<65) ||
        (int(text[i])>90 && int(text[i])<97) || int(text[i])>122)
            text[i]=' ';
    }
}

string selectionSort(string text, int length)
{
    char tempChar= ' ';
    for(unsigned int i=0;i<length;i++)
    {
        char minVal=text[i];
        for(unsigned int j=i+1;j<length;j++)
        {
            if(text[j] < minVal)
            {
                //swap values
                tempChar=text[j];
                text[j]=minVal;
                text[i]=tempChar;
                minVal=tempChar;
            }
        }
    }
    cout << text << " sorted" << endl;
    return text;
}

void decode(Node * root, string encodedtext[], int textlength)
{
    cout << "Entering decoding function" << endl;
    //cout << text << endl;
    Node * current = root;
    string decoded;
    char chartext[textlength + 1];
    encodedtext->copy(chartext, textlength + 1);
    chartext[textlength] = '\0';
    for(int i = 0; i < textlength; i++)
    {
        if(chartext[i] == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        if(current->left == nullptr && current->right == nullptr)
        {
            decoded = decoded + current->letter;
            current = root;
        }
    }
    cout << decoded << " decoded" << endl;
}

string encode(string word, char letter[], string encodedtext[])
{
    ofstream out;
    out.open("encodedtext.txt");
    string encoded;
    bool found = false;
    cout << word << ": raw text" << endl;
    for(int i = 0; i < word.length(); i++)
    {
        found = false;
        int k = 0;
        while(!found)
        {
            if(word[i] == letter[k])
            {
                encoded.append(encodedtext[k]);
                found = true;
            }
            else
            {
                k++;
            }
        }
    }
    cout << encoded << " encoded word" << endl;
    out << encoded << endl;
    return encoded;
}

void arrangeletters(char letter[])
{
    ifstream in;
    int i = 0;
    char character;
    in.open("characters.txt");
    while(in >> character)
    {
        letter[i] = character;
        i++;
    }
    in.close();
}

int main()
{
    ofstream out;
    ifstream in ("./textfile.txt");
    string rawtext;
    //in.open("./textfile.txt");
    bool open = in.is_open();
    while(in.is_open() && !in.eof()){
        in >> rawtext;
        cout << rawtext << endl;
    }
    in.close();
    sanitize(rawtext);
    int size = rawtext.length();
    string sortedtext = selectionSort(rawtext, size);
    int numchar = 0;
    char letter[size]; //array of unique chars
    int freq[size]; //parallel to letter[] the freq of each char
    int counter = 0;
    for(int i = 0; i < size; i++)
    {
        if(sortedtext[i] != sortedtext[i+1])
        {
            letter[counter] = sortedtext[i];
            numchar++;
            counter++;
        }
    }
    frequencyCount(sortedtext, letter, freq, numchar);
    Node * root = HuffmanTree(letter, freq, numchar);
    in.open("encoded.txt");
    string code;
    string encodedtext[numchar];
    int i = 0;
    while(in >> code)
    {
        encodedtext[i] = code;
        cout << encodedtext[i] << endl;

        i++;
    }
    in.close();
    out.open("encoded.txt");
    out.close();
    arrangeletters(letter);
    out.open("characters.txt");
    out.close();
    in.open("textfile.txt");
    in >> rawtext;
    in.close();
    string encoded = encode(rawtext, letter, encodedtext);
    int textlength = encoded.length();
    decode(root, &encoded, textlength);

    return 0;
}
