#pragma once
#include <string>

namespace str = std::string;

struct Node
{//basic building block for compact trie
    char head;          //can be null for root, first char in label
    str label;          //can be null for root, but holds compacted strings in words
    bool eow;           //"end of word" flag to tell whether this node ends a word
    tnode::Node *right_sib;    //right sibling
    tnode::Node *child1;       //first child

    //constructors
    Node(); //default
    Node(str s); //custom
    findSibling(char target_head);  //finds the sibling containing the target_head

    //destructor
    ~Node();
}

#include "tnode.cpp"    //include implementation for import into future files