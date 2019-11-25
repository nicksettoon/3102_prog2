#pragma once
#include "hsh_node.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

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