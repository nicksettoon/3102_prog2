#pragma once
#include <string>
#include <iostream>
// #include "tools.h"
/*FILL_LATER*/

using str = std::string;    //type abstraction for easier use

struct LLNode
{//basic building block for compact trie
    char head;          //can be null for root, first char in label
    str label;          //can be null for root, but holds compacted strings in words
    bool eow;           //"end of word" flag to tell whether or not this node ends a word
    LLNode* rightsib;    //right sibling
    LLNode* child1;       //first child

    //constructors
    LLNode(); //default
    LLNode(str word_in, bool e_o_w); //basic custom constructor
    LLNode(str word_in, bool e_o_w, LLNode* right_sib, LLNode* child_1);  //full custom constructor
    LLNode* findHead(char target_head);  //finds the sibling containing the target_head
    void printSibs(); //prints the sibling nodes from the target_node down the line
    void print(); //prints the node instance

    //destructor
    ~LLNode();
};