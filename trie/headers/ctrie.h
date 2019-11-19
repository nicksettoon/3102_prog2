#pragma once
// #include <string>   //included in llnode.h
// #include <iostream> //included in llnode.h
// #include <memory>   //included in llnode.h
// #include <stdio.h>  //included in llnode.h
#include "llnode.h"



class Insertable
{//insert interface for CompTrie classes
    //functions
    // virtual void* insert() = 0; //virtual function forcing subclasses to implement
    // virtual void add() = 0; //virtual function forcing subclasses to implement
    // virtual void edit() = 0; //virtual function forcing subclasses to implement
};

class CompTrie : public Insertable
{/*trie whose nodes with only one child have been compressed into one node @ parent node.
    All internal nodes of this trie must have at least two children.
    This is a base class for HSCompTrie and LLCompTrie.*/
    public:
        //constructors
        CompTrie(); //default
        // CompTrie(char term, node* root); //initializes Trie with given root node
        // CompTrie(char term, str raw_text[]); //initializes Trie with array of words
        std::shared_ptr<compResult> compareLabel(std::shared_ptr<LLNode> target_node, std::string target_label);
        ~CompTrie(); //default
    private:
        //functions
            //compares target_label to label @ target_node
        //destructors
};