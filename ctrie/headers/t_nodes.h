#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <memory>

struct HSHnode
{
    char head;
    std::string label;
    bool wordEnd;

    HSHnode(char head_in, std::string label_in, bool wordEnd_in); //full constructor
    void print(); 
};

struct LLnode
{
    char head;
    std::string label;
    bool wordEnd;
    LLnode* firstChild; //child of parent
    LLnode* rightSibling; //siblings of first child

    LLnode(char head_in, std::string label_in, bool wordEnd_in, LLnode* child_in, LLnode* r_sib_in); //constructor
    void print();
};