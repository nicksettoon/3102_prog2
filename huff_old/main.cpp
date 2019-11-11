#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

#include "huff.h"
node::Node *a = new Node("c", 10);

node::Node array = 
void frequencyCount(string text, char letter[], int frequency[], int numchar);
void getCode(Node *root,int A[], int top, ofstream &output, ifstream &input);
void selectionSort(string & text, unsigned int length);
void sanitize(string &text);
string selectionSort(string text, int length);
void decode(Node * root, string encodedtext[], int textlength);
string encode(string word, char letter[], string encodedtext[]);
void arrangeletters(char letter[]);


int main()
{
    //open txt and get contents
    ofstream output;
    ifstream input;
    input.open("txt.txt");
    string rawtext;
    input >> rawtext;
    cout << rawtext << endl;
    input.close();

    //sanitize txt string
    sanitize(rawtext);

    //sort letters into string sortedtext 
    int size = rawtext.length();
    string sortedtext = selectionSort(rawtext, size);
    int numchar = 0;
    char letter[size];
    int freq[size];
    int counter = 0;

    for(int i = 0; i < size; i++)
    {
        if(sortedtext[i] != sortedtext[i+1])
        {
            letter[counter] = sortedtext[i];
            numchar++;
            counter++;
        }
    }

    //get freqency of each letter
    frequencyCount(sortedtext, letter, freq, numchar);


    //make huffman tree 
    Node * root = HuffmanTree(letter, freq, numchar);

    //encode text?
    input.open("encoded.txt");
    string code;
    string encodedtext[numchar];
    int i = 0;
    while(input >> code)
    {
        encodedtext[i] = code;
        cout << encodedtext[i] << endl;

        i++;
    }
    input.close();
    output.open("encoded.txt");
    output.close();

    //?
    arrangeletters(letter);
    output.open("characters.txt");
    output.close();
    input.open("textfile.txt");
    input >> rawtext;
    input.close();
    string encoded = encode(rawtext, letter, encodedtext);
    int textlength = encoded.length();
    decode(root, &encoded, textlength);

    return 0;
}

void frequencyCount(string text, char letter[], int frequency[], int numchar)
{
    cout << "Entering frequency function" << endl;
    char current = letter[0];
    int freq = 0;
    for(int k = 0; k < numchar; k++)
    {
        freq = 0;
        current = letter[k];
        for(int i = 0; i < text.length(); i++)
        {
            if(text[i] == current)
            {
                freq++;
            }
        }
        frequency[k] = freq;
    }
  //  FrequencyTable[Flength] = newNode(text[textlength - 1], frequency, nullptr, nullptr);
    //size++;
}


void getCode(Node *root,int A[], int top, ofstream &output, ifstream &input)
{
    int i = 0;
    int encodedtext[600];
    int encodearray[600];
    int sizeofarray = 0;
    if(root->left)
    {
        A[top] = 0;
        getCode(root->left, A, top + 1, output, input);
    }

    if(root->right)
    {
        A[top] = 1;
        getCode(root->right, A, top+1, output, input);
    }

    if(!(root->left) && !(root->right)) //LeafNode
    {
        cout << "Character: " << root->letter << "  ";
        cout << "Code: ";
        for(int i=0;i<top;i++)
        {
            cout << A[i];
        }
        //int encodearray[i] = A[i];
        cout << endl;
    }
}

void selectionSort(string & text, unsigned int length)
{
    char tempChar= ' ';
    for(unsigned int i=0;i<length;i++)
    {
        char minVal=text[i];
        for(unsigned int j=i+1;j<length;j++)
        {
            if(text[j]<minVal)
            {
                //swap values
                tempChar=text[j];
                text[j]=minVal;
                text[i]=tempChar;
                minVal=tempChar;
            }
        }
    }
}


void sanitize(string &text)
{
     for(unsigned int i=0;i<text.length();i++)
    {
        //if char<32, 32<char<48, 57<char<65, 90<char<97, or char>122 replace it with white space
        if(int(text[i])<32 || (int(text[i])>32 && int(text[i])<48) || (int(text[i])>57 && int(text[i])<65) ||
        (int(text[i])>90 && int(text[i])<97) || int(text[i])>122)
            text[i]=' ';
    }
}

string selectionSort(string text, int length)
{
    char tempChar= ' ';
    for(unsigned int i=0;i<length;i++)
    {
        char minVal=text[i];
        for(unsigned int j=i+1;j<length;j++)
        {
            if(text[j] < minVal)
            {
                //swap values
                tempChar=text[j];
                text[j]=minVal;
                text[i]=tempChar;
                minVal=tempChar;
            }
        }
    }
    cout << text << " sorted" << endl;
    return text;
}

void decode(Node * root, string encodedtext[], int textlength)
{
    cout << "Entering decoding function" << endl;
    //cout << text << endl;
    Node * current = root;
    string decoded;
    char chartext[textlength + 1];
    encodedtext->copy(chartext, textlength + 1);
    chartext[textlength] = '\0';
    for(int i = 0; i < textlength; i++)
    {
        if(chartext[i] == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        if(current->left == nullptr && current->right == nullptr)
        {
            decoded = decoded + current->letter;
            current = root;
        }
    }
    cout << decoded << " decoded" << endl;
}

string encode(string word, char letter[], string encodedtext[])
{
    ofstream output;
    output.open("encodedtext.txt");
    string encoded;
    bool found = false;
    cout << word << ": raw text" << endl;
    for(int i = 0; i < word.length(); i++)
    {
        found = false;
        int k = 0;
        while(!found)
        {
            if(word[i] == letter[k])
            {
                encoded.append(encodedtext[k]);
                found = true;
            }
            else
            {
                k++;
            }
        }
    }
    cout << encoded << " encoded word" << endl;
    output << encoded << endl;
    return encoded;
}

void arrangeletters(char letter[])
{
    ifstream input;
    int i = 0;
    char character;
    input.open("characters.txt");
    while(input >> character)
    {
        letter[i] = character;
        i++;
    }
    input.close();
}


