#include "headers/t_nodes.h"
// #include <string>    //included in t_nodes.h
// #include <iostream>  //included in t_nodes.h
// #include <stdio.h>   //included in t_nodes.h
// #include <memory>    //included in t_nodes.h

using str = std::string;

HSHnode::HSHnode(char head_in, std::string label_in, bool wordEnd_in)
    : head(head_in), label(label_in), wordEnd(wordEnd_in) {/*full constructor*/}

void HSHnode::print()
{//prints a single node
    str eow = this->wordEnd == 1 ? "yes" : "no";
    std::cout << "head: " << this->head << "\tlabel: " << this->label << "\tEoW? " << eow << std::endl;
}

LLnode::LLnode(char letter_in, str label_in, bool wordEnd_in, LLnode* child_in, LLnode* r_sib_in) //constructor
    : head(letter_in), label(label_in), wordEnd(wordEnd_in), firstChild(child_in), rightSibling(r_sib_in) {}

void LLnode::print()
{//prints a single node
    str eow = this->wordEnd == 1 ? "yes" : "no";
    std::cout << "head: " << this->head << "\tlabel: " << this->label << "\tEoW? " << eow << std::endl;
}