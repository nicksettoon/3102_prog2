#include "headers/ll_node.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

using str = std::string;

LLnode::LLnode(char letter_in, str label_in, bool wordEnd_in, LLnode* child_in, LLnode* r_sib_in) //constructor
    : head(letter_in), label(label_in), wordEnd(wordEnd_in), firstChild(child_in), rightSibling(r_sib_in) {}

void LLnode::print()
{//prints a single node
    str eow = this->wordEnd == 1 ? "yes" : "no";
    std::cout << "head: " << this->head << "\tlabel: " << this->label << "\tEoW? " << eow << std::endl;
}