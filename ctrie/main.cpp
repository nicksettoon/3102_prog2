#include <fstream>
#include "headers/ll_trie.h"
#include "headers/hsh_trie.h"
// #include <vector>    //included in hsh_trie.h
// #include <math.h>    //included in hsh_trie.h
// #include <fstream>   //included in hsh_trie.h 
// #include <chrono>    //included in hsh_trie.h
// #include <string>    //included in t_nodes.h
// #include <iostream>  //included in t_nodes.h
// #include <stdio.h>   //included in t_nodes.h
// #include <memory>    //included in t_nodes.h
#include "headers/tools.h"

using str = std::string;
using Hash = HSHtrie::Hashes;

int main()
{
    //SET UP DATA STREAM//
    str filename;
    std::cout << "Please enter the filename you wish to use. It must be correct with the file extension. I'm not doing error correction here." << std::endl;
    std::getline(std::cin, filename);
    std::ifstream inputstream(filename);
    str targetword;
    int listsize = 1009;
    //CREATE LLtrie//
    LLtrie* lltrie = new LLtrie;
    //FILL IT//
    while (inputstream >> targetword)
    {
        lltrie->insert(targetword);
        listsize++;
    }
    //GENERATE HASH TABLE SIZE//
    int hashtablesize = tools::getNextPrime(listsize);
    //DECIDE ON HASH FUNCTION//
    Hash hashtype = Hash::prime;
    //MAKE THE HSHtrie//
    HSHtrie* hshtrie = new HSHtrie(hashtablesize, hashtype, 1);
    {
        hshtrie->insertString(targetword);
    }
    inputstream.close();
    //RUN TEST FOR EACH TRIE//
    lltrie->testSearch(filename);
    hshtrie->testSearch(filename);
    //CLEAN UP//
    delete lltrie;
    delete hshtrie;
    return 0;
}
