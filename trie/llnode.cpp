// #include "headers/tools.h"
#include "headers/llnode.h"
/*FILL_LATER*/
//function parameters are underscored. function variables are just appended.

// auto& prt = tools::print;   //"alias" for print function for easier use 
// using node = LLNode; //"alias" for LLNode to make it easier to type
using snode = std::shared_ptr<LLNode>; //shared pointer to LLNode
using str = std::string;

LLNode::LLNode()   //default constuctor
    : head('\0'), label(""), eow(0), rightsib(nullptr), child1(nullptr){
    //printf("Creating node with default constructor.\n");
    }

LLNode::LLNode(char head_in)   //default constuctor
    : head(head_in), label(""), eow(0), rightsib(nullptr), child1(nullptr){
    //printf("Creating node with char constructor.\n");
    }

LLNode::LLNode(str word_in, bool e_o_w)
{//lighter custom constructor for building 1st child node
    // printf("Creating node with word_in constructor.\n");
    head = word_in[0]; //set node's head to first letter of the word_in.
    label = word_in.substr(1); //set node's label to remaining word_in
    eow = e_o_w;
}

// LLNode::LLNode(str word_in, bool e_o_w, snode left_sib, snode right_sib, snode child_1)
// {//full custom constructor
//     /*FILL*/
//     printf("Creating node with full constructor.\n");
//     head = word_in[0]; //set node's head to first letter of the word_in.
//     label = word_in.substr(1); //set node's label to remaining word_in
//     eow = e_o_w;
//     leftsib = left_sib;
//     rightsib = right_sib;
//     child1 = child_1;
// }

snode LLNode::findHead(char target_head)
{//returns ptr to the sibling of this node instance or the instance itself if its head equals the target_head
    /*FILL*/
    printf("Finding head from starting node: \t");
    this->print();
    if(this->head == target_head)
        return std::shared_ptr<LLNode>(this);

    snode targetnode = this->rightsib;  //FIX LATER//
    while(targetnode->head <= target_head)
    {//while the current node's head  
        if(targetnode->head == target_head) //if a child is found with the desired starting character
            return targetnode;  //return that node
        else //move the target node to the next sibling in the chain
            targetnode = targetnode->rightsib;
    }
    printf("Could not find node with that head in the sibling list.\n");
    return targetnode->leftsib; //send by node to the left of where the node should be.
}

void LLNode::print()
{//prints a single node
    str eow = this->eow == 1 ? "yes" : "no";
    std::cout << "head: " << this->head << "\tlabel: " << this->label << "\tEoW? " << eow << std::endl;
}

void LLNode::printSibs()
{//prints the sibling nodes from the target_node down the line
    printf("Printing sibling nodes of ");
    this->print();
    snode targetnode;
    targetnode = this->rightsib;
    // std::cout << targetnode.use_count() << std::endl;

    while(targetnode != nullptr)
    {//while the end of the sibling chain hasn't bee reached.
        targetnode->print();
        targetnode = targetnode->rightsib;
        // std::cout << targetnode.use_count() << std::endl;
    }
}

void LLNode::edit(str new_label, bool e_o_w)
{//edits node instance
    // this->head = new_word[0];
    this->label = new_label;
    if(e_o_w)
        this->eow = 1;
}

void LLNode::deleteNode(char c)
{//finds node with char c and deletes it
    std::shared_ptr<LLNode> target = this->findHead(c);
    target->leftsib->rightsib = target->rightsib;
    target->rightsib->leftsib = target->leftsib;
}

LLNode::~LLNode()
{//destroys the node
    /*FILL*/
    printf("\nDeleting node: \n");
    this->print();
    printf("\n");
    // this->leftsib->rightsib = this->rightsib;
    // this->rightsib->leftsib = this->leftsib;
}
