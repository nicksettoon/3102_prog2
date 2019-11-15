#include <iostream>
#include "headers/lltrie.h"
#include <stdio.h>

using node = LLNode;

int main()
{

    node* node3 = new node("de", 1);
    node* node2 = new node("ca", 0, node3, nullptr);
    node* node1 = new node("ba", 0, node2, nullptr);

    node1->printSibs();
    // printf("wordhead: %c\n", node1->head);
    // std::cout << "label: " << node1->label << std::endl;
    // str eow = (node1->eow == 1) ? "yes":"no";
    // printf("eow?: %d\n", node1->eow);
}