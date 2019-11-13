/*this is a header file to setup all the required #includes and namespace abstractions.
  It basically has all the necessary stuff that each header and cpp file will need.*/
#pragma once
#include <iostream> //needed for print() 
#include <string>   //pretty much everything needs this
#include <fstream>  //need for printFile() and main.cpp
#include <limits.h> //needed for getPath()
#include <unistd.h> //needed for getPath()
/*FILL_LATER*/

namespace tools
{//namespace for use elsewhere
    using str = std::string;    //type abstraction for easier use in all the files

    str getPath();  //func definition so the prints can be adjacent to each other
    
    void print(str s)
    {//prints single string to output
        std::cout << s << std::endl;
    }

    void printc(char c)
    {//prints single char to output
        std::cout << c << std::endl;
    }

    void pwd()
    {//prints working directory of program
       str PATH = getPath(); 
       print(PATH);
    }

    void printFile(str file_name)
    {//prints a given file's contents
        std::ifstream infile;   //create file stream to read from
        char rawtext;    //str to hold input from file stream
        infile.open(file_name);    //open list of words

        while(infile.is_open() && !infile.eof())
        {//while the file is open and the end hasn't been reached.
            infile >> rawtext;  //get next str in file
            // print(rawtext);     //print it
        }

        infile.close(); //close infile
    }

    str getPath()
    {//no idea how this works, only that it does.

        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        return std::string( result, (count > 0) ? count : 0 );
    }
}