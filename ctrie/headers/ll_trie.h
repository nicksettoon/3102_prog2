#pragma once
#include "ll_node.h"
#include "hsh_trie.h"


class LinkedList
{
private:
    // LLNode * newNode(char, string, bool, Node *, Node *);
    std::string findSubstring(int, int, std::string);
public:
    LLNode* root;
    LinkedList(); //constructor
    // typedef void(*printFunc)(std::string); //define type for passing functions

    void insert(std::string word_in);
    void search(std::string target_word);
    void getNodes(HashTrie* target_hashtrie, LLNode* start_parent, LLNode* start_node, std::string prefix_context);
};
