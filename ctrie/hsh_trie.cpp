#include "headers/hsh_trie.h"
// #include <string>    //included in t_nodes.h
// #include <iostream>  //included in t_nodes.h
// #include <stdio.h>   //included in t_nodes.h
// #include <memory>    //included in t_nodes.h

using str = std::string;
using Node = LLnode;
using Edge = EDGnode;
using s_Edge = EDGnode;
using Hash = HSHtrie::Hashes;
using Stack = HSHtrie::searchStack;
using s_Stack = std::shared_ptr<HSHtrie::searchStack>;
using Fstream = std::ifstream;

                  //CONSTRUCTORS//
//-----------------------EDGnode----------------------------//
EDGnode::EDGnode(Node* parent_in, Node* child_in) //base constructor
    : parent(parent_in), child(child_in), childhead(child_in->head), nextedge(nullptr) {/*base constructor*/}
//-----------------------HSHtrie----------------------------//
HSHtrie::HSHtrie(int size_in, HSHtrie::Hashes hash_type)
    : size(size_in)
{//full constructor//
    // std::cout << "HSHtrie size: " << this->size << std::endl;
    edgetable.resize(this->size);
    this->setHash(hash_type);

}
    
Stack::searchStack(int index_in, Stack::CompCase case_in, str string_in, Node* start_node)
{//constructor for searchStack struct
    index = index_in;
    resultcase = case_in;
    targetstring = string_in;
    Node* currentnode = start_node; 
    currentedge = nullptr;
}
                //MEMBER FUNCTIONS//

//-----------------------EDGnode----------------------------//
void EDGnode::print()
{//prints the edge instance
    std::cout << "Edge: " << this << "\t";
    if(this->parent != nullptr)
        std::cout << "parent: " << this->parent->head << this->parent->label << "\t";
    std::cout << "child: " << this->child->head << this->child->label <<"\t";
    std::cout << "childhead: " << this->childhead << "\t";
    std::cout << "nextedge: " << this->nextedge << std::endl;
}

Edge* EDGnode::searchList(Node* target_parent, char target_childhead)
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

bool HSHtrie::insertString(str string_in)
{//inserts string into HSHtrie
    std::cout << "Inserting: " << string_in << std::endl;
    //BUILD searchStack OBJECT//
    s_Stack searchstack = std::make_shared<s_Stack>(0, Stack::NoCase, string_in, this->root);

    //SEARCH FOR LOCATION TO INSERT//
    searchstack = this->search(searchstack, 1);

    Node c_n = &(searchstack->currentnode);
    int& i = searchstack->index;

    //INTERPRET SEARCH RESULT//
    switch (searchstack->resultcase)
    {
    case Stack::CaseNotInTrie:
        //INSERT//
        //make new node
        Node* newnode = new Node(string_in[i], string_in.substr(i+1), 1);
        //make new edge
        Edge newedge = new Edge(c_n, newnode);
        break;

    case Stack::CaseSubstr:
        //INSERT//
        //make new node
        Node* newnode = new Node(c_n->label[i], string_in.substr(i+1), 1);
        //cut new parent at index
        c_n->label = c_n->label.substr(0,i-1);
        //set new parent as wordend
        c_n->wordEnd = 1;
        //make new edge
        Edge newedge = new Edge(c_n, newnode);
        break;

    case Stack::CaseDiv: //
        //INSERT//
        //new node for string being inserted
        if(i == string_in.length())
        {//if this is the case label needs to be empty str
            Node* newnode = new Node(string_in[i], "", 1); }
        else
            Node* newnode = new Node(string_in[i], string_in.substr(i+1), 1);
        //new node for remaining label of current node 
        Node* remainingstr = new Node(c_n->label[i], string_in.substr(i+1), c_n->wordEnd);
        //cut parent's label at index and mark as not a word
        c_n->label = c_n->label.substr(0,i-1);
        c_n->wordEnd = 0;
        //make new edge
        Edge newnodeedge = new Edge(c_n, newnode);
        Edge remainingstredge = new Edge(c_n, remainingstr);
        break;

    case Stack::CaseInTrie:
        //PRINT NODE AS PROOF//
        std::cout << "Found node:" << std::endl;
        stackout->currentedge->child->print();
        break;

    case Stack::CaseFound:
        //NOTIFY AND PRINT NODE//
        std::cout << "The string is in the trie. It's just not marked as a word." << std::endl;
        std::cout << "Inserting..." << std::endl;
        searchstack->currentedge->child->wordEnd = 1; 
        break;

    default:
        std::cout << "Well done. No idea how you got here. Theres a problem with HSHtrie::search" << std::endl;
        break;
    }    

    //CONFIRM INSERT WORKED//
    if(this->insertString(searchstack->targetstring))
        return 1;
    else
        std::cout << "Inserting " << searchstack->targetstring <<< " failed." << std::endl;
        return 0;
}

