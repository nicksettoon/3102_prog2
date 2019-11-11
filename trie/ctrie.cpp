#include "headers/tools.h"
#include "headers/ctrie.h"
/*FILL_LATER*/

using trie = ctrie::CompTrie;   //namespace abstraction for easier use
auto& prt = tools::print;   //"alias" for print function for easier use

trie::CompTrie()
    : term('$') 
{//default constructor
    prt("Entering default CompTrie constructor."); //notification
    node *newroot = new node;
    this->root = newroot;
}

trie::~CompTrie()
{//delete all nodes from the memory heap and clean up other stuff if necessary
    prt("Entering CompTrie destructor."); //notification
}