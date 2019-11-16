#include "headers/llnode.h"
#include <stdio.h>
#include <memory>
#include <string>
// #include <iostream> //included in llnode.h
enum alpha
{
    A=0,a,B,b,C,c,D,d,E,e,F,f,G,g,H,h,I,i,J,j,K,k,L,l,M,m,N,n,O,o,P,p,Q,q,R,r,S,s,T,t,U,u,V,v,W,w,X,x,Y,y,Z,z
};


int main()
{
    std::string str = "elephant";
    char head = str[0];

    std::shared_ptr<LLNode> nodes[52];
    nodes[0] = std::make_shared<LLNode>('A');
   
    int j = 0;
    for(int i=66; i<=90;i++)
    {
        std::shared_ptr<LLNode> node = std::make_shared<LLNode>(static_cast<char>(i));
        nodes[(i-65)] = node;
        nodes[(i-66)]->rightsib = node; 
        j++;
    }
    j++;

    for(int i=97;i<=122;i++)
    {
        std::shared_ptr<LLNode> node = std::make_shared<LLNode>(static_cast<char>(i));
        nodes[(j+i-97)] = node;
        nodes[(j+i-98)]->rightsib = node; 
    }

    nodes[0]->printSibs();
    // node* node3 = new node("de", 1);
    // node* node2 = new node("ca", 0, node3, nullptr);
    // node* node1 = new node("ba", 0, node2, nullptr);

    // node1->printSibs();
    // printf("wordhead: %c\n", node1->head);
    // std::cout << "label: " << node1->label << std::endl;
    // str eow = (node1->eow == 1) ? "yes":"no";
    // printf("eow?: %d\n", node1->eow);
}