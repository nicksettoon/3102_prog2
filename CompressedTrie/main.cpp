// #include<iostream>  //included in node.h
// #include<string>    //included in node.h
#include<fstream>
#include <chrono>
#include "linkedlist.h"

using str = std::string;

int main()
{
    LinkedList * trie;
    trie = new LinkedList;
    std::ifstream input;
    str word;
    input.open("words.txt");
    while (input >> word)
    {
        trie->insert(word);
    }
    input.close();
    input.open("words.txt");
    auto start = std::chrono::high_resolution_clock::now();
    while(input >> word)
    {
        trie->search(word);
    }
    input.close();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "Linked list performance for search: " << microseconds << " micro-sec" << std::endl;
    return 0;
}
