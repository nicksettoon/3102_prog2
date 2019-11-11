#pragma once
#include "tnode.h"
/*FILL_LATER*/

namespace ctrie
{//namespace definition for use elsewhere

    class CompTrie
    {/*trie whose nodes with only one child have been compressed into one node @ parent node.
    All internal nodes of this trie must have at least two children.*/
        using node = tnode::Node;

        char term;   //termination character for strings
        node *root;  //pointer to the root node of the trie instance

        //constructors
        CompTrie(); //default
        CompTrie(char term, node *root); //custom

        //destructors
        ~CompTrie();//default
    };
}