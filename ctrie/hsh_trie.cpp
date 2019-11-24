// #include <string> //included in node.h 
// #include <iostream> //included in node.h 
// #include <stdio.h> //included in node.h 
// #include <memory> //included in node.h 
#include "headers/hsh_trie.h"
#include "headers/ll_node.h"

using str = std::string;
using Edge = HshEdge;
using Hash = HashTrie::Hashes;

                  //CONSTRUCTORS//
//-----------------------HshEdge----------------------------//
//struct holding the details of the relationship between two HshNodes in a HashTrie
//     LLNode* parent;   //pointer to parent of relationship
//     LLNode* child;    //pointer to child of relationship
//     char childhead;         //head of child node
//     HshEdge* nextedge; //pointer to next entry in the HshEdge's linked list.

HshEdge::HshEdge(LLNode* parent_in, LLNode* child_in) //base constructor
    : parent(parent_in), child(child_in), childhead(child_in->letter), nextedge(nullptr) {/*base constructor*/}

//-----------------------HashTrie----------------------------//
//     HashTrie(int size_in); //basic constructor
//     const int size;   //size of the hash table
//     std::vector<HshEdge> hshtable; //array of HashEntries
//     LLNode* root;
//     typedef int(*hashFunc)(int parent_addr, char child_head);

HashTrie::HashTrie(int size_in)
    : size(size_in) {/*full constructor*/ hshtable[size];}

                //MEMBER FUNCTIONS//
//-----------------------HshEdge----------------------------//
void HshEdge::print()
{//prints the edge instance
    std::cout << "Edge: " << this << "\t";
    std::cout << "parent: " << this->parent->letter << this->parent->label << "\t";
    std::cout << "child: " << this->child->letter << this->child->label <<"\t";
    std::cout << "childhead: " << this->childhead << "\t";
    std::cout << "nextedge: " << this->nextedge << std::endl;
}

Edge* HshEdge::searchList(LLNode* target_parent, char target_childhead)
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
 
//-----------------------HashTrie----------------------------//
bool Hashtrie::search(str target_word)
{
    LLNode *rootchild = root->firstChild;
    if(rootchild == nullptr) //empty trie
    {
        return;
    }
    else //not empty trie, start searcg
    {
        int i = 0;
            while(rootchild != nullptr && rootchild->letter < target_word[i])
            {
                rootchild = rootchild->rightSibling; //continue through level
            }
            if(rootchild == nullptr) //reached end, not found
            {
                std::cout << target_word << " is not found " << std::endl;
                return;
            }
            else //continue search
            {
                i++;
                bool found = false;
                while(!found && i < rootchild->label.length())
                {
                    if(target_word[i] == rootchild->label[i]) //still matching, continue
                    {
                        i++;
                    }
                    else
                    {
                         rootchild = rootchild->firstChild; //next level
                         found = true;
                    }
                }
            }
        std::cout << target_word << " found." << std::endl;
    }
}

bool HashTrie::insert(LLNode* parent_in, LLNode* child_in)
{//insert function, uses this->hash()
    //make edge
    Edge* newedge = new Edge(parent_in, child_in);
    int parentaddr = reinterpret_cast<std::uintptr_t>(parent_in); 
    int hashresult = (this->*hash)(parentaddr, child_in->letter);

    if (this->hshtable[hashresult] != NULL)
    {
        Edge* collidingedge = this->hshtable[hashresult];
        newedge->nextedge = collidingedge;
        this->hshtable[hashresult] = newedge;
    }
    else
    {
        this->hshtable[hashresult] = newedge;
    }
    return 1;
}

void HashTrie::setHash(Hash desired_hash)
{//sets the HashTrie's hash function to one of the defined options in the Hashes enum
    std::cout << "Setting hash function to: " << desired_hash << std::endl;

    this->hash = &HashTrie::primeHash;
    // switch (desired_hash)
    // {
    // case prime:
    //     this->hash = primeHash;
    //     break;
    
    // default:
    //     this->hash = primeHash;
    //     break;
    // }
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

