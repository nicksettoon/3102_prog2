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
using s_Result = std::shared_ptr<HSHtrie::searchResult>;

int main()
{
    //SET UP DATA STREAM//
    std::shared_ptr<std::ifstream> inputstream = std::make_shared<std::ifstream>("word_list.txt");
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
    //GENERATE HASH TABLE SIZE//
    int hashtablesize = tools::getNextPrime(listsize);
    //DECIDE ON HASH FUNCTION//
    Hash hashtype = Hash::prime;
    //MAKE THE HSHtrie//
    HSHtrie* hshtrie = new HSHtrie(hashtablesize, hashtype);
    //GET ALL NODES FROM LLtrie// 
    std::cout << "Copying LLtrie to HSHtrie." << std::endl;
    lltrie->preorderTraversal(hshtrie, nullptr, lltrie->root, lltrie->root->label);
    //RUN TEST FOR EACH TRIE//
    hshtrie->testTrieSearch(inputstream);
    lltrie->testTrieSearch(inputstream);
    //CLEAN UP//
    delete lltrie;
    delete hshtrie;
    inputstream->close();
    return 0;
}
