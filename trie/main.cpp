#include "headers/lltrie.h"
// #include <string>   //included in llnode.h
// #include <iostream> //included in llnode.h
// #include <memory>   //included in llnode.h
// #include <stdio.h>  //included in llnode.h

using snode = std::shared_ptr<LLNode>;

LLNode* initNodes();

int main()
{
    // LLNode* root = initNodes();
    // snode st = root->child1;
    LLCompTrie trie;

    trie.insert("bad");

    trie.insert("cadet");
    trie.root->child1->printSibs();
    trie.insert("add");
    trie.root->child1->printSibs();
    // trie.insert("bat");
    // trie.root->child1->printSibs();
    // trie.insert("babbage");
    // trie.root->child1->printSibs();
    // trie.insert("batter");
    // trie.root->child1->printSibs();

    // trie.search("bad");
    // trie.search("cadet");
    // trie.search("add");
    // trie.search("bat");
    // trie.search("babbage");
    // trie.search("batter");
    // trie.search("adder");

    // std::cin.get();
    //find place newnode should be placed at
}

LLNode* initNodes()
{//initialize trie manually for testing

    LLNode* root = new LLNode();
    root->child1 = std::make_shared<LLNode>('A');
   
    snode tn = root->child1;
    
    for(int i=66; i<=90;i++)
    {
        snode node = std::make_shared<LLNode>(static_cast<char>(i));
        tn->rightsib = node;
        node->leftsib = tn;
        tn = node; 
    }

    for(int i=97;i<=122;i++)
    {
        snode node = std::make_shared<LLNode>(static_cast<char>(i));
        tn->rightsib = node;
        node->leftsib = tn;
        tn = node; 
    }
    
    return root;
}

// enum alpha
// {
//     A=0,a,B,b,C,c,D,d,E,e,F,f,G,g,H,h,I,i,J,j,K,k,L,l,M,m,N,n,O,o,P,p,Q,q,R,r,S,s,T,t,U,u,V,v,W,w,X,x,Y,y,Z,z
// };