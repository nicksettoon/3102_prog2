#pragma once
#include <string>
#include "tnode.h"

using node = tnode::Node;
using str = std::string;

enum CompCase
{//restrict possible cases of compResult
    CaseSubstr,     //the target_label is a substring of the node_label
    CaseDiv,        //the target_word diverges from the label @ i
    CaseSuperstr,   //the target_word is a superstring of the label (label diverges from target_word @ i)
    CaseInTrie      //the exact target_word is in the trie
};

struct compResult
{//struct for returning things from trie::compareLabel()
    int index;  //index at which the strings need to be split
    CompCase resultcase; //resulting case of the if statements
    compResult(int index_in, CompCase case_in);
};

struct searchStack
{//struct for passing the state of a search between functions
    //fields
    char wordhead;      //current wordhead of word being searched.
    node* targetnode;   //current targetnode for compareLabel()
    str targetlabel;    //current targetlabel for compareLabel()
    compResult* result; //last result of compareLabel()
    //constructors
    searchStack(str target_word, node* child_1);  //constructor
};