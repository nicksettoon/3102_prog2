#include "headers/tools.h"
// using str = std::string;    //from tools.h
// using node = tnode::Node;   //from tools.h
/*FILL_LATER*/

auto& prt = tools::print;   //"alias" for print function

int main()
{//main function
    tools::printFile("WORD.LST");
    prt("blah");
    tools::pwd();
    return 0;
}