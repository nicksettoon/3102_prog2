#include "headers/lltrie.h"
using lltrie = LLCompTrie;

searchStack::searchStack(str target_word, node* child_1)
{//constructor for searchStack struct
    wordhead = target_word[0];     //set wordhead
    targetnode = child_1->findHead(wordhead); //set new target_node with result of findHead() on the 1st child
    targetlabel = target_word.substr(1);   //set target_label to everything after the wordhead
    result = nullptr;      //set result to nullptr cause no comparison has happened yet
}

lltrie::LLCompTrie()
{//default constructor
    prt("Entering default CompTrie constructor."); //notification
    this->root = std::make_shared<node>();   //create smart shared pointer for root node
}


node* lltrie::insert(str target_word) override
{//frontend for inserting word via linked list implementation
    prt("Entering LLinsert().")

    if(this->root->child1 == nullptr)
    {//if there is no first child of this trie
        prt("Root node has no children yet.")
        add(str::make_shared<node>(target_word, 1), this->root, 1); //add new node w/ target_word as child of root node
        // this->root->child1 = new node(target_word, 1); //make one with the given word
        return this->root->child1;
    }
    else
    {
        //prep searchStack for searchTrie()
        std::shared_ptr<stack> newstack = std::make_shared<stack>(target_word, this->root->child1);
        //send it off
        resultstack = searchTrie(newstack);
    }
}

void lltrie::add(node* in_node, node* neighbor, bool child) override
{//actually responsible for adding a node at a given neighbor node

    if(child)
        neighbor->child1 = in_node;     //add given node as child
    else
        neightbor->rightsib = in_node;  //add given node to right sibling
}

void lltrie::edit(node* target_node, str new_label, bool e_o_w) override
{//edits target node and returns pointer to that node
    target_node->label = new_label;
    if(e_o_w)
        target_node->eow = 1;
}