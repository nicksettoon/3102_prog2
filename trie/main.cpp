#include <memory>
#include "headers/tools.h"
#include "headers/ctrie.h"
// using str = std::string;    //from tools.h
// using node = tnode::Node;   //from tools.h
/*FILL_LATER*/
//function parameters are underscored. function variables are just appended.

using str = std::string;    //type abstraction for easier use
// auto& prt = tools::print;   //"alias" for print function

int main()
{//main function
    // tools::printFile("WORD.LST");
    // prt("blah");
    // tools::pwd();

    std::unique_ptr<ctrie::LLCompTrie> Trie = std::make_unique<ctrie::LLCompTrie>(); //make unique pointer for trie
    
    // Trie.insert("baggage");
    // Trie.insert("bag");
    // Trie.insert("bags");
    // Trie.insert("babbage");
	// std::cout << s.replace(0,1,"") << '\n';
    return 0;
}