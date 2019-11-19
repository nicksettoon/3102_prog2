#include "hshnode.h"
// #include <string> //included in node.h
// #include <iostream> //included in node.h
// #include <stdio.h> //included in node.h
// #include <memory> //included in node.h

using str = std::string;

Node::Node(str word_in, bool e_o_w)
{//constructor
    Node::node_counter++;
    node_id = Node::node_counter;
    head = word_in[0];
    label = word_in.substr(1);
    eow = e_o_w;
}