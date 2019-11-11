#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

struct Node
{
    char letter;
    int frequency;
    Node * left;
    Node * right;
};

class Heap
{
    std::vector<int> heap;
    void swap(int &a, int &b);
    void buildHeap();

public:
    void insertKey(int elem);
    int extractMin();
    void heapify(int index);
    void showHeap();
    void decreaseKey(int index, int new_key);
};

void Heap::swap(int &a, int &b){
        int temp = a;
        a = b;
        b = temp;
}

void Heap::heapify(int index){

    int smallest = index;
    while(true){
        if(2*index+1 <= heap.size() && heap[2*index+1] < heap[smallest])
            smallest = 2*index+1;
        if (2*index+2 <= heap.size() && heap[2*index+2] < heap[smallest])
            smallest = 2*index+2;
        if(index != smallest){
            swap(heap[index], heap[smallest]);
            /*
             int temp = arr[index];
             arr[index] = arr[smallest];
             arr[smallest] = temp;
             */
            index=smallest;
        }
        else
            break;
    }
}

int Heap::extractMin(){
    int min = heap[0];
    int lastEle = heap.back();
    heap[0] = lastEle;
    heapify(0);
    return min;

}

void Heap::insertKey(int elem){

    heap.push_back(elem);
    long i = heap.size() - 1;

    while(i>0 && heap[i] < heap[(i-1)/2]){
        swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
}


void Heap::decreaseKey(int i, int new_key){
    heap[i] = new_key;
    while(i>0 && heap[i] < heap[(i-1)/2]){
        swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

void Heap::showHeap() {
    std::vector <int>::iterator pos = heap.begin();
    std::cout<<"Heap --> ";
    while (pos != heap.end()) {
        cout<< *pos <<" ";
        pos++;
    }
    std::cout<<std::endl;
}

class HuffmanCode
{
private:
    string data;
    string encoded;
    Heap * heap;

};

Node * newNode(char c, int frequency, Node * left, Node * right)
{
    Node * newNode;
    newNode = new Node;
    newNode->letter = c;
    newNode->frequency = frequency;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void frequencyCount(string text, Node *FrequencyTable[], int &Flength)
{
    int current = text[0];
    int frequency = 1;
    int textlength = text.size();
    for(int i = 1; i < textlength; i++)
    {
        if(text[i] == current)
        {
            frequency++;
        }
        else
        {
            FrequencyTable[Flength] = newNode(text[i-1], frequency, nullptr, nullptr);
            frequency = 1;
            current = text[i];
            Flength++;
        }
    }
    FrequencyTable[Flength] = newNode(text[textlength - 1], frequency, nullptr, nullptr);
    Flength++;
}




void heapify(Node *FrequencyTable[], int Flength, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < Flength && FrequencyTable[left]->frequency < FrequencyTable[smallest]->frequency)
    {
        smallest = left;
    }
    if(right < Flength && FrequencyTable[right]->frequency < FrequencyTable[smallest]->frequency)
    {
        smallest = right;
    }
    if(smallest != i)
    {
        Node * temp = FrequencyTable[i];
        FrequencyTable[i] = FrequencyTable[smallest];
        FrequencyTable[smallest] = temp;
        heapify(FrequencyTable, Flength, smallest);
    }
}

Node * extractMin(Node * FrequencyTable[], int &Flength)
{
    Node * temp;
    temp = FrequencyTable[0];
    FrequencyTable[0] = FrequencyTable[Flength - 1];
    FrequencyTable[Flength - 1] = temp;
    Flength--;
    heapify(FrequencyTable, Flength, 0);
    return temp;
}

void insertNode(Node * FrequencyTable[], Node * node, int &Flength)
{
    Flength++;
    FrequencyTable[Flength - 1] = node;
    int parent = ((Flength -1 ) - 1)/2;
    while(FrequencyTable[Flength - 1]->frequency < FrequencyTable[parent]->frequency)
    {
        Node * temp = FrequencyTable[Flength - 1];
        FrequencyTable[Flength - 1] = FrequencyTable[parent];
        FrequencyTable[parent] = temp;
        Flength = parent + 1;
    }
}

void createHeap(Node *FrequencyTable[], int Flength)
{
    for(int i = (Flength / 2) - 1; i >= 0; i--)
    {
        heapify(FrequencyTable, Flength, i);
    }
}

string getCode(Node *root,int A[], int top, ofstream &output, ifstream &input)
{
    string encodedtext;
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
            output << A[i];
            cout << A[i];
        }
        cout << endl;
        return encodedtext;
    }
}

void HuffmanTree(Node * FrequencyTable[], int &Flength)
{
    Node *left=extractMin(FrequencyTable,Flength);
    Node *right=extractMin(FrequencyTable,Flength);
    int sum = left->frequency + right->frequency;
    insertNode(FrequencyTable, newNode('\0',sum,left,right),Flength);
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
        if(int(text[i])<32 || (int(text[i])>32 && int(text[i])<48) || (int(text[i])>57 && int(text[i])<65) ||
        (int(text[i])>90 && int(text[i])<97) || int(text[i])>122)
            text[i]=' ';
    }
}

string decode(Node * root, string text)
{
    cout << "Entering decoding function" << endl;
    //cout << text << endl;
    Node * current = root;
    string decoded = "";
    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] == '0')
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
    return decoded + '\0';
}

string encode(string word)
{
    word = "he";
    cout << "Word: " << word << endl;
    cout << "encoding function here" << endl;
    word = "11010";
    cout << "Encoded: " << word << endl;
    return word;
}



int main()
{
    ofstream output;
    ifstream input;
    output.open("output.txt");
    string text = "hello";
    sanitize(text);
    cout << text << endl;
    //selectionSort(text, text.length());
    cout << text << endl;
    Node *FrequencyTable[1000];
    int Flength = 0; //FrequencyTableLength
    frequencyCount(text,FrequencyTable, Flength);

    createHeap(FrequencyTable, Flength);

    //HuffmanTree(FrequencyTable, Flength);
    while(Flength>1)
    {
        Node *left=extractMin(FrequencyTable, Flength);
        Node *right=extractMin(FrequencyTable,Flength);
        int sum = left->frequency + right->frequency;
        insertNode(FrequencyTable, newNode('\0',sum,left,right),Flength);
    }

    Node * root = extractMin(FrequencyTable, Flength);

    int A[500];
    cout << "Getting code now" << endl;
    string encodedtext = getCode(root, A, 0, output, input);
    cout << encodedtext << endl;
    output.close();
    input.open("output.txt");
    input >> encodedtext;
    cout << encodedtext;
    string decodedtext;
    cout << decodedtext.length() << endl;
    string teststring; //"he" in binary code
    string encoded = encode(teststring);
    decodedtext = decode(root, encoded);
    cout << decodedtext << endl;
    //h.extractMin();
    // h.decreaseKey(7, 1);

    //h.showHeap();
    input.close();
    return 0;
}
