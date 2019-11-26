#include "headers/hsh_trie.h"
// #include <string>    //included in t_nodes.h
// #include <iostream>  //included in t_nodes.h
// #include <stdio.h>   //included in t_nodes.h
// #include <memory>    //included in t_nodes.h

using str = std::string;
using Edge = EDGnode;
using s_Edge = std::shared_ptr<EDGnode>;
using Hash = HSHtrie::Hashes;
using Stack = HSHtrie::searchStack;
using s_Stack = std::shared_ptr<HSHtrie::searchStack>;
using Fstream = std::ifstream;

//---------------------CONSTRUCTORS----------------------------//
//-----------------------EDGnode----------------------------//
EDGnode::EDGnode(LLnode* parent_in, LLnode* child_in) //base constructor
    : parent(parent_in), child(child_in), childhead(child_in->head), nextedge(nullptr) {/*base constructor*/}
//-----------------------HSHtrie----------------------------//
HSHtrie::HSHtrie(int size_in, HSHtrie::Hashes hash_type, bool make_handle)
    : size(size_in)
{//full constructor//
    // std::cout << "HSHtrie size: " << this->size << std::endl;
    edgetable.resize(this->size);
    this->setHash(hash_type);
    if(make_handle)
        this->handle = new LLnode('$', "", 0, nullptr, nullptr);
}
    
Stack::searchStack(int index_in, Stack::CompCase case_in, str string_in, LLnode* start_node)
{//constructor for searchStack struct
    index = index_in;
    resultcase = case_in;
    targetstring = string_in;
    currentnode = start_node; 
    currentedge = nullptr;
}
                //MEMBER FUNCTIONS//

//-----------------------EDGnode----------------------------//
void EDGnode::print()
{//prints the edge instance
    // std::cout << "Edge: " << this << "\t";
    // if(this->parent != nullptr)
    //     std::cout << "parent: " << this->parent->head << this->parent->label << "\t";
    // std::cout << "child: " << this->child->head << this->child->label <<"\t";
    // std::cout << "childhead: " << this->childhead << "\t";
    // std::cout << "nextedge: " << this->nextedge << std::endl;
}

Edge* EDGnode::searchList(LLnode* target_parent, char target_childhead)
{//searches the linked list of EDGnode nodes for node with correct parent and childhead
    /*FILL*/
    // std::cout << "Finding parent: " << target_parent << " childhead: " << target_childhead << std::endl;
    // std::cout << "Starting from: ";
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
    // std::cout << "Did not find edge which matched the parent and childhead given." << std::endl;
    return currentedge;
}
//-----------------------HSHtrie----------------------------//
bool HSHtrie::insertString(str string_in)
{//inserts string into HSHtrie
    // std::cout << "Inserting: " << string_in << std::endl;
    //BUILD searchStack OBJECT//
    s_Stack searchstack = std::make_shared<Stack>(0, Stack::NoCase, string_in, this->handle);

    //SEARCH FOR LOCATION TO INSERT//
    searchstack = this->stackSearch(searchstack, 1);

    auto& c_n = searchstack->currentnode;
    int& i = searchstack->index;

    //INTERPRET SEARCH RESULT TO DETERMINE HOW TO//
    LLnode* newnode;
    LLnode* newnode2;
    Edge* newedge;
    Edge* newedge2;
    switch (searchstack->resultcase)
    {
    case Stack::CaseNotInTrie:
        //INSERT//
        //make new node
        newnode = new LLnode(c_n->label[i], string_in.substr(i+1), 1, nullptr, nullptr);
        //make new edge
        newedge = new Edge(c_n, newnode);
        this->insertEdge(newedge);
        break;

    case Stack::CaseSubstr:
        //INSERT//
        //make new node
        newnode = new LLnode(c_n->label[i], string_in.substr(i+1), 1, nullptr, nullptr);
        //cut new parent at index
        c_n->label = c_n->label.substr(0,i-1);
        //set new parent as wordend
        c_n->wordEnd = 1;
        //make new edge
        newedge = new Edge(c_n, newnode);
        this->insertEdge(newedge);
        break;

    case Stack::CaseDiv: //
        //INSERT//
        //new node for string being inserted
        if(i == string_in.length())
        {//if this is the case label needs to be empty str
            newnode = new LLnode(string_in[i], "", 1, nullptr, nullptr); }
        else
            newnode = new LLnode(string_in[i], string_in.substr(i+1), 1, nullptr, nullptr);
        //new node for remaining label of current node 
        newnode2 = new LLnode(c_n->label[i], string_in.substr(i+1), c_n->wordEnd, nullptr, nullptr);
        //cut parent's label at index and mark as not a word
        c_n->label = c_n->label.substr(0,i-1);
        c_n->wordEnd = 0;
        //make new edge
        newedge = new Edge(c_n, newnode);
        newedge2 = new Edge(c_n, newnode2);
        this->insertEdge(newedge);
        this->insertEdge(newedge2);
        break;

    case Stack::CaseInTrie:
        //PRINT NODE AS PROOF//
        // std::cout << "Found node:" << std::endl;
        searchstack->currentedge->child->print();
        break;

    case Stack::CaseFound:
        //NOTIFY AND PRINT NODE//
        // std::cout << "The string is in the trie. It's just not marked as a word." << std::endl;
        // std::cout << "Inserting..." << std::endl;
        searchstack->currentedge->child->wordEnd = 1; 
        break;

    default:
        std::cout << "Well done. No idea how you got here. Theres a problem with HSHtrie::stackSearch" << std::endl;
        break;
    }    

    //CONFIRM INSERT WORKED//
    if(this->search(string_in))
    {
        // std::cout << "Insert Success" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Inserting " << searchstack->targetstring << " failed." << std::endl;
        return 0;
    }

    std::cout << "You simply must teach a master class in reaching impossible locations in programs." << std::endl;
    return 0;
}

