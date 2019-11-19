#include "headers/linkedlist.h"

using snode = std::shared_ptr<LLNode>;
using comp = std::shared_ptr<compResult>;
using str = std::string;

void LinkedList::insert(str word_in)
{


}


findNodeResult LinkedList::findNode(char target_head)
{ //returns ptr to the sibling of this node instance or the instance itself if its head equals the target_head
    /*FILL*/
    printf("Finding head from starting node: \t");
    this->root->print();
    snode targetnode;  //FIX LATER//
    targetnode.reset(this);
    
    std::shared_ptr<findNodeResult> result;
    if(targetnode->head == target_head)
    {//if a child is found with the desired starting character
        result->targetnode = targetnode;
        result->res = atnode; 
        return result
    }
    else if(targetnode->head > target_head)
    {//if we passed the place where the node should have been
        result->targetnode = targetnode;
        result->res = left;
        return result;
    }
    else if(targetnode->rightsib == nullptr)
    {//if we reach the end of the linked list
        result->targetnode = targetnode;
        result->res = right;
        return result;
    }
    else
        return result = targetnode->rightsib->findNode(target_head);
}


comp LinkedList::compareLabel(snode target_node, str target_label)
{//Compares the target_label to the node_label at target_node.
 //returns case the comparison falls under, as well as the index at which to split if necessary
    printf("\nEntering compareLabel().\n");
    str& t_l = target_label;            //reference ("target label") to make it easier to type
    str& n_l = target_node->label;      //reference ("node label") to make it easier to type

    int i = 0;  //initialize iterator for moving through target_node's label below
    comp result = std::make_shared<compResult>(-1, NoCase);    //instantiate struct for returning later

    for(char c:t_l) //What if comparing single letter which already exists at target_node? c=null?
    {//for each char in the target_label, compare it against the label @ the target_node

        if(i == n_l.length())
        {//case 1: If the index for node_label is equal to the  length of node_label and
         //the for loop is still going, the target_label is a superstring of the node_label
            // prt("hit case 1");
            result->index = i;  //return index of where to begin 
            result->resultcase = CaseSuperstr; //case to show the target_label is a superstring of the node_label
            result->endsearch = 0;
            return result;
        }

        if(c == n_l[i])
        {//If current char in target_label is the same as the char @ same position in the node_label
            i++;    //move to next char in node_label and next iteration of for loop
        }
        else
        {//case 2.1: Neither target_label nor node_label have run out of chars, but the current chars differ
         //the target_label diverges from the node_label
            // prt("hit case 2.1");
            result->index = i; //return the index at which they diverge for splitting later
            result->resultcase = CaseDiv; //set case to show the target_label diverges from the node label at i
            result->endsearch = 1;
            return result; 
        }
    }
    //all chars in target_label have been compared
    if(i < n_l.length())
    {//case 2.2: 1. The for loop ended without differing strings, and 2. end of node_label was not reached
     //The target_label is a substring of target_node's label.
        // prt("hit case 2.1");
        result->index = i; //return the index at which they diverge for splitting later
        result->resultcase = CaseSubstr;   //set case to show the target_label is a substring of the label
        result->endsearch = 1;
        return result;
    }
    else if(i == n_l.length())
    {//case 3: 1. The for loop ended without differing strings, and 2. the entire target_node's label was compared, 
     //then the target_label is the node_label.
        // prt("hit case 3");
        result->index = -1;
        result->resultcase = CaseInTrie;   //set case to show the target_label is in the trie
        result->endsearch = 1;
        return result;
    }
    else
        // prt("Something went wrong in ctrie::compareLabel! HELP!");
        return result;
}

compResult::compResult(int index_in, CompCase case_in)
{//constructor for compResult struct
    index = index_in;
    resultcase = case_in;
    endsearch = 0;
}

enum CaseFindNodeResult
{
   left, atnode, right, none
}
struct findNodeResult
{
    std::shared_ptr<LLNode> targetnode;
    CaseFindNodeResult res;
    findNodeResult(); //constructor
}

findNodeResult::findNodeResult(snode target_node)
{
    targetnode = target_node;
    res = none;
}