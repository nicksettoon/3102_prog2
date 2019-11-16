#include "headers/lltrie.h"

using lltrie = LLCompTrie;
using str = std::string;
using node = std::shared_ptr<LLNode>; //"alias" for LLNode to make it easier to type
using comp = std::shared_ptr<compResult>; //"alias" for compResult to make it easier to type
using stack = std::shared_ptr<searchStack>; //"alias" for compResult to make it easier to type


searchStack::searchStack(str target_word, node child_1)
{//constructor for searchStack struct
    head = target_word[0];     //set head to be the first char of the target_word
    targetnode = child_1->findHead(head); //set new target_node with result of findHead() on the 1st child
    targetlabel = target_word.substr(1);   //set target_label to everything after the wordhead
    result = std::make_shared<compResult>(-1, NoCase);      //set result to nullptr cause no comparison has happened yet
};

lltrie::LLCompTrie()
{//default constructor
    // prt("Entering default CompTrie constructor."); //notification
    this->root = std::make_shared<LLNode>();   //create smart shared pointer for root node
};


node lltrie::insert(str target_word)
{//frontend for inserting word via linked list implementation
    // prt("Entering LLinsert().")

    if(this->root->child1 == nullptr)
    {//if there is no first child of this trie
        // prt("Root node has no children yet.");
        node newchild = std::make_shared<LLNode>(target_word,1);
        add(newchild, this->root, 1); //add new node w/ target_word as child of root node
        // this->root->child1 = new node(target_word, 1); //make one with the given word
        return this->root->child1;
    }
    //prep searchStack for searchTrie()

    stack newstack = std::make_shared<searchStack>(target_word, this->root->child1);
    if (newstack->targetnode == nullptr)
    {//this means no node was found which contains the first char of the target_word 
        //make new node
        //insert it where it should be
    }
    
    //send it off
    newstack = searchTrie(newstack);
    return newstack->targetnode;
}

std::shared_ptr<searchStack> searchTrie(std::shared_ptr<searchStack> stack_in);
{//searches Trie recursively and returns searchStack struct with result of the search.

    stack_in->

}

void lltrie::add(node in_node, node neighbor, bool child) 
{//actually responsible for adding a node at a given neighbor node

    if(child)
        neighbor->child1 = in_node;     //add given node as child
    else
        neighbor->rightsib = in_node;  //add given node to right sibling
}
