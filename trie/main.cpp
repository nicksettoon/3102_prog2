#include "headers/tools.h"
// using str = std::string;    //from tools.h
// using node = tnode::Node;   //from tools.h
/*FILL_LATER*/

using str = std::string;    //type abstraction for easier use
auto& prt = tools::print;   //"alias" for print function

int main()
{//main function
    // tools::printFile("WORD.LST");
    // prt("blah");
    // tools::pwd();

    // str s = "string";
    // prt(s);
    // tools::printc(s[0]);
    str s = "Random string";
	std::cout << s.substr(1) << '\n';
    s.erase();
	// std::cout << s.replace(0,1,"") << '\n';
    return 0;
}