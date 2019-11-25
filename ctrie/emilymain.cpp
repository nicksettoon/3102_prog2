/* Programming Homework 2
Emily Vu, Ferris DeHart
CSC 3102
*/
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

class Node{
    public:
        char letter;
        string label; //data
        bool isEnd; //indicates whether current node is whole word or not
        Node * sibling; //node to right
        Node * child;
        Node()
        {
        }
        Node(char letter, Node * sibling, Node * child)
        {
            this->letter = letter;
            this->sibling = sibling;
            this->child = child;
        }
};

class NodeAddResult
{
    public:
    Node * node;
    bool added;
    NodeAddResult(Node * node, bool added)
    {
        this->node = node;
        this->added = added;
    }

};

class Trie
{
    public:
    char terminate = '$';
    Node * root;
    Trie()
    {
        root = new Node();
    }
    Node * getChild(Node * starter, char c)
    {
        Node * nextSibling = starter;
        while(nextSibling != nullptr)
        {
            if(nextSibling->letter == c)
            {
                break;
            }
            nextSibling = nextSibling->sibling;
        }
        return nextSibling;
    }

    NodeAddResult * addSiblingNode(Node * starter, char c)
    {
        if(starter == nullptr)
        {
            starter = new Node(c, nullptr, nullptr);
            return new NodeAddResult(starter, true);
        }
        else
        {
            Node * next = starter;
            while(next->sibling != nullptr)
            {
                if(next->letter == c)
                {
                    break;
                }
                next = next->sibling;
            }
            if(next->letter == c)
            {
                return new NodeAddResult(next, false);
            }
            else
            {
                next->sibling = new Node(c, nullptr, nullptr);
                return new NodeAddResult(next->sibling, true);
            }
        }
    }

    Node * findSibling(Node * sibling, char c)
    {
        Node * next = sibling;
        while(next != nullptr)
        {
            if(next->letter == c)
            {
                break;
            }
            next = next->sibling;
        }
        return next;
    }

    NodeAddResult * addChildNode(Node * parent, char c)
    {
        if(parent->child == nullptr)
        {
            parent->child = new Node(c, nullptr, nullptr);
            return new NodeAddResult(parent->child, true);
        }
        else
        {
            return addSiblingNode(parent->child, c);
        }
    }

    Node * findChild(Node * parent, char c)
    {
        return findSibling(parent->child, c);
    }


    bool add(string s)
    {
        //s = s + terminate;
        Node * currentNode = root;
        bool added = false;
        for(int i = 0; i < s.length(); i++)
        {
            char c = s.at(i);
            NodeAddResult * result = addChildNode(currentNode, c);
            currentNode = result->node;
            added = result->added;
        }
    }

};


int main()
{
    ifstream file;
    string word, filecontent;
    filecontent = "WORD.LST"; //Note to grader: Included in my directory are different sets of input files that you can test. I ran each file to create the bar chart.
    file.open(filecontent.c_str());
    ofstream output;
    output.open("output.txt");
    Trie * k;
    auto start = std::chrono::high_resolution_clock::now();
    k->add("hello");
        while (file >> word)
    {
        k->add(word);
        output << word << endl;
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    output << microseconds << " micro-sec" << endl;
    return 0;
    file.close();
    output.close();
}
