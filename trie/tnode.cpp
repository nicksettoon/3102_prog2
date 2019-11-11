#include "tnode.h"
/*FILL*/

tnode::Node()   //default constuctor
    : head(NULL), label(NULL), eow(0), right_sib(nullptr), fst_child(nullptr){}


tnode::Node()
{//custom constructor
    /*FILL*/
}

tnode::Node* findSibling(char target_head)
{//returns ptr to the sibling of this node instance whose head equals the target_head
    /*FILL*/
}

tnode::~Node()
{//destroys the node
    /*FILL*/
}

tnode::~Node()
{//destroys the node and all it's siblings.
    /*FILL*/
}