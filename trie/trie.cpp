#include "../headers/tools.h"
#include "../headers/trie.h"


trie::CompTrie()
    : term("$") 
{//default constructor
    cout << < endl;
    prt("Entering default CompTrie constructor.");
    node *newroot = new node;
    this->root = newroot;
}

trie::~CompTrie()
{//delete all nodes from the memory heap and clean up other stuff if necessary
    prt("Entering CompTrie destructor.");
}