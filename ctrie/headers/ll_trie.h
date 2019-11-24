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
    typedef void(*nodeVisitFunc)(std::string); //define type for passing functions

    nodeVisitFunc insert(std::string word_in);
    nodeVisitFunc search(std::string target_word);
    void getNodes(nodeVisitFunc visit_func, LLNode* start_node, std::string prefix_context, HashTrie* target_trie);
};
