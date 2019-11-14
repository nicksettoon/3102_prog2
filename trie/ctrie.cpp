#include "headers/tools.h"
#include "headers/ctrie.h"
#include <stdio.h>
/*FILL_LATER*/
//function parameters are underscored. function variables are just appended.

trie::CompTrie()
    : term('$') 
{//default constructor
    prt("Entering default CompTrie constructor."); //notification
    node* newroot = new node;   //make new, empty node with default constructor
    this->root = newroot;   //assign it to this CompTrie's root ptr
}

node* trie::findWord(str target_word)
{//finds word in trie. Not recursively called
    char wordhead = target_word[0]; //get first letter of the given word.
    node* targetnode = this->root->child1.findHead(wordhead);  //try to find the node with that letter    

    if(targetnode == nullptr)
    {//if findHead() didn't find a child with target wordhead at first level of tree
        printf("%s not in trie.", target_word);
        return targetnode;
    }
    else
    {//figure out if target_word's label is substring of label
        str targetlabel = target_word.substr(1);
        compResult result = compareLabel(targetnode, targetlabel);
        switch (result.case)
        {
        case CaseSuperstr:
            //move one level down
            //find new target_node
            //compare labels again
            break;
        case CaseDiv:
            //1. split node_label @ i
            //2. make new node for remaining node_label
                //2.1 set eow for that node to 1
            //4. set eow on current node to 0
            //5. make new node for remaining target_label
            break;
        case CaseSubstr:
            //1. split label @ i
            //2. make new_node for split label
                //2.1 set eow for new_node to 1
            //4. set eow on target_node to 1
            break;
        case CaseInTrie:
            //1. change eow flag on target_node to 1
            break;
        default
            // throw exception;
            prt("Somehow result.case is not correct in findWord()")
            break;
        }
    }
}

trie::compResult trie::compareLabel(node* target_node, str target_label)
{//Compares the target_label to the node_label at target_node.
 //returns case the comparison falls under, as well as the index at which to split if necessary
    str& t_l = target_label;            //reference ("target label") to make it easier to type
    str& n_l = target_node->label;      //reference ("node label") to make it easier to type

    int i = 0;  //initialize iterator for moving through target_node's label below
    trie::compResult result;    //instantiate struct for returning later

    for(char c:t_l) //What if comparing single letter which already exists at target_node? c=null?
    {//for each char in the target_label, compare it against the label @ the target_node

        if(i == n_l.length())
        {//case 1: If the index for node_label is equal to the  length of node_label and
         //the for loop is still going, the target_label is a superstring of the node_label
            result.index = -1;  //return bad index so no splitting can occur
            result.compCase = CaseSuperstr; //set case to show the target_label is a superstring of the node_label
            return result;
        }

        if(c == n_l[i])
        {//If current char in target_label is the same as the char @ same position in the node_label
            i++;    //move to next char in node_label and next iteration of for loop
        }
        else
        {//case 2.1: Neither target_label nor node_label have run out of chars, but the current chars differ
         //the target_label diverges from the node_label
            result.index = i; //return the index at which they diverge for splitting later
            result.compCase = CaseDiv; //set case to show the target_label diverges from the node label at i
            return result; 
        }
    }
    //all chars in target_label have been compared
    if(i < n_l.length())
    {//case 2.2: 1. The for loop ended without differing strings, and 2. end of node_label was not reached
     //The target_label is a substring of target_node's label.
        result.index = i; //return the index at which they diverge for splitting later
        result.compCase = CaseSubstr;   //set case to show the target_label is a substring of the label
        return result;
    }
    else if(i == n_l.length())
    {//case 3: 1. The for loop ended without differing strings, and 2. the entire target_node's label was compared, 
     //then the target_label is the node_label.
        result.index = -1;
        result.compCase = CaseInTrie;   //set case to show the target_label is in the trie
        return result;
    }
    else
        prt("Something went wrong in ctrie::compareLabel! HALP!");
}

bool trie::insertLL(str target_label)
{//insert word via linked list implementation
    prt("Entering insertLL")

    if(this->root->child1 == nullptr)
    {//if there is no first child of this trie
       this->root->child1 = new node(word); //make one with the given word
       return 1;    //return successful insert
    }
    else
    {//find node where word should be inserted
        node* insertnode = trie::findWord(target_label);
        if(insertnode->eow)
        {//if the discovered node is the end node of a full word

        }
    }

}

// trie::~CompTrie()
// {//delete all nodes from the memory heap and clean up other stuff if necessary
    // prt("Entering CompTrie destructor."); //notification
// }