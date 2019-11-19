#include "llnode.h"


using str = std::string;

LLNode::LLNode(char letter_in, str label_in, bool eow_in, LLNode* child_1, LLNode* r_sibling_in) //constructor
    : letter(letter_in), label(label_in), isWord(eow_in), firstChild(child_1), rightSibling(r_sibling_in) {}

