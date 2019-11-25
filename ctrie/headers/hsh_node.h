#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <memory>

struct HSHnode
{
    char head;
    std::string label;
    bool wordEnd;

    HSHnode(char head_in, std::string label_in, bool wordEnd_in); //full constructor
    virtual void print(); 
};