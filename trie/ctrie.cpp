#include "headers/tools.h"
#include "headers/ctrie.h"
/*FILL_LATER*/


trie::CompTrie()
    : term('$') 
{//default constructor
    prt("Entering default CompTrie constructor."); //notification
    node *newroot = new node;
    this->root = newroot;
}

trie::insertLL(str word)
{//insert word via linked list implementation
    prt("Entering insertLL")
    char word_head = (char)word[0];
    node* targetnode = this->root->child1.findHead(word_head);    


}
trie::~CompTrie()
{//delete all nodes from the memory heap and clean up other stuff if necessary
    prt("Entering CompTrie destructor."); //notification
}