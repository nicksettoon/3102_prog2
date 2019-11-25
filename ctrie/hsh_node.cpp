#include "headers/hsh_node.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

using str = std::string;

HSHnode::HSHnode(char head_in, std::string label_in, bool wordEnd_in)
    : head(head_in), label(label_in), wordEnd(wordEnd_in) {/*full constructor*/}

void HSHnode::print()
{//prints a single node
    str eow = this->wordEnd == 1 ? "yes" : "no";
    std::cout << "head: " << this->head << "\tlabel: " << this->label << "\tEoW? " << eow << std::endl;
}