bool HSHtrie::search(str word_in)
{
    s_Stack searchstack = std::make_shared<Stack>(0, Stack::NoCase, "", this->handle);
    searchstack->currentnode = this->handle;
    searchstack->targetstring = word_in;
    searchstack = this->stackSearch(searchstack, 0);
    if(searchstack->resultcase = Stack::CaseInTrie)
        return 1;
    return 0;
}

s_Stack HSHtrie::stackSearch(s_Stack stack_in, bool insert_flag)
{
    //check if trie is empty by checking for first child node of root
    s_Stack stackout = stack_in; 
    //GET NEXT EDGnode//
    stackout->currentedge = getEDGnode(stack_in->currentnode, stack_in->targetstring[stack_in->index]); 

    if (stackout->currentedge == nullptr)
    {//if that edge doesn't exist, there is no child node with that head
        // std::cout << stackout->targetstring << " was not found in the trie." << std::endl;
        stackout->resultcase = Stack::CaseNotInTrie;
        // stackout->locationfound = NULL;
        return stackout;
    }
    //COMPARE THE LABELS(stackout->targetstring against stackout->currentedge->child->label)//
    stackout = compareSubstr(stack_in);

    //EVALUATE COMPARISON RESULT//
    switch (stackout->resultcase)
    {
    case Stack::CaseSuperstr:
        stackout->currentnode = stackout->currentedge->child;  //move the stackSearch's currentnode to the child
        //maybe edit targetstring here?
        stackout = stackSearch(stackout, 1); //recurse with child as new focus
        return stackout;
    
    case Stack::CaseInTrie:
        //PRINT NODE AS PROOF//
        if(insert_flag)//don't print if stackSearch is being called by insertStr()
            return stackout;
        std::cout << "Found node:" << std::endl;
        stackout->currentnode->print();
        return stackout;

    case Stack::CaseFound:
        //NOTIFY AND PRINT NODE//
        if(insert_flag)//don't print if stackSearch is being called by insertStr()
            return stackout;
        std::cout << "The string is in the trie. It's just not marked as a word." << std::endl;
        return stackout;

    default:
        return stackout;
    }
    std::cout << "Well done. No idea how you got here. Theres a problem with HSHtrie::stackSearch" << std::endl;
    return stackout;
}

