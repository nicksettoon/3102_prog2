#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct Node
{
    char letter;
    int frequency;
    Node * left;
    Node * right;
};

struct Heap
{
    int size;
    int capacity;
    Node ** array;
    Heap(int capacity)
    {
        size = 0;
        capacity = capacity;
        *array = new Node[capacity];
    }
};


Node * newNode(char c, int frequency)
{
    Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->letter = c;
    temp->frequency = frequency;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}


/*
Node * newHeap(int capacity)
{
    Node * temp;
    //struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp = new Node();
    temp->size = 0;
    temp->capacity = capacity;
    //temp->array = (struct Node**)malloc(Heap->capacity * sizeof(struct Node*));
    return temp;
}
*/


Heap* newHeap(int capacity)
{
    Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct Node**)malloc(heap->capacity * sizeof(struct Node*));
    return heap;
}

void heapify(Heap * heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if(left < heap->size && heap->array[left]->frequency < heap->array[smallest]->frequency)
    {
        smallest = left;
    }
    if(right < heap->size && heap->array[right]->frequency < heap->array[smallest]->frequency)
    {
        smallest = right;
    }
    if(smallest != index)
    {
        swap(heap->array[smallest], heap->array[index]);
        heapify(heap, smallest);
    }
}

Node * extractMin(Heap * heap)
{
    Node * temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size = heap->size - 1;
    heapify(heap, 0);
    return temp;
}

void insertHeap(Heap * heap, Node * node)
{
    heap->size = heap->size + 1;
    int i = heap->size - 1;
    while(i < heap->array[(i - 1) / 2]->frequency && node->frequency < heap->array[(i - 1) / 2]->frequency)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i-1)/2;
    }
    heap->array[i] = node;
}

void buildHeap(Heap * heap)
{
    int n = heap->size - 1;
    for(int i = (n - 1)/2; i >= 0; i--)
    {
        heapify(heap, i);
    }
}


void printArray(int array[], int n)
{
    ofstream output;
    ifstream input;
    output.open("encoded.txt", std::ios_base::app);
    int i;
    for (i = 0; i < n; i++)
    {
        cout << array[i];
        output << array[i];
    }
    cout << endl;
    output << endl;
    output.close();
}

Heap * combineHeap(char letter[], int frequency[], int size)
{
    Heap * heap = newHeap(size);
    for(int i = 0; i < size; i++)
    {
        heap->array[i] = newNode(letter[i], frequency[i]);
    }
    heap->size = size;
    buildHeap(heap);
    return heap;
}

Node * buildHuffman(char letter[], int frequency[], int size)
{
    Node * left;
    Node * right;
    Node * top;
    Heap * heap = combineHeap(letter, frequency, size);

    while(heap->size != 1)
    {
        left = extractMin(heap);
        right = extractMin(heap);
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertHeap(heap, top);
    }
    return extractMin(heap);
}

void printHuffman(Node * root, int array[], int top)
{
    ofstream output;
    output.open("characters.txt", std::ios_base::app);
    if(root->left)
    {
        array[top] = 0;
        printHuffman(root->left, array, top + 1);
    }
    if(root->right)
    {
        array[top] = 1;
        printHuffman(root->right, array, top + 1);
    }
    if(!(root->left) && !(root->right))
    {
        cout << root->letter << ": ";
        output << root->letter << endl;
        printArray(array, top);
    }
    output.close();
}

Node * HuffmanTree(char letter[], int frequency[], int size)
{
    Node * root = buildHuffman(letter, frequency, size);
    int array[500];
    int top = 0;
    printHuffman(root, array, top);
    return root;
}

void frequencyCount(string text, char letter[], int frequency[], int numchar)
{
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



void sanitize(string &text)
{
    cout << "Entering sanitize function" << endl;
     for(int i = 0;i < text.length(); i++)
    {
        if(isalpha(text[i]))
        {
            text[i] = text[i];
        }
        else
        {
            text[i] = '\0';
        }
    }
}

string selectionSort(string text, int length)
{
    cout << "Entering sorting function" << endl;
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
    cout << text << endl;
    return text;
}

void decode(Node * root, string encodedtext[], int textlength)
{
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

string encode(string word, char letter[], string encodedtext[], int numchar)
{
    cout << "Entering encoding function" << endl;
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
            if(word[i] == letter[k]) //letter found
            {
                encoded.append(encodedtext[k]);
                found = true;
            }
            else //not found
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







void merge(string text, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    char L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = text[l + i];
    for (j = 0; j < n2; j++)
        R[j] = text[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            text[k] = L[i];
            i++;
        }
        else
        {
            text[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1)
    {
        text[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2)
    {
        text[k] = R[j];
        j++;
        k++;
    }
    cout << text << "from merging" << endl;
}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
void r_mergeSort(string text, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        r_mergeSort(text, l, m);
        r_mergeSort(text, m+1, r);

        merge(text, l, m, r);
    }
}

int min(int x, int y) { return (x<y)? x :y; }

/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(string text, int n)
{
    int curr_size;  // For current size of subarrays to be merged
    // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
    // to be merged

    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
    {
        // Pick starting point of different subarrays of current size
        for (left_start=0; left_start<n-1; left_start += 2*curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting
            // point of right
            int mid = min(left_start + curr_size - 1, n-1);

            int right_end = min(left_start + 2*curr_size - 1, n-1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(text, left_start, mid, right_end);
        }
    }
}


/*


int partition (string text, int low, int high)
{
    int pivot = text[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (text[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&text[i], &text[j]);
        }
    }
    swap(&text[i + 1], &text[high]);
    return (i + 1);
}

void quickSort(string text, int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(text, l, h);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}




void sortString(string &str)
{
   sort(str.begin(), str.end());
   cout << str;
}



*/

int main()
{
    ofstream output;
    /*
    ifstream input;
    input.open("textfile.txt");
    */
    ifstream input { "englishshorter.txt" };
    string rawtext { istreambuf_iterator<char>(input), istreambuf_iterator<char>() };
    input >> rawtext;
    input.close();
    sanitize(rawtext);
    int size = rawtext.length();
    string sortedtext = selectionSort(rawtext, size);
    /*
    string sortedtext;
    sortString(rawtext);
    sortedtext = rawtext;
    */
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
    frequencyCount(sortedtext, letter, freq, numchar);
    Node * root = HuffmanTree(letter, freq, numchar);
    input.open("encoded.txt");
    string code;
    string encodedtext[numchar];
    int i = 0;
    while(input >> code) //make array of encodedtext
    {
        encodedtext[i] = code;
        i++;
    }
    input.close();
    output.open("encoded.txt");
    output.close();
    arrangeletters(letter);
    output.open("characters.txt");
    output.close();
    string encoded = encode(rawtext, letter, encodedtext, numchar);
    int textlength = encoded.length();
    decode(root, &encoded, textlength);

    return 0;
}
