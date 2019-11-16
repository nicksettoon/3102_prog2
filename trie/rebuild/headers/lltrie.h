#pragma once
#include "ctrie.h"
// #include "llnode.h" //included in ctrie.h
// #include <memory>   //included in llnode.h
// #include <string>   //included in llnode.h
// #include <iostream>   //included in llnode.h

struct searchStack
{//struct for passing the state of a search between functions
    //fields
    char head;      //current wordhead of word being searched.
    std::shared_ptr<LLNode> targetnode;   //current targetnode for compareLabel()
    std::string targetlabel;    //current targetlabel for compareLabel()
    std::shared_ptr<compResult> result; //last result of compareLabel()
    //constructors
    searchStack(std::string target_word, std::shared_ptr<LLNode> child_1);  //constructor
};


class LLCompTrie : public CompTrie
{//Child class of CompTrie which implements traversal and insertion of nodes via linked lists.
    public:
        //fields
        std::shared_ptr<LLNode> root;  //pointer to the root node of the trie instance

        //constructors
        LLCompTrie();

        //functions
        std::shared_ptr<LLNode> insert(std::string target_word);  //front end for insertion
        // node* search(str target_word);  //front end for search
    private:
        //functions
        std::shared_ptr<searchStack> searchTrie(std::shared_ptr<searchStack> stack_in); //recursive search function
        void add(std::shared_ptr<LLNode> in_node, std::shared_ptr<LLNode> neighbor, bool child);  //actually creates and adds a node
};