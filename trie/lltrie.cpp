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

bool LinkedList::search(str target_word)
{//finds word in linked list if it exists
    printf("Finding head from starting node: \t");
    this->root->print();
    std::shared_ptr<findNodeResult> result;
    result = this->root->findNode(target_word[0]);

    comp compresult;
    switch (result->res)
    {
    case atnode 
        compresult = compareLabel(result->targetnode, target_word.substr(1)); //compare the two labels at the resulting node
        if(compresult->resultcase == CaseSuperstr)
        {//if label is a superstr of the target label, search the child's linked list for the remaining word past the index of separation
            result->targetnode->child1->search(target_word.substr(compresult->index+1));
        }
        else
        {

        }
        break;
    default:
        std::cout << target_word << "is not in this Linked List." << std::endl;
        return 0;
        break;
    }
}

searchStack::searchStack(str target_word, snode target_node)
{//constructor for searchStack struct
    head = target_word[0];     //set head to be the first char of the target_word
    targetnode = target_node;
    targetlabel = target_word.substr(1);   //set target_label to everything after the wordhead
    result = std::make_shared<compResult>(-1, NoCase);      //set result to nullptr cause no comparison has happened yet
};

void searchStack::print()
{
    printf("Printing searchStack.\n");
    std::cout << "Head: " << this->head;
    std::cout << "\ttargetnode: " << this->targetnode->head << this->targetnode->label;
    std::cout << "\ttargetlabel: " << this->targetlabel << std::endl;
    std::cout << "result index: " << result->index << "\t endsearch: " << result->endsearch << "\tcase: " << result->resultcase;
}
searchStack::~searchStack()
{
    printf("Deleting searchStack.\n");
    this->print();
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

snode lltrie::add(snode in_node, snode neighbor, bool child) 
{//actually responsible for adding a node at a given neighbor node
    printf("Adding node.\n");
    if(child)
    {
        printf("Adding child node.\n");
        neighbor->child1 = in_node;     //add given node as child
        return neighbor;
    }
    else
    {
        if (neighbor->rightsib == nullptr)
        {
            printf("neighbor has no right sib.\n");
            std::cout << "in_node: " << in_node->head << in_node->label << std::endl;
            std::cout << "neighbor: " << neighbor->head << neighbor->label << std::endl;
            in_node->leftsib = neighbor;
            neighbor->rightsib = in_node;
            std::cout << "in_node use_count: " << in_node.use_count() <<std::endl;
            neighbor->printSibs();
            return neighbor;
        }
        //make in_node the leftsib of neighbor's rightsib
        printf("rightsib of neighbor exists.\n");
        std::cout << "in_node: " << in_node->head << in_node->label << std::endl;
        std::cout << "neighbor: " << neighbor->head << neighbor->label << std::endl;
        neighbor->rightsib->leftsib = in_node;
        in_node->rightsib = neighbor->rightsib;
        //make in_node the rightsib of neighbor
        in_node->leftsib = neighbor;
        neighbor->rightsib = in_node;
        return neighbor;
    }
}

bool lltrie::insert(str target_word)
{//frontend for inserting word via linked list implementation
    std::cout << "\nInserting: " << target_word << std::endl;

    if(this->root->child1 == nullptr)
    {//if there is no first child of this trie
        printf("Root node has no children yet.\n");
        snode newchild = std::make_shared<LLNode>(target_word,1);
        add(newchild, this->root, 1); //add new node w/ target_word as child of root node
        // this->root->child1 = new node(target_word, 1); //make one with the given word
        // return this->root->child1;
        std::cout << "Inserted " << target_word << std::endl;
        this->root->child1->printSibs();
        return 1;
    }

    std::cout << "targethead: " << target_word[0] << std::endl;
    snode targetnode = this->root->child1->findHead(target_word[0]); //search for node with head=first letter of target word
    std::cout << "found node: " << targetnode->head << targetnode->label << std::endl;
    stack newstack;
    if (targetnode == nullptr)
    {//this happens when the node being inserted belongs at the front of the child linked list
        snode newnode = std::make_shared<LLNode>(targetnode, 1);
        add(newnode, targetnode) 
    }
    
    if (targetnode->head != target_word[0])
    {//if findHead did not return the correct node containing head=target_word[0], add the word to the right of the returned node
        snode newnode = std::make_shared<LLNode>(target_word, 1);   //make newnode
        targetnode = add(newnode, targetnode, 0);    //add newnode inbetween neighbor and neighbor's rightsib
        targetnode->printSibs();
        std::cout << "in_node use_count2: " << targetnode.use_count() <<std::endl;
        // return newnode; //return inserted node
        this->root->child1->printSibs();
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
        this->root->child1->printSibs();
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
    printf("Entering insertCase().\n");
    snode tn = stack_in->targetnode;
    comp res = stack_in->result;
    str tl = stack_in->targetlabel;
    bool inserted = 0;

    snode node1;
    snode node2;

    switch(res->resultcase)
    {
    case CaseDiv:
        printf("Entering CaseDiv.\n");
        //divides node into two child nodes and a parent
        //1. make new node for remaining node_label and set eow for that node to its previous eow
        node1 = std::make_shared<LLNode>(tn->label.substr(res->index),tn->eow);
        //2. make new node for remaining target_label w/ eow of 1
        node2 = std::make_shared<LLNode>(tl.substr(res->index),1); //node for new word getting inserted
        //3. edit current node's label and set eow on current node to 0
        tn->edit(tn->label.substr(1,res->index+1),0);
        //hook everything together
        if (node1->head < node2->head)
        {//alphabetical insert
            add(node1, tn, 1);
            add(node2, node1, 0);
            // node1->rightsib = node2;
            // node2->leftsib = node1;
        }
        else
        {//node1->head > node2->head
            add(node2, tn, 1);
            // tn->child1 = node2;
            add(node1, node2, 0);
            // node2->rightsib = node1;
            // node1->leftsib = node2;
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
        add(node1, tn, 1);
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