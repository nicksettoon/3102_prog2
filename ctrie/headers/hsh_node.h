#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <memory>

struct Node
{
    // static int node_counter;
    // int node_id; just going to use node's memory address as a unique id
    char head;
    std::string label;
    bool eow;

    Node(std::string word_in, bool e_o_w);
    // void edit(std::string);
    void print(); 
};