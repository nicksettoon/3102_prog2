#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char data;
    int freq;
    Node *left;
    Node *right;
};
Node *createNode(char,int,Node *,Node *);
void sanitize(string &);
void selectionSort(string &,unsigned int);
void freqCount(string, Node *[],int &);
void beginHeap(Node *[], int);
void heapify(Node *[], int, int);
Node *extractMin(Node *[],int &);
void insertNode(Node *[],Node *,int &);
void heapifyBtmUp(Node *[],int);
void getCode(Node *,int [],int);

int main()
{
    string text="aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff";
    //Sanitize string
    sanitize(text);
    
    //First sort the text using a simple selection sort
    string sortedText=text;
    selectionSort(sortedText,sortedText.length());
    
    //Count frequencies and put into array 
    Node *A[500]; 
    int Alength=0;
    freqCount(sortedText,A,Alength);

    //Heapify A
    beginHeap(A,Alength);
    
    //Build the Huffman Tree
    while(Alength>1)
    {
        Node *left=extractMin(A,Alength);
        Node *right=extractMin(A,Alength);
        int sum=left->freq+right->freq;
        insertNode(A,createNode('\0',sum,left,right),Alength);
    }
    Node *root=extractMin(A,Alength);
    
    //Get the Huffman Code for each character
    int codeA[500];
    getCode(root,codeA,0);
     
  return 0;
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

void freqCount(string sortedText, Node *A[],int &Alength)
{
    int current=sortedText[0];
    int currentFreq=1;
    for(unsigned int i=1;i<sortedText.size();i++)
    {
        if(sortedText[i]==current)
            currentFreq++;
        else
        {
            A[Alength]=createNode(sortedText[i-1],currentFreq,NULL,NULL);
            currentFreq=1;
            current=sortedText[i];
            Alength++;
        }   
    }
    //insert last one
    A[Alength]=createNode(sortedText[sortedText.size()-1],currentFreq,NULL,NULL);
    Alength++;
}

Node *createNode(char c,int f,Node *l,Node *r)
{
    Node * createdNode;
    createdNode= new Node;
    createdNode->data=c;
    createdNode->freq=f;
    createdNode->left=l;
    createdNode->right=r;
    return createdNode;
}

void beginHeap(Node *A[], int Alength)
{
    for (int i = Alength / 2 - 1; i >= 0; i--) 
        heapify(A, Alength, i); 
}

void heapify(Node *A[], int Alength, int i)
{
    int smallest=i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < Alength && A[l]->freq < A[smallest]->freq)
        smallest=l;
    if (r < Alength && A[r]->freq < A[smallest]->freq)
        smallest = r;
        
    if (smallest != i)
    {
        Node *temp=A[i];
        A[i]=A[smallest];
        A[smallest]=temp;
        heapify(A,Alength,smallest);
    }
}

Node *extractMin(Node *A[],int &Alength)
{
    Node *temp;
    temp=A[0];
    A[0]=A[Alength-1];
    A[Alength-1]=temp;
    Alength--;
    heapify(A,Alength,0);
    return temp;
}

void insertNode(Node *A[], Node *newNode,int &Alength)
{
    Alength++;
    A[Alength-1]=newNode;
    heapifyBtmUp(A,Alength-1);
}

void heapifyBtmUp(Node *A[],int i)
{
        int parent=(i-1)/2;
        if(A[i]->freq < A[parent]->freq)
        {
            Node *temp=A[i];
            A[i]=A[parent];
            A[parent]=temp;
            heapifyBtmUp(A,parent);
        }
}

void getCode(Node *root,int A[],int top)
{
    if(root->left)
    {
        A[top]=0;
        getCode(root->left,A,top+1);
    }
    
    if(root->right)
    {
        A[top]=1;
        getCode(root->right,A,top+1);
    }
    
    if(!(root->left) && !(root->right)) //LeafNode
    {
        cout << "Character: " << root->data << "  ";
        cout << "Code: ";
        for(int i=0;i<top;i++)
            cout << A[i];
        cout << endl;
    }
}