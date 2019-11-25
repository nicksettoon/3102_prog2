#include "headers/ll_trie.h"
#include "headers/hsh_trie.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

using str = std::string;
using Fstream = std::ifstream;

// void LLtrie::preorderTraversal(HSHtrie* target_hashtrie, LLnode* current_node, str prefix_context)
void LLtrie::preorderTraversal(HSHtrie* target_hashtrie, LLnode* parent_in, LLnode* current_node, str prefix_context)
{//traverses the trie in preorder giving each parent child relationship to the HSHtrie insert function
    if(current_node == nullptr){return;}
    //UPDATE PREFIX//
    prefix_context = prefix_context + current_node->label;

    if(current_node->wordEnd && prefix_context != "acdeme")
        std::cout << prefix_context << std::endl;

    //INSERT THE HSHedge//
    // target_hashtrie->insertEdge(parent_in, current_node);
    if(parent_in != nullptr)
    {
        std::cout << "parent: " << parent_in->label << std::endl;
        std::cout << "child: " << current_node->label << std::endl;
        std::cout << std::endl;
    }

    LLnode* nextnode = current_node->firstChild;
    while (nextnode != nullptr)//if there is a child, visit that child
    {
        // preorderTraversal(target_hashtrie, current_node, nextnode, prefix_context);
        preorderTraversal(target_hashtrie, current_node, nextnode, prefix_context);
        nextnode = nextnode->rightSibling;
        while (nextnode != nullptr)
        {
            preorderTraversal(target_hashtrie, current_node, nextnode, prefix_context);
            nextnode = nextnode->rightSibling;
        }
    }
}

void LLtrie::testTrieSearch()
{//runs searches for every word in the stream_in and outputs the time it takes in microseconds
    std::ifstream inputstream("word_list.txt");
    str targetword;
    //START TIMER AND BEGIN//
    auto start = std::chrono::high_resolution_clock::now();
    while (inputstream >> targetword)
    {
        this->search(targetword);
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "Linked list performance for search: " << microseconds << " micro-sec" << std::endl;
    inputstream.close();
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

void LLtrie::search(str word_in)
{
    LLnode *currentnode = root->firstChild;
    bool found = false;
    if(currentnode == nullptr) //empty trie
    {
        std::cout << "Trie is empty." << std::endl;
        return;
    }
    else //not empty trie, start search
    {
        int i = 0;
        // while()
            while(currentnode != nullptr && currentnode->head < word_in[i])
            {
                currentnode= currentnode->rightSibling; //continue through level
            }
            if(currentnode == nullptr) //reached end, not found
            {
                std::cout << word_in << " is not found " << std::endl;
                return;
            }
            else //continue search
            {
                i++;
                while(!found && i < currentnode->label.length())
                {
                    if(word_in[i] == currentnode->label[i]) //still matching, continue
                    {
                        i++;
                    }
                    else
                    {
                         currentnode = currentnode->firstChild; //next level
                         found = true;
                    }
                }
            }
        std::cout << word_in << " found." << std::endl;
    }
}