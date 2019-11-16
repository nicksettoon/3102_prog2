#include "headers/lltrie.h"
// #include <string>   //included in llnode.h
// #include <iostream> //included in llnode.h
// #include <memory>   //included in llnode.h
// #include <stdio.h>  //included in llnode.h

using lltrie = LLCompTrie;
using str = std::string;
using snode = std::shared_ptr<LLNode>; //"alias" for LLNode to make it easier to type
using comp = std::shared_ptr<compResult>; //"alias" for compResult to make it easier to type
using stack = std::shared_ptr<searchStack>; //"alias" for compResult to make it easier to type


searchStack::searchStack(str target_word, snode target_node)
{//constructor for searchStack struct
    head = target_word[0];     //set head to be the first char of the target_word
    targetnode = target_node;
    targetlabel = target_word.substr(1);   //set target_label to everything after the wordhead
    result = std::make_shared<compResult>(-1, NoCase);      //set result to nullptr cause no comparison has happened yet
};

searchStack::~searchStack()
{
    printf("Deleting searchStack.");
}

lltrie::LLCompTrie()
{//default constructor
    printf("\nConstructing LLCompTrie.\n"); //notification
    this->root = std::make_shared<LLNode>();   //create smart shared pointer for root node
}

void lltrie::search(str target_word)
{//front end for search
    stack newstack = std::make_shared<searchStack>(target_word, this->root->child1);
    newstack = searchTrie(newstack);
    if (newstack->result->resultcase != CaseInTrie)
    {
        bool end = 0;
        while( end != 1)
        {
            printf("Did not find ");
            std::cout << target_word;
            printf(" in trie.\nInsert it? [y/n]");
            str input;
            std::cin >> input;

            if(input == "Y" || input == "y")
            {
                insert(target_word);
                end = 1;
            }

            else if(input == "N" || input == "n")
            {
                printf("Ok. Closing");
                end = 1;
            }
            else
            {printf("I did not understand your input. Please try again.");}
        }
       
    }
   
}

stack lltrie::searchTrie(stack stack_in)
{//searches Trie and returns searchStack struct with result of the search.
    comp result = compareLabel(stack_in->targetnode, stack_in->targetlabel); //compare labels @ targetnode
    stack_in->result.reset(); //put result in searchStack
    stack_in->result = result;
    stack_in = evalCase(stack_in);  //evaluate the result
    return stack_in;    //hitting this means the while loop finished.
}

stack lltrie::evalCase(stack stack_in)
{//evaluates the result of the compareLabel() output and decides what to do
    snode tn = stack_in->targetnode;
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
            res->endsearch = 1;
            return stack_in;
        }
        break;
    default:
        break;
    }
    return stack_in;
}

void lltrie::add(snode in_node, snode neighbor, bool child) 
{//actually responsible for adding a node at a given neighbor node

    if(child)
        neighbor->child1 = in_node;     //add given node as child
    else
    {
        //make in_node the leftsib of neighbor's rightsib
        neighbor->rightsib->leftsib = in_node;
        in_node->rightsib = neighbor->rightsib;
        //make in_node the rightsib of neighbor
        in_node->leftsib = neighbor;
        neighbor->rightsib = in_node;
    }
}

bool lltrie::insert(str target_word)
{//frontend for inserting word via linked list implementation
    // prt("Entering LLinsert().")

    if(this->root->child1 == nullptr)
    {//if there is no first child of this trie
        // prt("Root node has no children yet.");
        snode newchild = std::make_shared<LLNode>(target_word,1);
        add(newchild, this->root, 1); //add new node w/ target_word as child of root node
        // this->root->child1 = new node(target_word, 1); //make one with the given word
        // return this->root->child1;
        std::cout << "Inserted " << target_word << std::endl;
        return 1;
    }

    snode targetnode = this->root->child1->findHead(target_word[0]); //search for node with head=first letter of target word
    stack newstack;
    if (targetnode->head != target_word[0])
    {//if findHead did not return the correct node containing head=target_word[0], add the word to the right of the returned node
        snode newnode = std::make_shared<LLNode>(target_word, 1);   //make newnode
        add(newnode, targetnode, 0);    //add newnode inbetween neighbor and neighbor's rightsib
        // return newnode; //return inserted node
        std::cout << "Inserted " << target_word << std::endl;
        return 1;
    }
    else //targetnode->head == target_word[0]
    {//make new searchStack with target_word, and targetnode
        newstack = std::make_shared<searchStack>(target_word, targetnode);
        while(newstack->result->endsearch == 0)
        {//while the search hasn't resulted in a terminating search case (CaseDiv, CaseSubstr, CaseInTrie)
            newstack = searchTrie(newstack);    //search the Trie for the correct insertion point
        }
    }
    //after search has finished insert node based on newstack->result.resultcase
    bool success = insertCase(newstack);
    if(success)
    {
        std::cout << "Inserted " << target_word << std::endl;
        return success;
    }
    else
    {
        std::cout << "Failed to insert " << target_word << std::endl;
        return ~success;
    }

}

bool lltrie::insertCase(stack stack_in)
{//called to do the inserting based on the case in stack_in->result
    //declare some quick shared_ptrs to make things easier to type
    printf("Entering insertCase().");
    snode tn = stack_in->targetnode;
    comp res = stack_in->result;
    str tl = stack_in->targetlabel;
    bool inserted = 0;

    snode node1;
    snode node2;

    switch(res->resultcase)
    {
    case CaseDiv:
        printf("Entering CaseDiv.");
        //divides node into two child nodes and a parent
        //1. make new node for remaining node_label and set eow for that node to its previous eow
        node1 = std::make_shared<LLNode>(tn->label.substr(res->index),tn->eow);
        //2. make new node for remaining target_label w/ eow of 1
        node2 = std::make_shared<LLNode>(tl.substr(res->index),1); //node for new word getting inserted
        //3. edit current node's label and set eow on current node to 0
        tn->edit(tn->label.substr(1,res->index - 1),0);
        //hook everything together
        if (node1->head < node2->head)
        {//alphabetical insert
            tn->child1 = node1;
            node1->rightsib = node2;
            node2->leftsib = node1;
        }
        else
        {//node1->head > node2->head
            tn->child1 = node2;
            node2->rightsib = node1;
            node1->leftsib = node2;
        }
        inserted = 1;
        break;
    case CaseSubstr:
        printf("\nEntering CaseSubstr.\n");
        //1. make new_node for split label
        node1 = std::make_shared<LLNode>(tn->label.substr(res->index),tn->eow);
            //2.1 set eow for new_node to 1
        tn->edit(tl,1); //2. edit current node's label and set eow to 1
        //hook everything together
        tn->child1 = node1;
        inserted = 1;
        break;
    case CaseInTrie:
        printf("\nEntering CaseInTrie.\n");
        tn->eow = 1; //Change eow flag on target_node to 1
        inserted = 1;
        break;
    default:
        // throw exception;
        printf("\ninsertCase() did not hit any of the valid insert cases.\n");
        inserted = 0;
        break;
    }
    return inserted;
}

lltrie::~LLCompTrie()
{//default constructor
    printf("\nDeleting LLCompTrie.\n"); //notification
}