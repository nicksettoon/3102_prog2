#include<fstream>
#include <chrono>
// #include<iostream>  //included in node.h
// #include<string>    //included in node.h
#include "headers/ll_trie.h"
#include "headers/hsh_trie.h"

using str = std::string;

void printFunc(str string_in)
{//prints one line with a single given string
    std::cout << string_in << std::endl;
}
int main()
{

    LinkedList* trie;
    trie = new LinkedList;
    std::ifstream input;
    str word;
    input.open("words.txt");
    while (input >> word)
    {
        trie->insert(word);
    }
    input.close();
    
    // LinkedList::printFunc printit = printFunc;
    // HashTrie::insertFunc insertHash = HashTrie::insert;
    // trie->getNodes(insertHash, trie->root, "");

    // input.open("words.txt");
    // auto start = std::chrono::high_resolution_clock::now();
    // while(input >> word)
    // {
    //     trie->search(word);
    // }
    // input.close();
    // auto elapsed = std::chrono::high_resolution_clock::now() - start;
    // long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // std::cout << "Linked list performance for search: " << microseconds << " micro-sec" << std::endl;
    return 0;
}
