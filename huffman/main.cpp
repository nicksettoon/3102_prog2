#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <ctype.h>
using namespace std;

//Huffman node
struct HuffmanNode
{
	char letter; //character
	int freq; //character's frequency
	HuffmanNode *left; //left
	HuffmanNode *right; //right
};

//getHuffManNode creates a new HuffmanNode
HuffmanNode* getHuffmanNode(char letter, int freq, HuffmanNode* left, HuffmanNode* right)
{
	HuffmanNode* node = new HuffmanNode();
	node->letter = letter;
	node->freq = freq;
	node->left = left;
	node->right = right;
	return node;
}

//compare compares frequency of left node and right node
struct compare
{
	bool operator()(HuffmanNode* left, HuffmanNode* right)
	{
		return left->freq > right->freq;
	}
};

//storeCode stores huffman codes into map(letter and huffman code)
void storeCode(HuffmanNode* root, string text, unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
    {
        return;
    }

	if (root->left == nullptr && root->right == nullptr) {
		huffmanCode[root->letter] = text; //reached end leaf; store
	}

	storeCode(root->left, text + "0", huffmanCode);
	storeCode(root->right, text + "1", huffmanCode);
}

//decode takes encoded and decodes it.
void decode(HuffmanNode* root, int &index, string text, ofstream &output)
{
	if (root == nullptr) //nothing
    {
		return;
	}
	if (root->left == nullptr && root->right == nullptr)
	{
		output << root->letter; //reached end leaf; take letter
		return;
	}
	index++; //not leaf, so check to see if we should go left or right in the tree
	if (text[index] == '0') //0, so go to the left
    {
        decode(root->left, index, text, output);
    }
	else //1, so go to the right
    {
        decode(root->right, index, text, output);
    }
}

//HuffmanTree find frequency, stores into a map that holds
//letter and frequency, creates huffman tree using priority queue, stores the code into a map that holds letter and huffman code
void HuffmanTree(string text)
{
	unordered_map<char, int> freq; //map that stores letter and frequency
    unordered_map<char, string> huffmanCode; //map that stores letter and huffman code
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> priorityqueue; //priority queue
    cout << "Finding frequency.." << endl;
    for(int i = 0; i < text.length(); i++)
	{
		freq[text[i]]++; //everytime it sees this letter, it will increment frequency to store in the frequency map
	}
    for (auto pair: freq) {
        priorityqueue.push(getHuffmanNode(pair.first, pair.second, nullptr, nullptr)); //create node for character, push to priority queue
	}
	cout << "Creating Huffman tree.." << endl;
	while (priorityqueue.size() != 1)
	{
		HuffmanNode *left = priorityqueue.top(); //pop and top the two nodes with lowest frequency until queue is empty
		priorityqueue.pop();
		HuffmanNode *right = priorityqueue.top();
		priorityqueue.pop();
		int sum = left->freq + right->freq; //take sum of the two that just got popped.
		priorityqueue.push(getHuffmanNode('$', sum, left, right)); //combine to be one node that has the letters as children; then add to queue
	}
	HuffmanNode* root = priorityqueue.top();
	storeCode(root, "", huffmanCode); //store code into map
	cout << "Frequency: " << endl;
    for (auto pair: freq) {
		cout << pair.first << ": " << pair.second << endl; //outputs the map; letter and its frequency
	}
	cout << "Huffman code: " << endl;
	for (auto pair: huffmanCode) {
		cout << pair.first << ": " << pair.second << endl; //outputs the map; letter and its huffman code
	}
	cout << "Length of huffman code: " << endl;
    for (auto pair: huffmanCode) {
    cout << pair.first << ": " << pair.second.length() << endl; //outputs the map; letter and length of the huffman code
	}
    cout << "Encoding.." << endl;
	string encoded = "";
	for (char ch: text) {
		encoded = encoded + huffmanCode[ch]; //find character in huffmancode map; take its huffman code and store in string
	}

    ofstream output;
	output.open("encodedtext.txt");
	output << encoded; //store encoded string into output file
	output.close();
	cout << "Encoding complete" << endl;

	int current = -1; //current index position
	cout << "Decoding.." << endl;
	output.open("decodedtext.txt");
	while (current < (int)encoded.size() - 1) {
		decode(root, current, encoded, output); //decode encoded string, storedecoded string into output file
	}
	output.close();
	cout << "Decoding complete" << endl;
}

//sanitize takes text and replaces everything that isn't an alphabetical letter into a white-space character
void sanitize(string &text)
{
    cout << "Sanitizing.." << endl;
     for(long int i = 0;i < text.length(); i++)
    {
        if(isalpha(text[i]) == false)
        {
            text[i] = '\0'; //is not alphabetical,replace with white-space character
        }
    }
    cout << "Sanitizing complete" << endl;
}









int main()
{
	ifstream input { "textfile.txt" }; //input in text file
    string text { istreambuf_iterator<char>(input), istreambuf_iterator<char>() }; //takes whole text as a string
    input >> text;
    input.close();
    sanitize(text); //sanitize text
	HuffmanTree(text); //take sanitized text, create tree, encode, decode
	return 0;
}
