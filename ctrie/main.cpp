#include <fstream>
#include "headers/ll_trie.h"
#include "headers/hsh_trie.h"
// #include <vector>    //included in hsh_trie.h
// #include <math.h>    //included in hsh_trie.h
// #include <fstream>   //included in hsh_trie.h 
// #include <chrono>    //included in hsh_trie.h
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h
#include "headers/tools.h"

using str = std::string;
using Hash = HSHtrie::Hashes;

int notmain()
{
    //SET UP DATA STREAM//
    std::ifstream inputstream("word_list.txt");
    str targetword;
    int listsize;
    //CREATE LLtrie//
    LLtrie* lltrie = new LLtrie;
    //FILL IT//
    while (inputstream >> targetword)
    {
        lltrie->insert(targetword);
        listsize++;
    }
    inputstream.close();
    //GENERATE HASH TABLE SIZE//
    int hashtablesize = tools::getNextPrime(listsize);
    //DECIDE ON HASH FUNCTION//
    Hash hashtype = Hash::prime;
    //MAKE THE HSHtrie//
    HSHtrie* hshtrie = new HSHtrie(hashtablesize, hashtype);
    //GET ALL NODES FROM LLtrie// 
    // lltrie->preorderTraversal(hshtrie, nullptr, lltrie->root, lltrie->root->label);
    // std::cout << "finished" << std::endl;
    // std::cout << "Copying LLtrie to HSHtrie." << std::endl;
    //RUN TEST FOR EACH TRIE//
    // lltrie->testTrieSearch();
    // lltrie->search("aben");
    // hshtrie->testTrieSearch();
    //CLEAN UP//
    delete lltrie;
    delete hshtrie;
    return 0;
}
