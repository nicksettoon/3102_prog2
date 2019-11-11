#include "headers/tools.h"
// #include <iostream>
// #include <string>
// #include <fstream>
// #include <limits.h>
// #include <unistd.h>


// str getPath();  //func definition so the prints can be adjacent to each other
// void print(str s)
// {//prints single string to output
//     std::cout << s;
// }

// void pwd()
// {//prints working directory of program
//     str PATH = getPath(); 
//     print("pwd: ");
//     print(PATH);
// }

// str getPath()
// {
//     char result[ PATH_MAX ];
//     ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
//     return str( result, (count > 0) ? count : 0 );
// }

// namespace prt = tools::print;   //namespace definition for easier use
/*FILL*/

// namespace node = tnode::Node;    //from trie.cpp
// namespace prt = tools::print;    //from trie.cpp
// namespace str = std::string;     //from tnode.h

int main()
{//main function
    tools::pwd();
    // tools::printFile("WORD.LST");
    return 0;
}

