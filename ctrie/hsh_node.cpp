#include "headers/hsh_node.h"
// #include <string> //included in node.h
// #include <iostream> //included in node.h
// #include <stdio.h> //included in node.h
// #include <memory> //included in node.h

using str = std::string;

HshNode::HshNode(str word_in, bool e_o_w)
{//constructor
    head = word_in[0];
    label = word_in.substr(1);
    eow = e_o_w;
}