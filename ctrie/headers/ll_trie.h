#pragma once
#include <fstream>
#include <chrono>
#include "t_nodes.h"
#include "hsh_trie.h"
// #include <string>    //included in t_nodes.h
// #include <iostream>  //included in t_nodes.h
// #include <stdio.h>   //included in t_nodes.h
// #include <memory>    //included in t_nodes.h

class LLtrie
{
private:
    // LLnode * newNode(char, string, bool, Node *, Node *);
    std::string findSubstring(int, int, std::string);
public:
    LLnode* root;
    LLtrie(); //constructor
    // typedef void(*printFunc)(std::string); //define type for passing functions

    void insert(std::string word_in);
    void search(std::string target_word);
    void preorderTraversal(HSHtrie* target_hashtrie, LLnode* start_parent, LLnode* start_node, std::string prefix_context);
    // void preorderTraversal(HSHtrie* target_hashtrie, LLnode* start_node, std::string prefix_context);
    void testSearch();
};
