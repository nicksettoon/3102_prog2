#include "headers/ll_trie.h"
#include "headers/hsh_trie.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

using str = std::string;
using Fstream = std::shared_ptr<std::ifstream>;

void LLtrie::preorderTraversal(HSHtrie* target_hashtrie, LLnode* parent_in, LLnode* current_node, str prefix_context)
{//traverses the trie in preorder giving each parent child relationship to the HSHtrie insert function
    if(current_node == nullptr){return;}
    
    str prefix = prefix_context + current_node->label;
    target_hashtrie->insertEdge(parent_in, current_node);

    LLnode* nextnode = current_node->firstChild;
    if (nextnode != nullptr)
    {
        LLnode* parentout = current_node;
        preorderTraversal(target_hashtrie, parentout, nextnode, prefix);
    }
    else
        nextnode = current_node->rightSibling;

    while(nextnode != nullptr)
    {
        preorderTraversal(target_hashtrie, parent_in, nextnode, prefix);
        nextnode = nextnode->rightSibling;
    }
}

void LLtrie::testTrieSearch(Fstream stream_in)
{//runs searches for every word in the stream_in and outputs the time it takes in microseconds
    str targetword;
    auto start = std::chrono::high_resolution_clock::now();
    while((*stream_in) >> targetword)
    {
        this->search(targetword);
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "Linked list performance for search: " << microseconds << " micro-sec" << std::endl;
}

LLtrie::LLtrie() //constructor
{
    root = new LLnode('$', "", false, nullptr, nullptr);
}

str LLtrie::findSubstring(int i, int j, str word)
{
    str substring;
    if(i == j)
        substring = word[i];
    else
        substring = word.substr(i, j);

    return substring;
}

void LLtrie::insert(str word)
{
    // std::cout << "Inserting " << word << " into trie" << std::endl;

    if(root->firstChild == nullptr) //trie empty, insert first word
    {
        // std::cout << "Trie empty" << std::endl;
        LLnode * node = new LLnode(word[0], word, false, nullptr, nullptr);
        root->firstChild = node;
        return;
    }
    else //trie not empty, find where to insert
    {
        // std::cout << "Trie not empty" << std::endl;
        int i = 0;
        bool done = false;
        LLnode *rootchild = root->firstChild;
        LLnode *prevNode = nullptr;
        LLnode *parent = root;
        while(!done)
        {
            while(rootchild != nullptr && rootchild->label[i] < word[i]) //check char
            {
                prevNode = rootchild;
                rootchild = rootchild->rightSibling;
            }
            if(rootchild && rootchild->label[i] == word[i]) //if matches char, continue through label
            {
                bool stop = false; //bool stop to see when to stop
                i++;
                while(!stop && i < rootchild->label.length() && i < word.length())
                {
                    if(rootchild->label[i] == word[i]) //continue until word[i] does not match
                    {
                        i++;
                    }
                    else //word[i] doesn't match label[i] anymore, stop
                    {
                        stop = true;
                    }
                }
                if(stop)
                {
                    str firstChildLabel;
                    str rightSiblingLabel;
                    str newLabel = findSubstring(0, i - 1, rootchild->label); //find substring
                    bool add = false; //bool add
                    if(rootchild->label[i] > word[i])
                    {
                        firstChildLabel = findSubstring(i, word.length() - 1, word);
                        rightSiblingLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
                        add = true;
                    }
                    else
                    {
                        firstChildLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
                        rightSiblingLabel = findSubstring(i, word.length() - 1, word);
                    }
                    rootchild->wordEnd = false;
                    rootchild->label = newLabel; //new label for split case
                    LLnode *rightSib = new LLnode(rightSiblingLabel[0], rightSiblingLabel, true, nullptr, nullptr);
                    LLnode *leftChild = new LLnode(firstChildLabel[0], firstChildLabel, true, nullptr, rightSib);
                    if(rootchild->firstChild == nullptr)
                    {
                        rootchild->firstChild = leftChild;
                        done = true;
                    }
                    else
                    {
                        if(add)
                        {
                            rightSib->firstChild = rootchild->firstChild;
                        }
                        else
                        {
                            leftChild->firstChild = rootchild->firstChild;
                        }
                        rootchild->firstChild = leftChild;
                    }
                    done = true;
                }
                else //find prefix
                {

                    if(rootchild->label.length() < word.length()) //rootchild->label is prefix of word
                    {
                       if(rootchild->firstChild != nullptr) //go to next level
                       {
                           parent = rootchild;
                           prevNode = nullptr;
                           rootchild = rootchild->firstChild;
                           word = findSubstring(i, word.length() - 1, word);
                           i = 0;
                       }
                       else //make new node to be child for rootchild
                       {
                           str childLabel = findSubstring(i, word.length() - 1, word);
                           LLnode *newChild = new LLnode(childLabel[0], childLabel, true, nullptr, nullptr);
                           rootchild->firstChild = newChild;
                           done = true;
                       }
                    }
                    else if(rootchild->label.length() == word.length()) //same length
                    {
                         rootchild->wordEnd = true; //set to true
                         done = true;
                    }
                    else
                    {
                        str newChildLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
                        rootchild->label = findSubstring(0, rootchild->label.length() - 1, rootchild->label);
                        rootchild->wordEnd = true; //set to true
                        LLnode * node = new LLnode(newChildLabel[0], newChildLabel, true, rootchild->firstChild, nullptr);
                        rootchild->firstChild = node;
                        done = true;
                    }
                }
            }
            else
            {
                if(prevNode == nullptr) //new level, make firstChild of level
                {
                    LLnode* node = new LLnode(word[i], word, true, nullptr, rootchild);
                    parent->firstChild = node;
                    done = true;
                }
                else //make to be rightSibling
                {
                    LLnode * node = new LLnode(word[0], word, true, nullptr, rootchild);
                    prevNode->rightSibling = node;
                    done = true;
                }

            }
        }
        // std::cout << "Inserted." << std::endl;
    }
}

void LLtrie::search(str word)
{
    LLnode *rootchild = root->firstChild;
    if(rootchild == nullptr) //empty trie
    {
        return;
    }
    else //not empty trie, start searcg
    {
        int i = 0;
            while(rootchild != nullptr && rootchild->head < word[i])
            {
                rootchild = rootchild->rightSibling; //continue through level
            }
            if(rootchild == nullptr) //reached end, not found
            {
                std::cout << word << " is not found " << std::endl;
                return;
            }
            else //continue search
            {
                i++;
                bool found = false;
                while(!found && i < rootchild->label.length())
                {
                    if(word[i] == rootchild->label[i]) //still matching, continue
                    {
                        i++;
                    }
                    else
                    {
                         rootchild = rootchild->firstChild; //next level
                         found = true;
                    }
                }
            }
        std::cout << word << " found." << std::endl;
    }
}