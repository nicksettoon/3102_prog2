#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct Node
{
    char letter; //first character
    string label; //word
    bool isWord; //if this node is a word or not
    Node * firstChild; //child of parent
    Node * rightSibling; //siblings of first child
};

class LinkedList
{
private:
    Node * root;
    Node * newNode(char, string, bool, Node *, Node *);
    string findSubstring(int, int, string);
public:
    LinkedList(); //constructor
    void insert(string);
    void search(string);
};

Node* LinkedList::newNode(char letter, string label, bool isWord, Node * firstChild, Node *rightSibling)
{
    Node *newNode;
    newNode = new Node;
    newNode->letter = letter;
    newNode->label = label;
    newNode->firstChild = firstChild;
    newNode->rightSibling = rightSibling;
    newNode->isWord = isWord;
    return newNode;
}

string LinkedList::findSubstring(int i, int j, string word)
{
    string substring;
    if(i == j)
        substring = word[i];
    else
        substring = word.substr(i, j);

    return substring;
}

LinkedList::LinkedList() //constructor
{
    root = newNode('$', "", false, nullptr, nullptr);
}

void LinkedList::insert(string word)
{
    cout << "Inserting " << word << " into trie" << endl;
    if(root->firstChild == nullptr) //trie empty, insert first word
    {
        cout << "Trie empty" << endl;
        Node * node = newNode(word[0], word, false, nullptr, nullptr);
        root->firstChild = node;
        return;
    }
    else //trie not empty, find where to insert
    {
        cout << "Trie not empty" << endl;
        int i = 0;
        bool done = false;
        Node *rootchild = root->firstChild;
        Node *prevNode = nullptr;
        Node *parent = root;
        while(!done)
        {
            while(rootchild != nullptr && rootchild->label[i] < word[i]) //check char
            {
                prevNode = rootchild;
                rootchild = rootchild->rightSibling;
            }
            if(rootchild && rootchild->label[i] == word[i]) //if matches char, continue through label
            {
                bool stop = false; //bool stop to see when to stop
                i++;
                while(!stop && i < rootchild->label.length() && i < word.length())
                {
                    if(rootchild->label[i] == word[i]) //continue until word[i] does not match
                    {
                        i++;
                    }
                    else //word[i] doesn't match label[i] anymore, stop
                    {
                        stop = true;
                    }
                }
                if(stop)
                {
                    string firstChildLabel;
                    string rightSiblingLabel;
                    string newLabel = findSubstring(0, i - 1, rootchild->label); //find substring
                    bool add = false; //bool add
                    if(rootchild->label[i] > word[i])
                    {
                        firstChildLabel = findSubstring(i, word.length() - 1, word);
                        rightSiblingLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
                        add = true;
                    }
                    else
                    {
                        firstChildLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
                        rightSiblingLabel = findSubstring(i, word.length() - 1, word);
                    }
                    rootchild->isWord = false;
                    rootchild->label = newLabel; //new label for split case
                    Node *rightSib = newNode(rightSiblingLabel[0], rightSiblingLabel, true, nullptr, nullptr);
                    Node *leftChild = newNode(firstChildLabel[0], firstChildLabel, true, nullptr, rightSib);
                    if(rootchild->firstChild == nullptr)
                    {
                        rootchild->firstChild = leftChild;
                        done = true;
                    }
                    else
                    {
                        if(add)
                        {
                            rightSib->firstChild = rootchild->firstChild;
                        }
                        else
                        {
                            leftChild->firstChild = rootchild->firstChild;
                        }
                        rootchild->firstChild = leftChild;
                    }
                    done = true;
                }
                else //find prefix
                {

                    if(rootchild->label.length() < word.length()) //rootchild->label is prefix of word
                    {
                       if(rootchild->firstChild != nullptr) //go to next level
                       {
                           parent = rootchild;
                           prevNode = nullptr;
                           rootchild = rootchild->firstChild;
                           word = findSubstring(i, word.length() - 1, word);
                           i = 0;
                       }
                       else //make new node to be child for rootchild
                       {
                           string childLabel = findSubstring(i, word.length() - 1, word);
                           Node *newChild = newNode(childLabel[0], childLabel, true, nullptr, nullptr);
                           rootchild->firstChild = newChild;
                           done = true;
                       }
                    }
                    else if(rootchild->label.length() == word.length()) //same length
                    {
                         rootchild->isWord = true; //set to true
                         done = true;
                    }
                    else
                    {
                        string newChildLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
                        rootchild->label = findSubstring(0, rootchild->label.length() - 1, rootchild->label);
                        rootchild->isWord = true; //set to true
                        Node * node = newNode(newChildLabel[0], newChildLabel, true, rootchild->firstChild, nullptr);
                        rootchild->firstChild = node;
                        done = true;
                    }
                }
            }
            else
            {
                if(prevNode == nullptr) //new level, make firstChild of level
                {
                    Node* node = newNode(word[i], word, true, nullptr, rootchild);
                    parent->firstChild = node;
                    done = true;
                }
                else //make to be rightSibling
                {
                    Node * node = newNode(word[0], word, true, nullptr, rootchild);
                    prevNode->rightSibling = node;
                    done = true;
                }

            }
        }
        cout << "Inserted." << endl;
    }
}

void LinkedList::search(string word)
{
    Node *rootchild = root->firstChild;
    if(rootchild == nullptr) //empty trie
    {
        return;
    }
    else //not empty trie, start searcg
    {
        int i = 0;
            while(rootchild != nullptr && rootchild->letter < word[i])
            {
                rootchild = rootchild->rightSibling; //continue through level
            }
            if(rootchild == nullptr) //reached end, not found
            {
                cout << word << " is not found " << endl;
                return;
            }
            else //continue search
            {
                i++;
                bool found = false;
                while(!found && i < rootchild->label.length())
                {
                    if(word[i] == rootchild->label[i]) //still matching, continue
                    {
                        i++;
                    }
                    else
                    {
                         rootchild = rootchild->firstChild; //next level
                         found = true;
                    }
                }
            }
        cout << word << " found." << endl;
    }
}




int main()
{
    LinkedList * trie;
    trie = new LinkedList;
    ifstream input;
    string word;
    input.open("words.txt");
    while (input >> word)
    {
        trie->insert(word);
    }
    input.close();
    input.open("words.txt");
    while(input >> word)
    {
        trie->search(word);
    }
    input.close();
    return 0;
}
