#pragma once
#include <memory>
#include <string>
/*FILL_LATER*/

using str = std::string;

enum CompCase
{//restrict possible cases of compResult
    CaseSubstr,     //the target_label is a substring of the node_label
    CaseDiv,        //the target_word diverges from the label @ i
    CaseSuperstr,   //the target_word is a superstring of the label (label diverges from target_word @ i)
    CaseInTrie      //the exact target_word is in the trie
};

struct compResult
{//struct for returning things from trie::compareLabel()
    int index;  //index at which the strings need to be split
    CompCase resultcase; //resulting case of the if statements
    compResult(int index_in, CompCase case_in);
};

class Insertable
{//insert interface for CompTrie classes
    //functions
    virtual void* insert() = 0; //virtual function forcing subclasses to implement
    virtual void add() = 0; //virtual function forcing subclasses to implement
    virtual void edit() = 0; //virtual function forcing subclasses to implement
    virtual compResult compareLabel() = 0; //virtual function forcing subclasses to implement
};

class CompTrie : public Insertable
{/*trie whose nodes with only one child have been compressed into one node @ parent node.
    All internal nodes of this trie must have at least two children.
    This is a base class for HSCompTrie and LLCompTrie.*/
    public:
        //constructors
        // CompTrie(); //default
        // CompTrie(char term, node* root); //initializes Trie with given root node
        // CompTrie(char term, str raw_text[]); //initializes Trie with array of words
    private:
        //functions
        compResult compareLabel();
            //compares target_label to label @ target_node
        //destructors
        // ~CompTrie();//default
}