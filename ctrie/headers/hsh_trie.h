#pragma once
#include <vector>
#include <math.h>
#include <fstream>
#include <chrono>
#include "ll_node.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

struct EDGnode
{//struct holding the details of the relationship between two HshNodes in a HSHtrie i.e. an edge
    //CONSTRUCTORS//
    EDGnode(LLnode* parent_in, LLnode* child_in); //base constructor
    //MEMBER FUNCTIONS//
    void print(); //prints EDGnode's information

private:
    //FIELDS//
    LLnode* parent;   //pointer to parent of relationship
    LLnode* child;    //pointer to child of relationship
    EDGnode* nextedge; //pointer to next entry in the EDGnode's linked list.
    char childhead;         //head of child HSHnode
    //MEMBER FUNCTIONS//
    EDGnode* searchList(LLnode* target_parent, char target_childhead);    
};

class HSHtrie
{
public:
    //FIELDS//
    LLnode* handle;   //root HSHnode of the HSHtrie
    const int size;   //size of the hashtable
    std::vector<EDGnode*> edgetable; //array of EDGnode pointers
    //ENUMS AND STRUCTS//
    enum Hashes{ prime };
    struct searchResult
    {//struct for returning things from HSHtrie::compareLabel()
        //ENUMS//
        enum CompCase
        {//restrict possible cases of searchResult
            CaseSubstr,     //the target_label is a substring of the node_label
            CaseDiv,        //the target_word diverges from the label @ i
            CaseSuperstr,   //the target_word is a superstring of the label (label diverges from target_word @ i)
            CaseInTrie,     //the exact target_word is in the trie
            CaseNotInTrie,  //the target_word is not in the trie.
            NoCase          //state for default constructor
        };
        //FIELDS//
        int index;  //index at which the strings need to be split
        // bool locationfound; // bool indicating whether more comparisons need to be made
        CompCase resultcase; //resulting case of the if statements
        LLnode* currentnode; 
        std::string currentlabel;
        //CONSTRUCTORS//
        searchResult(int index_in, CompCase case_in);
    };
    //FRIENDS//
    friend struct EDGnode;
    //CONSTRUCTORS//
    HSHtrie(int size_in, HSHtrie::Hashes hash_type); //basic
    //MEMBER FUNCTIONS//
    bool insertEdge(LLnode* parent_in, LLnode* child_in);  //insert edge into trie function
    std::shared_ptr<searchResult> search(std::shared_ptr<searchResult> result_in);  //search function, uses hash()
    void testTrieSearch(std::shared_ptr<std::ifstream>stream_in);
    void setHash(Hashes hash_type);  //set the desired hash function for the HSHtrie
    // bool insertString(std::string string_in);    //insert string into HSHtrie
    // void preorderTraversal(LLnode* start_node, std::string prefix_context);

private:
    std::shared_ptr<searchResult> compareLabel(std::shared_ptr<searchResult> result_in, LLnode* target_node); //compares the label at a given HSHnode
    EDGnode* getEdge(LLnode* parent_in, char child_in); //hashes and handles collisions
    int getHash(LLnode* target_node, char head_in); //abstracts syntax of using hash()

    //enables variable hash function for trie
    int (HSHtrie::*hash)(int, char);

    //HASH FUNCTIONS//
    int primeHash(int parent_addr, char child_head)
    {//hash with basic arthimetic and prime mod
        int b = 5;
        int result = ((parent_addr + (int)child_head * (int)std::pow(b,31)) % this->size);
        return result;
    }
};
