#include "hshtrie.h"
// #include <string> //included in node.h
// #include <iostream> //included in node.h
// #include <stdio.h> //included in node.h
// #include <memory> //included in node.h

using str = std::string;

HashEntry::HashEntry(Node* parent_in)
    : parent(parent_in) {}

HashEntry::HashEntry(Node* parent_in, char head_in, Node* child_in)
    : parent(parent_in), c(head_in), child(child_in) {}

bool HashEntry::searchList()    
{//searches the list of HashEntry nodes

}






HashTrie::HashTrie(int size_in)
    : size(size_in)
    {
        hshtable[size];
    }

HashEntry::HashEntry* HashTrie::hash(int parent_id, char child_head) 
{//hash function to find child with given child_head

}
    
bool HashTrie::insert(str word_in)
{//insert function, uses hash()
    //make node
    //Node* newnode = new Node(word_in, 1)
    //
}

bool HashTrie::search()
{//search function, uses hash() and HashEntry::searchList()

}