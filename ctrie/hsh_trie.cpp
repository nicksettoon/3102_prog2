#include "headers/hsh_trie.h"
// #include <string> //included in node.h // #include <iostream> //included in node.h // #include <stdio.h> //included in node.h // #include <memory> //included in node.h using str = std::string; HashEntry::HashEntry(Node* parent_in) : parent(parent_in) {} HashEntry::HashEntry(Node* parent_in, char head_in, Node* child_in) : parent(parent_in), c(head_in), child(child_in) {} bool HashEntry::searchList()    {//searches the linked list of HashEntry nodes } 


HashTrie::HashTrie(int size_in)
    : size(size_in)
    {
        hshtable[size];
    }

int HashTrie::hash(int parent_address, char child_head) 
{//hash function to find child with given child_head
    return (parent_address * child_head * pow(b,31)) % 10007;
}
    
bool HashTrie::insert(str word_in)
{//insert function, uses hash()
    //make node
    Node* newnode = new Node(word_in, 1)
    //find where to insert
    //insert
    //increment node counter
}

bool HashTrie::search(str word_in)
{//search function, uses hash() and HashEntry::searchList()
    
    std::cout << "Inserting " << word << " into trie" << std::endl;

    if(this->root->firstChild == nullptr) //trie empty, insert first word
    {
        std::cout << "Trie empty" << std::endl;
        LLNode * node = new LLNode(word[0], word, false, nullptr, nullptr);
        root->firstChild = node;
        return;
    }
}