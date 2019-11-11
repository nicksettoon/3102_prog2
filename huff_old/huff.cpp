#include "huff.h" //includes huff, heap and node

huff::HuffmanTree() //default constructor
    : array(0), parent(0), root(nullptr){}

huff::HuffmanTree(char letter[], int frequency[], int size) //custom constructor
{
    Node *left;
    Node *right;
    Node *parent;
    Heap *heap = combineHeap(letter, frequency, size);

    while(heap->size != 1)
    {
        left = extractMin(heap);
        right = extractMin(heap);
        parent = newNode('$', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        insertHeap(heap, parent);
    }
    return extractMin(heap);
}

void printHuffman(Node * root, int array[], int parent)
{
    ofstream output;
    output.open("characters.txt", std::ios_base::app);
    if(root->left)
    {
        array[parent] = 0;
        printHuffman(root->left, array, parent + 1);
    }
    if(root->right)
    {
        array[parent] = 1;
        printHuffman(root->right, array, parent + 1);
    }
    if(!(root->left) && !(root->right))
    {
        cout << root->letter << ": ";
        output << root->letter << endl;
        printArray(array, parent);
    }
    output.close();
}

Node * HuffmanTree(char letter[], int frequency[], int size)
{
    Node * root = buildHuffman(letter, frequency, size);
    int array[500];
    int parent = 0;
    printHuffman(root, array, parent);
    return root;
}

void HuffmanTree(Node * FrequencyTable[], int &Flength)
{
    Node *left=extractMin(FrequencyTable,Flength);
    Node *right=extractMin(FrequencyTable,Flength);
    int sum = left->frequency + right->frequency;
  //  insertNode(FrequencyTable, newNode('\0',sum,left,right),Flength);
}

