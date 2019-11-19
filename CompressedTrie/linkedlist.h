#pragma once
#include "llnode.h"

class LinkedList
{
private:
    LLNode * root;
    // LLNode * newNode(char, string, bool, Node *, Node *);
    std::string findSubstring(int, int, std::string);
public:
    LinkedList(); //constructor
    void insert(std::string);
    void search(std::string);
};
