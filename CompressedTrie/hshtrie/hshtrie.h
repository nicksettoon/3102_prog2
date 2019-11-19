#pragma once
#include "hshnode.h"
// #include <string> //included in node.h
// #include <iostream> //included in node.h
// #include <stdio.h> //included in node.h
// #include <memory> //included in node.h

struct HashEntry
{
    Node* parent;   //pointer to parent of relationship
    Node* child;    //pointer to child of relationship
    char c;         //head of child node
    HashEntry* nextentry; //pointer to next entry in the HashEntry's linked list.

    HashEntry(Node* parent_in);
    HashEntry(Node* parent_in, char head_in, Node* child_in);
    bool searchList();    
};

class HashTrie
{
    const int size;   //size of the hash table
    HashEntry* hshtable[size]; //array of HashEntries
    
    HashTrie(int size_in); //basic constructor
    HashEntry* hash(int parent_id, char child_head); //hash function to find child with given child_head
    bool insert(std::string word_in);  //insert function
    bool search(std::string word_in);  //search function, uses hash()
};