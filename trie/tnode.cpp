#include "headers/tools.h"
#include "headers/tnode.h"
/*FILL_LATER*/

using node = tnode::Node;   //namespace abstraction for easier use

node::Node()   //default constuctor
    : head(NULL), label(NULL), eow(0), rightsib(nullptr), child1(nullptr){}

// Node()
// {//custom constructor
    /*FILL*/
// }

node* findSibling(char target_head)
{//returns ptr to the sibling of this node instance whose head equals the target_head
    /*FILL*/
}

node::~Node()
{//destroys the node
    /*FILL*/
}

// node::~Node()
// {//destroys the node and all it's siblings.
    /*FILL*/
// }