#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "trie.h"


namespace tools
{//namespace for later use
    namespace str = std::string;    //namespace definition for easier use
    namespace node = tnode::Node;   //namespace definition for easier use

    void print(str s)
    {//prints single string to output
        std::cout << s << std::endl;
    }

    void printFile(str file_name);
    {//prints a given file's contents
        std::ifstream infile;   //create file stream to read from
        str rawtext;    //str to hold input from file stream
        infile.open(file_name);    //open list of words

        while(infile.is_open() && !infile.eof())
        {//while the file is open and the end hasn't been reached.
            infile >> rawtext;
            print(rawtext);
        }

        infile.close(); //close infile
    }
}