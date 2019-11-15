#pragma once
#include "tnode.h"
#include <memory>
/*FILL_LATER*/

using lltrie = ctrie::LLCompTrie;   //namespace abstraction for easier use
using hshtrie = ctrie::HSHCompTrie;   //namespace abstraction for easier use
using sptr = std::shared_ptr;    //type abstraction for easier use
auto& prt = tools::print;   //"alias" for print function for easier use

namespace ctrie
{//namespace definition for use elsewhere
    using node = tnode::Node;

    class Insertable
    {//insert interface for CompTrie classes
        private:
            //structs and enums
            enum compCase;
            struct compResult;
            struct searchStack;
            //functions
            virtual node* insert(str word_in) = 0; //virtual function forcing subclasses to implement
            virtual searchStack* searchTrie(searchStack& stack_in) = 0; //virtual function forcing subclasses to implement
            virtual void add(node* in_node, node* neighbor, bool child) = 0; //virtual function forcing subclasses to implement
    }

    class CompTrie : Insertable
    {/*trie whose nodes with only one child have been compressed into one node @ parent node.
     All internal nodes of this trie must have at least two children.
     This is a base class for HSCompTrie and LLCompTrie.*/
        // char term;   //termination character for strings
        public:
            //constructors
            CompTrie(); //default
            // CompTrie(char term, node* root); //initializes Trie with given root node
            // CompTrie(char term, str raw_text[]); //initializes Trie with array of words
        private:
            //functions
            compResult compareLabel(searchStack& stack_in);
                //compares target_label to label @ target_node
            //destructors
            // ~CompTrie();//default
    };

    class LLCompTrie : public CompTrie
    {//Child class of CompTrie which implements traversal and insertion of nodes via linked lists.
        public:
            //fields
            sptr<node> root;  //pointer to the root node of the trie instance

            //constructors
            LLCompTrie();

            //functions
            node* insert(str target_word);  //front end for insertion
            node* search(str target_word);  //front end for search
        private:
            //functions
            searchStack* searchTrie(searchStack& stack_in) override; //recursive search function
            void edit(node* target_node, str new_label, bool e_o_w) override; //edits a node
            void add(node* in_node, node* neighbor, bool child) override;  //actually creates and adds a node
    }
    
    // class HSHCompTrie : public CompTrie
    // {//Child class of CompTrie which implements traversal and insertion of nodes via hash tables.

    //     public:
    //         //fields
            
    //         //constructors
    //         HSHCompTrie();

    //         //functions
    //         node* insert(str target_word);  //front end for insertion
    //         node* search(str target_word);  //front end for search

    //     private:
    //         //functions
    //         searchStack searchTrie(searchStack stack_in); //recursive search function
    //         node* edit(str new_label, bool e_o_w); //edits a node
    //         node* iadd(searchStack stack_in);  //actually creates and adds the node

    // }
}