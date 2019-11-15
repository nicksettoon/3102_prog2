#pragma once
#include <string>
#include <iostream>
// #include "tools.h"
/*FILL_LATER*/

using str = std::string;    //type abstraction for easier use

namespace tnode
{//namespace definition for use elsewhere
    
    struct Node
    {//basic building block for compact trie
        char head;          //can be null for root, first char in label
        str label;          //can be null for root, but holds compacted strings in words
        bool eow;           //"end of word" flag to tell whether or not this node ends a word
        Node* rightsib;    //right sibling
        Node* child1;       //first child

        //constructors
        Node(); //default
        Node(str word_in, bool e_o_w); //basic custom constructor
        Node(str word_in, bool e_o_w, Node* right_sib, Node* child_1);  //full custom constructor
        Node* findHead(char target_head);  //finds the sibling containing the target_head
        void printSibs(); //prints the sibling nodes from the target_node down the line
        void print(); //prints the node instance

        //destructor
        ~Node();
    };
}