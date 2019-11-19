#include "headers/ctrie.h"
// #include <string>   //included in llnode.h
// #include <iostream> //included in llnode.h
// #include <memory>   //included in llnode.h
// #include <stdio.h>  //included in llnode.h

using str = std::string;
using node = std::shared_ptr<LLNode>; //"alias" for LLNode to make it easier to type
using comp = std::shared_ptr<compResult>; //"alias" for compResult to make it easier to type

CompTrie::CompTrie()
{
    printf("\nConstructing CompTrie.\n");
}

CompTrie::~CompTrie()
{
    printf("\nDeleteing CompTrie.\n");
}