#include "headers/tools.h"
#include "headers/tnode.h"
/*FILL_LATER*/

using node = tnode::Node;   //namespace abstraction for easier use

node::Node()   //default constuctor
    : head(NULL), label(NULL), eow(0), rightsib(nullptr), child1(nullptr){}

node::Node(str word)
{//lighter custom constructor for building 1st child node
    prt("Entering node head, label constructor.")
    this->head = word[0]; //set head to first letter of the given word.
    word.erase(0);  //erase the first letter from the word
    this->label = word; //set label = to the rest
    
}

node::Node(char head, str label, bool eow, node* right_sib, node* child_1)
{//custom constructor
    /*FILL*/
    prt("Entering full node constructor.")
    this->head = head;
    this->label = label;
    this->eow = eow;
    this->rightsib = right_sib;
    this->child1 = child_1;
}

node* node::findHead(char target_head)
{//returns ptr to the sibling of this node instance or the instance itself if its head equals the target_head
    /*FILL*/
    prt("Entering findHead.")
    node* targetnode = &this;
    while(targetnode != nullptr)
    {//while the end of the sibling chain hasn't bee reached.
        if(targetnode->head == target_head)
        {//if a child is found with the desired starting character
            return targetnode;  //return that node
        }
        else
        {//move the target node to the next sibling in the chain
            targetnode = targetnode->rightsib;
        }
    }
    prt("Could not find node with that head in the sibling list.");
    prt("Sending back nullptr."); //would like to send back last valid node at some point.
    return targetnode;
}

// node::~Node()
// {//destroys the node
    /*FILL*/
// }

// node::~Node()
// {//destroys the node and all it's siblings.
    /*FILL*/
// }