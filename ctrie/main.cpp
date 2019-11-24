#include<fstream>
#include <chrono>
// #include<iostream>  //included in node.h
// #include<string>    //included in node.h
#include "headers/ll_trie.h"
#include "headers/hsh_trie.h"

using str = std::string;

void testTrie(auto* trie_in)
{
    input.open("words.txt");
    auto start = std::chrono::high_resolution_clock::now();
    while(input >> word)
    {
        trie_in->search(word);
    }
    input.close();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "Linked list performance for search: " << microseconds << " micro-sec" << std::endl;
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
        count++;
    }
    std::cout << count << std::endl;
    input.close();
    
    HashTrie hshtrie = new HashTrie(count);

    trie->getNodes(hshtrie, trie->root, trie->root->label);

    testTrie(trie);
    testTrie(hshtrie);
    return 0;
}
