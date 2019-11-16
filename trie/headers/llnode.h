#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <stdio.h>

struct LLNode
{//basic building block for compact trie
    char head;          //can be null for root, first char in label
    std::string label;          //can be null for root, but holds compacted strings in words
    bool eow;           //"end of word" flag to tell whether or not this node ends a word
    std::shared_ptr<LLNode> leftsib;    //left sibling
    std::shared_ptr<LLNode> rightsib;    //right sibling
    std::shared_ptr<LLNode> child1;       //first child

    //constructors
    LLNode(); //default
    LLNode(char head_in); //custom constructor
    LLNode(std::string word_in, bool e_o_w); //basic custom constructor
    // LLNode(std::string word_in, bool e_o_w, std::shared_ptr<LLNode> leftsib, std::shared_ptr<LLNode> right_sib, std::shared_ptr<LLNode> child_1);  //full custom constructor

    //functions
    std::shared_ptr<LLNode> findHead(char target_head);  //finds the sibling containing the target_head
    void printSibs(); //prints the sibling nodes from the target_node down the line
    void print(); //prints the node instance
    void edit(std::string new_label, bool e_o_w);   //edits a node
    void deleteNode(char c); //finds node with head c and deletes it

    //destructor
    ~LLNode();
};