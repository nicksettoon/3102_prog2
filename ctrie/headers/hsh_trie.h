#pragma once
#include <vector>   //needed for edgetable
#include <math.h>   //needed for hash functions
#include <fstream>  //needed for testSearch
#include <chrono>   //needed for testSearch
#include "t_nodes.h"
// #include <string>    //included in t_nodes.h
// #include <iostream>  //included in t_nodes.h
// #include <stdio.h>   //included in t_nodes.h
// #include <memory>    //included in t_nodes.h

struct EDGnode
{//struct holding the details of the relationship between two HshNodes in a HSHtrie i.e. an edge
    //CONSTRUCTORS//
    EDGnode(LLnode* parent_in, LLnode* child_in); //base constructor
    //MEMBER FUNCTIONS//
    void print(); //prints EDGnode's information
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
    struct searchStack
    {//struct for returning things from HSHtrie::compareSubstr()
        //ENUMS//
        enum CompCase
        {//restrict possible cases of searchStack
            CaseSubstr,     //current substring of targetstring is a substring of the currentnode->label
            CaseDiv,        //current substring of targetstring diverges from currentnode->label @ index
            CaseSuperstr,   //current substring of targetstring is a superstring of the currentnode->label (label diverges current substring of targetstring @ index)
            CaseFound,      //the current substring of targetstring is in the trie but isn't marked as end of a word
            CaseInTrie,     //the targetstring is already in the trie
            CaseNotInTrie,  //the targetstring is not in the trie
            NoCase          //state for default constructor
        };
        //FIELDS//
        int index;                  //index at which the strings need to be split
        CompCase resultcase;        //resulting case of the if statements
        LLnode* currentnode;        //the node being searched. the one calling compareSubstr
        EDGnode* currentedge;        //the current edge being used. Currentnode is the parent of this edge
        std::string targetlabel;    //the label compareSubstr compares against
        std::string targetstring;   //the original string the search stack was made to find
        //CONSTRUCTORS//
        searchStack(int index_in, CompCase case_in, std::string string_in, LLnode* start_node);
    };
    //FRIENDS//
    friend struct EDGnode;
    //CONSTRUCTORS//
    HSHtrie(int size_in, HSHtrie::Hashes hash_type); //basic
    //MEMBER FUNCTIONS//
    bool insertEdge(LLnode* parent_in, LLnode* child_in);  //insert edge into trie function
    std::shared_ptr<searchStack> search(std::shared_ptr<searchStack> stack_in, bool insert_flag);  //search function, uses hash()
    void testSearch();
    void setHash(Hashes hash_type);  //set the desired hash function for the HSHtrie
    bool insertString(std::string string_in);    //insert string into HSHtrie
    // void preorderTraversal(LLnode* start_node, std::string prefix_context);

private:
    std::shared_ptr<searchStack> compareSubstr(std::shared_ptr<searchStack> stack_in); //compares the label at a given HSHnode
    EDGnode* getEDGnode(LLnode* parent_in, char child_in); //hashes and handles collisions
    int getHash(LLnode* target_node, char head_in); //abstracts syntax of using hash()

    //enables variable hash function for trie
    int (HSHtrie::*hash)(int, char);

    //HASH FUNCTIONS//
    int primeHash(int parent_addr, char child_head);
    // {//hash with basic arthimetic and prime mod
    //     int b = 5;
    //     int result = ((parent_addr + (int)child_head * (int)std::pow(b,31)) % this->size);
    //     return result;
    // }
};
