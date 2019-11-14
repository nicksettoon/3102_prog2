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
        node* root;  //pointer to the root node of the trie instance

    public:
        //constructors
        CompTrie(); //default
        CompTrie(char term, node *root); //initializes Trie with given root node
        CompTrie(char term, str raw_text[]); //initializes Trie with array of words

        //functions
        // node* getWord(node target_node);    //search function
        void searchTrie(str target_word);
        node* insertFront(str target_word); //frontend for inserting word via linked list implementation
        node* insertFrontHash(str target_word);   //frontend for inserting word via hash implementation

    private:
        enum compCase
        struct compResult
        {//struct for returning things from trie::compareLabel()
            int index;  //index at which the strings need to be split
            case compCase; //resulting case of the if statements
        }
        struct searchStack
        {//struct for passing the state of a search between functions
            char wordhead;
            node* targetnode;
            str targetlabel;
            compResult result;
        }

        compResult compareLabel(node* target_node, str target_label);
            //compares target_label to label @ target_node
        searchStack searchTrie(searchStack stack_in); //recursive search function
        void insertLL(searchStack stack_in);    //does the actual insertion

        //destructors
        // ~CompTrie();//default
    };

    // class CompTrieHash : public CompTrie
    //{//Child class of CompTrie which implements traversal and insertion of nodes via hash tables.}

    // class CompTrieLL : public CompTrie
    //{//Child class of CompTrie which implements traversal and insertion of nodes via linked lists.}
}

