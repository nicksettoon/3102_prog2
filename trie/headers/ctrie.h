#pragma once
#include "tnode.h"
/*FILL_LATER*/

using trie = ctrie::CompTrie;   //namespace abstraction for easier use
auto& prt = tools::print;   //"alias" for print function for easier use

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
        CompTrie(char term, node *root); //initializes Trie with given root node
        CompTrie(char term, str raw_text[]); //initializes Trie with array of words

        //functions
        insertLL(str word); //insert word via linked list implementation
        inserthash(str word);   //insert word via hash implementation

        //destructors
        ~CompTrie();//default
    };
}