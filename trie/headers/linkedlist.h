#pragma once
#include "llnode.h"
// #include <string>   //included in llnode.h
// #include <iostream> //included in llnode.h
// #include <memory>   //included in llnode.h
// #include <stdio.h>  //included in llnode.h

class LinkedList
{
private:
    std::shared_ptr<LLNode> root;
    // std::shared_ptr<LLNode> makeNode(char, string, bool, Node *, Node *);
    string findSubstring(int, int, string);
    
    std::shared_ptr<compResult> compareLabel(node target_node, str target_label)
public:
    LinkedList(); //constructor
    // void insert(string);
    // bool search(string);
};

enum CompCase
{//restrict possible cases of compResult
    CaseSubstr,     //the target_label is a substring of the node_label
    CaseDiv,        //the target_word diverges from the label @ i
    CaseSuperstr,   //the target_word is a superstring of the label (label diverges from target_word @ i)
    CaseInTrie,     //the exact target_word is in the trie
    CaseNotInTrie,  //the target_word is not in the trie.
    NoCase          //state for default constructor
};

struct compResult
{//struct for returning things from trie::compareLabel()
    int index;  //index at which the strings need to be split
    CompCase resultcase; //resulting case of the if statements
    bool endsearch;
    compResult(int index_in, CompCase case_in);
};
