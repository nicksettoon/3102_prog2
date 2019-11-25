#pragma once
#include <fstream>
#include <chrono>
#include "ll_node.h"
#include "hsh_trie.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

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
    void testTrieSearch();
};
