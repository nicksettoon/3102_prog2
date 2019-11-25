#include "headers/hsh_trie.h"
#include "headers/ll_node.h"
// #include <string>    //included in hsh_node.h
// #include <iostream>  //included in hsh_node.h
// #include <stdio.h>   //included in hsh_node.h
// #include <memory>    //included in hsh_node.h

using str = std::string;
using Edge = EDGnode;
using s_Edge = EDGnode;
using Hash = HSHtrie::Hashes;
using Result = HSHtrie::searchResult;
using s_Result = std::shared_ptr<HSHtrie::searchResult>;
using Fstream = std::shared_ptr<std::ifstream>;

                  //CONSTRUCTORS//
//-----------------------EDGnode----------------------------//
EDGnode::EDGnode(LLnode* parent_in, LLnode* child_in) //base constructor
    : parent(parent_in), child(child_in), childhead(child_in->head), nextedge(nullptr) {/*base constructor*/}
//-----------------------HSHtrie----------------------------//
HSHtrie::HSHtrie(int size_in, HSHtrie::Hashes hash_type)
    : size(size_in)
    {//full constructor//
        std::cout << "HSHtrie size: " << this->size << std::endl;
        edgetable.resize(this->size);
        this->setHash(hash_type);

    }
    
                //MEMBER FUNCTIONS//
//-----------------------EDGnode----------------------------//
void EDGnode::print()
{//prints the edge instance
    std::cout << "Edge: " << this << "\t";
    std::cout << "parent: " << this->parent->head << this->parent->label << "\t";
    std::cout << "child: " << this->child->head << this->child->label <<"\t";
    std::cout << "childhead: " << this->childhead << "\t";
    std::cout << "nextedge: " << this->nextedge << std::endl;
}