s_Stack HSHtrie::search(s_Stack stack_in, bool insert_flag)
{
    //check if trie is empty by checking for first child node of root
    s_Stack stackout = stack_in; 
    //GET NEXT EDGnode//
    stackout->currentedge = getEDGnode(stack_in->currentnode, stack_in->targetstring[stack_in->index]); 

    if (stackout->currentedge == nullptr)
    {//if that edge doesn't exist, there is no child node with that head
        std::cout << stackout->targetstring << " was not found in the trie." << std::endl;
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
        stackout->currentnode = stackout->currentedge->child;  //move the search's currentnode to the child
        //maybe edit targetstring here?
        stackout = search(stackout); //recurse with child as new focus
        return stackout;
    
    case Stack::CaseInTrie:
        //PRINT NODE AS PROOF//
        if(insert_flag)//don't print if search is being called by insertStr()
            return stackout;
        std::cout << "Found node:" << std::endl;
        stackout->currentnode->print();
        return stackout;

    case Stack::CaseFound:
        //NOTIFY AND PRINT NODE//
        if(insert_flag)//don't print if search is being called by insertStr()
            return stackout;
        std::cout << "The string is in the trie. It's just not marked as a word." << std::endl;
        return stackout;

    default:
        return stackout;
    }
    std::cout << "Well done. No idea how you got here. Theres a problem with HSHtrie::search" << std::endl;
    return stackout;
}

s_Stack HSHtrie::compareSubstr(s_Stack stack_in)
{//Compares the targetstring to the target label at target_node.
 //returns case the comparison falls under, as well as the index at which to split if necessary
    //DECLARE REFERENCES//
    s_Stack stackout = stack_in;
    str& si = stack_in->targetstring; //reference ("string using i as iterator")
    str& sj = stack_in->currentedge->child->label;   //reference ("string using j as iterator")
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
           {//if the targetlabel is marked as end of word
               stackout->resultcase = Stack::CaseInTrie; }
           else//targetstring was found, but isn't marked as a word
               stackout->resultcase = Stack::CaseFound; } } 
    else if (j < sj.length())
    {//this means the strings stopped matching before the end of the targetlabel was reached
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

bool HSHtrie::insertEdge(Node* parent_in, Node* child_in)
{//insert function, uses this->hash()
    Edge* newedge;
    int hashresult;

    if(parent_in != nullptr)
    {//first insert will be root with nullptr as parent, checking for no nullptr means 1 check per insert
     //other way around we'd be constantly checking for root
        newedge = new Edge(parent_in, child_in);
        hashresult = getHash(parent_in, child_in->head); }
    else
    {//if we are inserting root
        this->handle = child_in;
        newedge = new Edge(nullptr, child_in); 
        hashresult = getHash(child_in, child_in->head);
    }

    if (this->edgetable[hashresult] != 0)
    {//if edgetable has an entry there already
        //PUSH LINKED LIST OUT OF SLOT//
        Edge* collidingedge = this->edgetable[hashresult]; //push linked list down
        //INSERT newedge AT FRONT OF LINKED LIST//
        newedge->nextedge = collidingedge;
        //PUT newedge IN EMPTY edgetable SLOT//
        this->edgetable[hashresult] = newedge;
        // std::cout << "Inserting: " << std::endl;
        // newedge->print();
        std::cout << " @ " << hashresult << std::endl; }
    else //JUST INSERT//
    {
        // std::cout << "Inserting: " << std::endl;
        // newedge->print();
        std::cout << " @ " << hashresult << std::endl;
        this->edgetable[hashresult] = newedge;
    }

    return 1;
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

int HSHtrie::getHash(Node* parent_in, char head_in)
{//small abstraction for hash function so I don't have to remember the special syntax everytime
    int parentaddr = reinterpret_cast<std::uintptr_t>(parent_in); 
    return (this->*hash)(parentaddr, head_in);
}

EDGnode* HSHtrie::getEDGnode(Node* parent_in, char head_in)
{
    int hash = getHash(parent_in, head_in);
    Edge* target_edge = this->edgetable[hash];
    target_edge = target_edge->searchList(this->handle, this->handle->head);

    return target_edge; 
}
  
void HSHtrie::testSearch()
{
    std::ifstream inputstream("word_list.txt");
    s_Stack resultinit = std::make_shared<Stack>(0, Stack::NoCase, "", this->root);
    resultinit->currentnode = this->handle;
    str targetword;
    //START TIMER AND BEGIN//
    auto start = std::chrono::high_resolution_clock::now();
    while (inputstream >> targetword)
    {
        resultinit->targetstring = targetword;
        this->search(resultinit, 0);
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "HSHtrie performance for search: " << microseconds << " micro-sec" << std::endl;
    inputstream.close();
}


                  //HASH FUNCTIONS//

int HSHtrie::primeHash(int parent_addr, char child_head)
{//hash with basic arthimetic and prime mod
    int b = 5;
    int result = ((parent_addr + (int)child_head * (unsigned int)std::pow(b,31)) % this->size);
    return result;
}