#include "test.h"



searchStack::searchStack(str target_word, node* child_1)
{//constructor for searchStack struct
    wordhead = target_word[0];     //set wordhead
    targetnode = child_1->findHead(wordhead); //set new target_node with result of findHead() on the 1st child
    targetlabel = target_word.substr(1);   //set target_label to everything after the wordhead
    result = nullptr;      //set result to nullptr cause no comparison has happened yet
}

compResult::compResult(int index_in, CompCase case_in)
{//constructor for compResult struct
    index = index_in;
    resultcase = case_in;
}