s_Stack HSHtrie::compareSubstr(s_Stack stack_in)
{//Compares the targetstring to the target label at target_node.
 //returns case the comparison falls under, as well as the index at which to split if necessary
    //DECLARE REFERENCES//
    s_Stack stackout = stack_in;
    str& si = stack_in->targetstring; //reference ("string using i as iterator")
    str& sj = stack_in->currentedge->child->label;   //reference ("string using j as iterator") this is the target label
    int& i = stack_in->index;          //reference ("index")
    int j = 0; //index for counting through target label
    
    std::cout << "Comparing: " << si << " against " << sj << std::endl;

    while (j < sj.length() && si[i] == sj[j])
    {//while we haven't reached the end of the target label and the current characters match
        //INCREMENT INDEXES//
        i++;
        j++;
        if (i == si.length())
        {//if end of targetstring is reached, but still comparing
            //SET SEARCH CASE//
            stackout->resultcase = Stack::CaseSubstr;
            return stackout;
        }        
    }
    //POST WHILE LOOP CHECKS//
    if (j == sj.length())
    {//this means we went though the entire target label
       if (i < si.length())
       {//this means there is still more of the targetstring left
           //SET SEARCH CASE//
           stackout->resultcase = Stack::CaseSuperstr; }
       else if (i == si.length())
       {//this means the target label and the substring of the targetstring are identical suffixes
           //SET SEARCH CASE//
           if (stack_in->currentedge->child->wordEnd)
           {//if the child is marked as end of word
               stackout->resultcase = Stack::CaseInTrie; }
           else//targetstring was found, but isn't marked as a word
               stackout->resultcase = Stack::CaseFound; } } 
    else if (j < sj.length())
    {//this means the strings stopped matching before the end of the target label was reached
        //SET SEARCH CASE//
        stackout->resultcase = Stack::CaseDiv; }
    //THIS POINT SHOULD NEVER BE REACHED//
        //j might have overflowed past the end of the target label
    std::cout << "You shouldn't be here. Don't pay any attention to the man behind the curtain. HSHtrie::compareSubstr has problems." << std::endl;
    return stackout;
    
    //OLD compareLable()
    // for(char c:si) //What if comparing single letter which already exists at target_node? c=null?
    // {//for each char in the targetstring, compare it against the label @ the target_node

    //     if(i == sj.length())
    //     {//case 1: If the index for target label is equal to the  length of target label and
    //      //the for loop is still going, the targetstring is a superstring of the target label
    //         // stack_in->index = i;  //return index of where to begin 
    //         stack_in->resultcase = Stack::CaseSuperstr; //case to show the targetstring is a superstring of the target label
    //         // stack_in->locationfound = 0;
    //         return stack_in;
    //     }

    //     if(c == sj[i])
    //     {//If current char in targetstring is the same as the char @ same position in the target label
    //         i++;    //move to next char in target label and next iteration of for loop
    //     }
    //     else
    //     {//case 2.1: Neither targetstring nor target label have run out of chars, but the current chars differ
    //      //the targetstring diverges from the target label
    //         // prt("hit case 2.1");
    //         // stack_in->index = i; //return the index at which they diverge for splitting later
    //         stack_in->resultcase = Stack::CaseDiv; //set case to show the targetstring diverges from the node label at i
    //         // stack_in->locationfound = 1;
    //         return stack_in; 
    //     }
    // }
    // //all chars in targetstring have been compared
    // if(i < sj.length())
    // {//case 2.2: 1. The for loop ended without differing strings, and 2. end of target label was not reached
    //  //The targetstring is a substring of target_node's label.
    //     // prt("hit case 2.1");
    //     // stack_in->index = i; //return the index at which they diverge for splitting later
    //     stack_in->resultcase = Stack::CaseSubstr;   //set case to show the targetstring is a substring of the label
    //     // stack_in->locationfound = 1;
    //     return stack_in;
    // }
    // else if(i == sj.length())
    // {//case 3: 1. The for loop ended without differing strings, and 2. the entire target_node's label was compared, 
    //  //then the targetstring is the target label.
    //     // prt("hit case 3");
    //     // stack_in->index = -1;
    //     stack_in->resultcase = Stack::CaseInTrie;   //set case to show the targetstring is in the trie
    //     // stack_in->locationfound = 1;
    //     return stack_in;
    // }
}

bool HSHtrie::insertEdge(Edge* edge_in)
{//Inserts given edge into the edgetable.

    int hashresult = getHash(edge_in->child, edge_in->childhead);
    if (this->edgetable[hashresult] != nullptr)
    {//if edgetable has an entry there already
        //PUSH LINKED LIST OUT OF SLOT//
        Edge* collidingedge = this->edgetable[hashresult]; //push linked list down
        //INSERT EDGE AT FRONT OF LINKED LIST//
        edge_in->nextedge = collidingedge;
        //PUT newedge IN EMPTY edgetable SLOT//
        this->edgetable[hashresult] = edge_in; }
    else //JUST INSERT//
        this->edgetable[hashresult] = edge_in;
    return 1;
}

bool HSHtrie::insertEdgeFromLLtrie(LLnode* parent_in, LLnode* child_in)
{//insert function, uses this->hash()
    Edge* newedge;
    if(parent_in != nullptr)
    {//first insert will be root with nullptr as parent, checking for no nullptr means 1 check per insert
     //other way around we'd be constantly checking for root
        newedge = new Edge(parent_in, child_in); }
    else
    {//if we are inserting root
        this->handle = child_in;
        newedge = new Edge(nullptr, child_in); 
    }

    return this->insertEdge(newedge);
}

void HSHtrie::setHash(Hash desired_hash)
{//sets the HSHtrie's hash function to one of the defined options in the Hashes enum
    // std::cout << "Setting hash function to: " << desired_hash << std::endl;

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

EDGnode* HSHtrie::getEDGnode(LLnode* parent_in, char head_in)
{
    int hash = getHash(parent_in, head_in);
    Edge* targetedge = this->edgetable[hash];
    if(targetedge == nullptr)
    {
        // std::cout << "Did not find that edge in edgetable." << std::endl;
        return targetedge;
    }
    targetedge = targetedge->searchList(parent_in, head_in);
    return targetedge; 
}
  
int HSHtrie::testSearch()
{
    std::ifstream inputstream("word_list.txt");
    str targetword;
    //START TIMER AND BEGIN//
    auto start = std::chrono::high_resolution_clock::now();
    while (inputstream >> targetword)
    {
        this->search(targetword);
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "HSHtrie performance for stackSearch: " << microseconds << " micro-sec" << std::endl;
    inputstream.close();
    return microseconds;
}
//---------------------HASH FUNCTIONS----------------------------//
int HSHtrie::primeHash(int parent_addr, char child_head)
{//hash with basic arthimetic and prime mod
    int b = 5;
    int result = ((parent_addr + (int)child_head * (unsigned int)std::pow(b,31)) % this->size);
    return result;
}