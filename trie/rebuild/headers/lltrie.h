#include "ctrie.h"
#include "llnode.h"
#include <memory>

using node = LLNode;

struct searchStack
{//struct for passing the state of a search between functions
    //fields
    char wordhead;      //current wordhead of word being searched.
    node* targetnode;   //current targetnode for compareLabel()
    str targetlabel;    //current targetlabel for compareLabel()
    compResult* result; //last result of compareLabel()
    //constructors
    searchStack(str target_word, node* child_1);  //constructor
};


class LLCompTrie : public CompTrie
{//Child class of CompTrie which implements traversal and insertion of nodes via linked lists.
    public:
        //fields
        std::shared_ptr<node> root;  //pointer to the root node of the trie instance

        //constructors
        LLCompTrie();

        //functions
        node* insert(str target_word);  //front end for insertion
        node* search(str target_word);  //front end for search
    private:
        //functions
        searchStack* searchTrie(searchStack& stack_in); //recursive search function
        void edit(node* target_node, str new_label, bool e_o_w) override; //edits a node
        void add(node* in_node, node* neighbor, bool child) override;  //actually creates and adds a node
}