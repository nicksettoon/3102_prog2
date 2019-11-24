#include "headers/hsh_trie.h"
// #include <string> //included in node.h // #include <iostream> //included in node.h // #include <stdio.h> //included in node.h // #include <memory> //included in node.h using str = std::string; HshEdge::HshEdge(HshNode* parent_in) : parent(parent_in) {} HshEdge::HshEdge(HshNode* parent_in, char head_in, HshNode* child_in) : parent(parent_in), c(head_in), child(child_in) {} bool HshEdge::searchList()    {//searches the linked list of HshEdge nodes } 

using str = std::string;
using Edge = HshEdge;

                            //CONSTRUCTORS//
//-----------------------HshEdge----------------------------//
//struct holding the details of the relationship between two HshNodes in a HashTrie
//     HshNode* parent;   //pointer to parent of relationship
//     HshNode* child;    //pointer to child of relationship
//     char childhead;         //head of child node
//     HshEdge* nextedge; //pointer to next entry in the HshEdge's linked list.

HshEdge::HshEdge(HshNode* parent_in, HshNode* child_in) //base constructor
    : parent(parent_in), child(child_in), childhead(child_in->head), nextedge(nullptr) {/*base constructor*/}

//-----------------------HashTrie----------------------------//
//     HashTrie(int size_in); //basic constructor
//     const int size;   //size of the hash table
//     std::vector<HshEdge> hshtable; //array of HashEntries
//     HshNode* root;
//     typedef int(*hashFunc)(int parent_addr, char child_head);

HashTrie::HashTrie(int size_in)
    : size(size_in) {/*full constructor*/ hshtable[size];}


                        //MEMBER FUNCTIONS//
//-----------------------HshEdge----------------------------//
void HshEdge::print()
{//prints the edge instance
    std::cout << "Edge: " << this << "\t";
    std::cout << "parent: " << this->parent->head << this->parent->label << "\t";
    std::cout << "child: " << this->child->head << this->child->label <<"\t";
    std::cout << "childhead: " << this->childhead << "\t";
    std::cout << "nextedge: " << this->nextedge << std::endl;
}

Edge* HshEdge::searchList(HshNode* target_parent, char target_childhead)
{//searches the linked list of HshEdge nodes for node with correct parent and childhead
    /*FILL*/
    std::cout << "Finding parent: " << target_parent << " childhead: " << target_childhead << std::endl;
    std::cout << "Starting from: ";
    this->print();
        
    Edge* currentedge = this;
    while(currentedge != nullptr)
    {//while we havent reached the end of the linked list of edges
        if (currentedge->parent != target_parent) //check parent pointers
            currentedge = currentedge->nextedge;    //advance to nextedge
        else
        {
            if(currentedge->childhead != target_childhead) //check childhead
                currentedge = currentedge->nextedge;    //advance to nextedge 
            else
            {
               return currentedge;
            }
        }
    }
    std::cout << "Did not find edge which matched the parent and childhead given." << std::endl;
    return currentedge;
}
 
//-----------------------HshEdge----------------------------//
bool HashTrie::insert(HashTrie::hashFunc hash_func, str word_in)
{//insert function, uses hash()
    //make node
    HshNode* newnode = new HshNode(word_in, 1);
    //find where to insert
    //insert
    //increment node counter
    return 0;
}

// bool HashTrie::search(str word_in)
// {//search function, uses hash() and HshEdge::searchList()
    
//     std::cout << "Inserting " << word_in << " into trie" << std::endl;

//     if(this->root->firstChild == nullptr) //trie empty, insert first word
//     {
//         std::cout << "Trie empty" << std::endl;
//         LLNode * node = new LLNode(word[0], word, false, nullptr, nullptr);
//         root->firstChild = node;
//         return;
//     }
// }

