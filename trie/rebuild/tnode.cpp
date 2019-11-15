// #include "headers/tools.h"
#include "tnode.h"
/*FILL_LATER*/
//function parameters are underscored. function variables are just appended.

// auto& prt = tools::print;   //"alias" for print function for easier use 
using node = tnode::Node;

tnode::Node::Node()   //default constuctor
    : head('\0'), label(""), eow(0), rightsib(nullptr), child1(nullptr){}

tnode::Node::Node(str word_in, bool e_o_w)
{//lighter custom constructor for building 1st child node
    // prt("Entering word_in constructor.")
    head = word_in[0]; //set node's head to first letter of the word_in.
    label = word_in.substr(1); //set node's label to remaining word_in
    eow = e_o_w;
}

tnode::Node::Node(str word_in, bool e_o_w, node* right_sib, node* child_1)
{//full custom constructor
    /*FILL*/
    // prt("Entering full node constructor.")
    head = word_in[0]; //set node's head to first letter of the word_in.
    label = word_in.substr(1); //set node's label to remaining word_in
    eow = e_o_w;
    rightsib = right_sib;
    child1 = child_1;
}

node* node::findHead(char target_head)
{//returns ptr to the sibling of this node instance or the instance itself if its head equals the target_head
    /*FILL*/
    // prt("Entering findHead.")
    node* targetnode = this;
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
    // prt("Could not find node with that head in the sibling list.");
    // prt("Sending back nullptr."); //would like to send back last valid node at some point.
    return nullptr;
}

void node::print()
{//prints a single node
    std::cout << "head: " << this->head << "\tlabel: " << this->label << "\tword? " << this->eow << std::endl;
}

void node::printSibs()
{//prints the sibling nodes from the target_node down the line
    node* target_node = this;
    while(target_node != nullptr)
    {//while the end of the sibling chain hasn't bee reached.
        target_node->print();
        target_node = target_node->rightsib;
    }
}
node::~Node()
{//destroys the node
    /*FILL*/
    // prt("Destroying node.");
}

// node::~Node()
// {//destroys the node and all it's siblings.
    /*FILL*/
// }