Edge* EDGnode::searchList(LLnode* target_parent, char target_childhead)
{//searches the linked list of EDGnode nodes for node with correct parent and childhead
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
//-----------------------HSHtrie----------------------------//
// std::cout << "Finding " << target_word << " in trie." << std::endl;
void HSHtrie::testTrieSearch(Fstream stream_in)
{
    s_Result resultinit = std::make_shared<Result>(0, HSHtrie::searchResult::NoCase);
    resultinit->currentnode = this->handle;
    str targetword;
    auto start = std::chrono::high_resolution_clock::now();
    while((*stream_in) >> targetword)
    {
        resultinit->currentlabel = targetword;
        this->search(resultinit);
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "Linked list performance for search: " << microseconds << " micro-sec" << std::endl;
}

s_Result HSHtrie::search(s_Result result_in)
{
    //check if trie is empty by checking for first child node of root
    s_Result resultout = result_in; 
    //GET NEXT EDGnode//
    Edge* targetedge = getEdge(result_in->currentnode, result_in->currentlabel[0]);

    if (targetedge == nullptr)
    {//if that edge doesn't exist, there is no child node with the rest of the label
        std::cout << resultout->currentlabel << " was not found." << std::endl;
        resultout->resultcase = Result::CaseNotInTrie;
        // resultout->locationfound = NULL;
        return resultout;
    }
    //COMPARE THE LABELS//
    resultout = compareLabel(resultout, targetedge->child);

    //EVALUATE RESULT//
    if (resultout->resultcase == Result::CaseSuperstr)
    {//if the target_string was a superstring of the child's label 
        resultout->currentnode = targetedge->child;  //move the node down a level
        resultout = search(resultout); //recurse
        return resultout;
    }
    else if(resultout->resultcase == Result::CaseInTrie)
    {//if the word was found in the trie.
        if(resultout->currentnode->wordEnd == 1)
        {
            std::cout << "Found node:" << std::endl;
            std::cout << resultout->currentnode->print() << std::endl;
            return resultout;
        }
    }
    else 
    {
        std::cout << target_string << " was not found." << std::endl;
        return resultout;
    }
}

bool HSHtrie::insertEdge(LLnode* parent_in, LLnode* child_in)
{//insert function, uses this->hash()
    //make edge
    Edge* newedge;
    int hashresult;

    if(parent_in != nullptr)
    {
        newedge = new Edge(parent_in, child_in);
        hashresult = getHash(parent_in, child_in->head);
    }
    else
    {
        this->handle = child_in;
        newedge = new Edge(child_in, child_in);
        hashresult = getHash(this->handle, child_in->head);
    }
    if (this->edgetable[hashresult] != NULL)
    {
        Edge* collidingedge = this->edgetable[hashresult];
        newedge->nextedge = collidingedge;
        this->edgetable[hashresult] = newedge;
    }
    else
    {
        this->edgetable[hashresult] = newedge;
    }
    return 1;
}

void HSHtrie::setHash(Hash desired_hash)
{//sets the HSHtrie's hash function to one of the defined options in the Hashes enum
    std::cout << "Setting hash function to: " << desired_hash << std::endl;

    switch (desired_hash)
    {
    case prime:
        this->hash = &HSHtrie::primeHash;
        break;
    
    default:
        this->hash = &HSHtrie::primeHash;
        break;
    }
}

int HSHtrie::getHash(LLnode* parent_in, char head_in)
{//small abstraction for hash function so I don't have to remember the special syntax everytime
    int parentaddr = reinterpret_cast<std::uintptr_t>(parent_in); 
    return (this->*hash)(parentaddr, head_in);
}

EDGnode* HSHtrie::getEdge(LLnode* parent_in, char head_in)
{
    int hash = getHash(parent_in, head_in);
    Edge* target_edge = this->edgetable[hash];
    target_edge = target_edge->searchList(this->handle, this->handle->head);

    return target_edge; 
}

int HSHtrie::primeHash(int parent_addr, char child_head)
{//hash with basic arthimetic and prime mod
    int b = 5;
    int result = ((parent_addr + (int)child_head * (int)std::pow(b,31)) % this->size);
    return result;
}
  
s_Result HSHtrie::compareLabel(s_Result result_in, LLnode* target_node)
{//Compares the target_label to the node_label at target_node.
 //returns case the comparison falls under, as well as the index at which to split if necessary
    std::cout << "Comparing: " << target_node->label << " against " << result_in->currentlabel << std::endl;

    str& c_l = result_in->currentlabel;            //reference ("target label") to make it easier to type
    str& n_l = target_node->label;      //reference ("node label") to make it easier to type


    for(char c:c_l) //What if comparing single letter which already exists at target_node? c=null?
    {//for each char in the target_label, compare it against the label @ the target_node

        if(result_in->index == n_l.length())
        {//case 1: If the index for node_label is equal to the  length of node_label and
         //the for loop is still going, the target_label is a superstring of the node_label
            // prt("hit case 1");
            // result_in->index = i;  //return index of where to begin 
            result_in->resultcase = Result::CaseSuperstr; //case to show the target_label is a superstring of the node_label
            // result_in->locationfound = 0;
            return result_in;
        }

        if(c == n_l[i])
        {//If current char in target_label is the same as the char @ same position in the node_label
            result_in->index++;    //move to next char in node_label and next iteration of for loop
        }
        else
        {//case 2.1: Neither target_label nor node_label have run out of chars, but the current chars differ
         //the target_label diverges from the node_label
            // prt("hit case 2.1");
            // result_in->index = i; //return the index at which they diverge for splitting later
            result_in->resultcase = Result::CaseDiv; //set case to show the target_label diverges from the node label at i
            // result_in->locationfound = 1;
            return result_in; 
        }
    }
    //all chars in target_label have been compared
    if(i < n_l.length())
    {//case 2.2: 1. The for loop ended without differing strings, and 2. end of node_label was not reached
     //The target_label is a substring of target_node's label.
        // prt("hit case 2.1");
        // result_in->index = i; //return the index at which they diverge for splitting later
        result_in->resultcase = Result::CaseSubstr;   //set case to show the target_label is a substring of the label
        // result_in->locationfound = 1;
        return result_in;
    }
    else if(i == n_l.length())
    {//case 3: 1. The for loop ended without differing strings, and 2. the entire target_node's label was compared, 
     //then the target_label is the node_label.
        // prt("hit case 3");
        // result_in->index = -1;
        result_in->resultcase = Result::CaseInTrie;   //set case to show the target_label is in the trie
        // result_in->locationfound = 1;
        return result_in;
    }
    else
        std::cout << "Something went wrong in ctrie::compareLabel! HELP!" << std::endl;
        return result_in;
}

HSHtrie::searchResult::searchResult(int index_in, CompCase case_in)
{//constructor for searchResult struct
    index = index_in;
    resultcase = case_in;
}



stack lltrie::evalCase(stack stack_in)
{//evaluates the result of the compareLabel() output and decides what to do
    LLnode* tn = stack_in->targetnode;
    comp res = stack_in->result;
    str tl = stack_in->targetlabel;

    switch (res->resultcase)
    {
    case CaseSuperstr: //if targetlabel ended up being a superstr of the targetnode's label
        if (stack_in->targetnode->child1 != nullptr)
        {//check for child @ the target node
            //if so, reset the searchStack with newly constructed searchStack that has adjusted label and targetnode
            stack_in = std::make_shared<searchStack>(tl.substr(res->index), tn->child1);
            /*turns out the index returned from compareLabel() is the position where a split would have happend
            and as such it signifies where to split the targetlabel to pass it on.*/
            return stack_in; //return searchStack to be 
        }
        else
        {//targetnode has no child, which means original target_word is not in trie.
            stack_in = std::make_shared<searchStack>(tl.substr(res->index), tn);
            res->resultcase = CaseNotInTrie;
            res->locationfound = 1;
            return stack_in;
        }
        break;
    default:
        break;
    }
    return stack_in;
}