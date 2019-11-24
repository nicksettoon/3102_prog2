#pragma once
#include "hsh_node.h"
#include <vector>
#include <math.h>
// #include <string> //included in node.h
// #include <iostream> //included in node.h
// #include <stdio.h> //included in node.h
// #include <memory> //included in node.h

struct HshEdge
{//struct holding the details of the relationship between two HshNodes in a HashTrie
    HshNode* parent;   //pointer to parent of relationship
    HshNode* child;    //pointer to child of relationship
    char childhead;         //head of child node
    HshEdge* nextedge; //pointer to next entry in the HshEdge's linked list.

    HshEdge(HshNode* parent_in, HshNode* child_in); //base constructor
    // HshEdge(HshEdge* predecessor_in, HshNode* parent_in, char head_in, HshNode* child_in); //full constructor unnecessary
    HshEdge* searchList(HshNode* target_parent, char target_childhead);    
    void print(); //prints HshEdge's information
};

class HashTrie
{
public:
    HashTrie(int size_in); //basic constructor
    const int size;   //size of the hash table
    std::vector<HshEdge> hshtable; //array of HashEntries
    HshNode* root;
    typedef int(*hashFunc)(int parent_addr, char child_head);

    bool insert(hashFunc hash_func, std::string word_in);  //insert function
    bool search(std::string word_in);  //search function, uses hash()
    
private:
    int hash1(int parent_addr, char child_head)
    {//hash function to find child with given child_head
        int b = 5;
        return ((parent_addr * child_head * (int)std::pow(b,31)) % 10007);
    }
};

// bool isPrime(int n)//Function to check if a number is Prime.
// {
//     int childhead=0;
//     for(int i=1;i<=n;i++)
//     {
//         if(n%i==0)
//             childhead++;
//     }
//     if(childhead==2)//Prime no.has 2 factors-1 and number itself.
//         return 1;
//     else
//         return 0;
// }

// int getNextPrime(int number_in)
// {
//     std::cout << "getting next prime number after "
//     int num=ob.nextInt();
//     int diff1=0,diff2=0;
//     int num1=0,num2=0;
//     for(int i=num;;i++)//No end limit as when prime will be found we will break the loop.
//     {
//         if(isPrime(i))
//         {
//             diff1=i-num;
//             num1=i;
//             break;
//         }
//     }
//     for(int i=num;;i--)//No end limit as when prime will be found we will break the loop.
//     {
//         if(isPrime(i))
//         {
//             diff2=num-i;
//             num2=i;
//             break;
//         }
//     }
//     if(diff1<diff2)//Nearest Prime number will have least difference from given number.
//         System.out.println("Nearest Prime Number from "+num+" is "+num1);
//     else if(diff2<diff1)
//         System.out.println("Nearest Prime Number from "+num+" is "+num2);
//         else//There can be more than 1 nearest prime like for 6 we have 5 and 7 as nearest prime.
//         System.out.println("Nearest Prime Number from "+num+" is "+num2+" and "+num1);
// };