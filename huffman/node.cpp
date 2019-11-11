#pragma once
#include "node.h"

node::Node() //default constructor
    : data(-1), freq(-1){}

node::Node(char dat, int f) //custom constructor
{
    this->data = dat; //init letter
    this->freq = f; //give key
    this->left = nullptr;
    this->right = nullptr;
}

/*
Old, manual constructor
Node * newNode(char c, int frequency)
{
    Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->letter = c;
    temp->frequency = frequency;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

*/
