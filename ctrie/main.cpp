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
    std::ifstream inputstream("word_list.txt");
    str targetword;
    int listsize = 1009;
    //CREATE LLtrie//
    // LLtrie* lltrie = new LLtrie;
    // //FILL IT//
    // while (inputstream >> targetword)
    // {
    //     lltrie->insert(targetword);
    //     listsize++;
    // }
    //GENERATE HASH TABLE SIZE//
    // int hashtablesize = tools::getNextPrime(listsize);
    int hashtablesize = listsize;
    //DECIDE ON HASH FUNCTION//
    Hash hashtype = Hash::prime;
    //MAKE THE HSHtrie//
    HSHtrie* hshtrie = new HSHtrie(hashtablesize, hashtype, 1);
    while (inputstream >> targetword)
    {
        hshtrie->insertString(targetword);
    }
    inputstream.close();
    //GET ALL NODES FROM LLtrie// 
    // lltrie->preorderTraversal(hshtrie, nullptr, lltrie->root, lltrie->root->label);
    // std::cout << "finished" << std::endl;
    // std::cout << "Copying LLtrie to HSHtrie." << std::endl;
    //RUN TEST FOR EACH TRIE//
    // lltrie->testSearch();
    hshtrie->testSearch();
    //CLEAN UP//
    // delete lltrie;
    delete hshtrie;
    return 0;
}
