#pragma once
#include "hsh_node.h"
// #include <string> //included in node.h
// #include <iostream> //included in node.h
// #include <stdio.h> //included in node.h
// #include <memory> //included in node.h

struct HashEntry
{
    Node* parent;   //pointer to parent of relationship
    Node* child;    //pointer to child of relationship
    char c;         //head of child node
    HashEntry* nextentry; //pointer to next entry in the HashEntry's linked list.

    HashEntry(Node* parent_in);
    HashEntry(Node* parent_in, char head_in, Node* child_in);
    bool searchList();    
};

class HashTrie
{
    const int size;   //size of the hash table
    HashEntry* hshtable[]; //array of HashEntries
    Node* root;
    
    typedef int(*hash_func)(Node* parent_in, char child_head);
    hash1(Node* parent_id, char child_head); //hash function to find child with given child_head
    
    HashTrie(int size_in); //basic constructor
    bool insert(std::string word_in);  //insert function
    bool search(std::string word_in);  //search function, uses hash()
}

// bool isPrime(int n)//Function to check if a number is Prime.
// {
//     int c=0;
//     for(int i=1;i<=n;i++)
//     {
//         if(n%i==0)
//             c++;
//     }
//     if(c==2)//Prime no.has 2 factors-1 and number itself.
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
// }