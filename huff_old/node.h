#pragma once

struct Node
{
    char data;  //char being encoded
    int freq;   //key minHeap uses to sort the nodes
    Node *left;
    Node *right;

    Node(); //default constructor
    Node(char dat, int f); //custom constructor
}

#include "node.cpp" //include implementation for import into heap.h