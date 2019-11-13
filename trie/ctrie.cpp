#include "headers/tools.h"
#include "headers/ctrie.h"
#include <stdio.h>
/*FILL_LATER*/


trie::CompTrie()
    : term('$') 
{//default constructor
    prt("Entering default CompTrie constructor."); //notification
    node* newroot = new node;   //make new, empty node with default constructor
    this->root = newroot;   //assign it to this CompTrie's root ptr
}

node* trie::findWord(str target_word)
{//finds word in trie.
    char wordhead = target_word[0]; //get first letter of the given word.
    node* targetnode = this->root->child1.findHead(wordhead);  //try to find the node with that letter    

    if(targetnode == nullptr)
    {//if findHead() didn't find a child with target wordhead
        printf("%s not in trie.", target_word);
        return targetnode;
    }
    else()
    {//figure out if word is substring of label
        trie::checkSubstring(targetnode, target_word);
    }
}

int trie::checkSubstr(node* target_node, str target_word)
{//figures out if target_word is a substring of a label at target_node
    str& t_w = target_word;  //alias (reference) for target_word to make it easier to type
    int i = 0;  //initialize iterator for moving through target_node's label below

    for(char c:t_w)
    {//for each char in the target_word
        //compare it against the label @ the target_node
        if(c == target_node->label[i])
        {//If current char in target_word is the same as the char @ same position in the node's label
            i++;    //move to next char in node's label and next iteration of for loop
        }
        else
        {//case 2.1: Neither target_word nor node's label have run out of chars, but the current chars differ
         //return the string index at which they diverge for splitting later
            //1. split label @ i
            //2. make new node for split label
                //3. set eow for new node to 1
            //4. set eow on current node to 0
            //5. make new node for remaining target_word
           return i; 
        }
    }
    if(i == t_w.length())
    {//case 1: If 1. for loop ended without differing strings and 2. the entire target_node's label was compared, 
     //then the node's label is the target label.
        target_node->eow = 1;   //set eow flag for target_node to 1
        return -1;  //return -1 so any splitting that happens throws an invalid index error
    }
    else if(i < t_w.length())
    {//case 2.2: 1. The for loop ended without differeing strings and 2. end of target_node's label was not reached
     //The target_word is a substring of target_node's label.
     //treat similar to case 2.1, but 
        //1. split label @ i
        //2. make new node for split label
            //3. set eow for new node to 1
        //4. set eow on current node to 1

        return i;
    }
    else
        prt("something went wrong in ctrie::checkSubstring! HALP!");
}

bool trie::insertLL(str target_word)
{//insert word via linked list implementation
    prt("Entering insertLL")

    if(this->root->child1 == nullptr)
    {//if there is no first child of this trie
       this->root->child1 = new node(word); //make one with the given word
       return 1;    //return successful insert
    }
    else
    {//find node where word should be inserted
        node* insertnode = trie::findWord(target_word);
        if(insertnode->eow)
        {//if the discovered node is the end node of a full word

        }
    }

}

// trie::~CompTrie()
// {//delete all nodes from the memory heap and clean up other stuff if necessary
    // prt("Entering CompTrie destructor."); //notification
// }