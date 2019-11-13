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

bool trie::checkSubstring(node* target_node, str target_word)
{//figures out if target_word is a substring of a label at target_node
    str targetlabel = target_word.substr(1);  //erase the first letter from the word
    int t_w_size = sizeof(targetlabel)  //get size of targetlabel
    int i = 0; 
    for(char c:targetlabel)
    {
        if(c == target_node->label[i])
        {//if current char in targetlabel is the same as the ith char in the node's label
            i++;
        }
        else
        {//case where neither the targetlabel or node's label have run out of chars, but they differ
         //return the string index at which they diverge from one another
           return i; 
        }
    }
    if(i < )
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