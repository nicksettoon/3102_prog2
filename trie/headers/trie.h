#pragma once
#include "tnode.h"

namespace trie
{//namespace for use elsewhere
    class CompTrie
    {/*trie whose nodes with only one child have been compressed into one node @ parent node.
    All internal nodes of this trie must have at least two children.*/

        char term;          //termination character for strings
        tnode::Node *root;  //pointer to the root node of the trie instance

        //constructors
        CompTrie(); //default
        CompTrie(char term, tnode::Node *root); //custom

        //destructors
        ~CompTrie();//default
    }

    #include "../trie.cpp"
}