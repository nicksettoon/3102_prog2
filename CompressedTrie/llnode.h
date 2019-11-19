#pragma once
#include<iostream>
#include<string>

struct LLNode
{
    char letter; //first character
    std::string label; //word
    bool isWord; //if this node is a word or not
    LLNode* firstChild; //child of parent
    LLNode* rightSibling; //siblings of first child

    LLNode(char letter_in, std::string word_in, bool eow_in, LLNode* firstChild, LLNode* rightSibling); //constructor
};