#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <unistd.h>
#include "trie.h"


namespace tools
{//namespace for later use
    using str = std::string;    //namespace definition for easier use
    using node = tnode::Node;   //namespace definition for easier use

    str getPath();  //func definition so the prints can be adjacent to each other
    void print(str s)
    {//prints single string to output
        std::cout << s << std::endl;
    }

    void pwd()
    {//prints working directory of program
       str PATH = getPath(); 
       print(PATH);
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

    str getPath()
    {
        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        return std::string( result, (count > 0) ? count : 0 );
    }
}