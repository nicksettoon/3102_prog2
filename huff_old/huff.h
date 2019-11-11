#pragma once
#include "heap.h" //includes heap and node.

class HuffmanTree
{
    node::Node * root; 
    int array[500];
    int parent = 0;
    HuffmanTree();  //default constructor
    HuffmanTree(char letter[], int frequency[], int size);  //custom constructor
    void printHuffman(Node * root, int array[], int parent);
    string getCode(); //get huffman code (encoding)

public:    
    void decode(string str); //decodes the given string via the huffman scheme
    void encode(string str); //encodes the given string via the huffman scheme

    
}

#include "huff.cpp" //include huff implementation for import into main.cpp