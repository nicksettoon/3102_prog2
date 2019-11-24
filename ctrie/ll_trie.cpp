// #include "headers/ll_trie.h"

// using str = std::string;

// //not needed nemore
// // LLNode* LinkedList::newNode(char letter, str label, bool isWord, LLNode * firstChild, LLNode *rightSibling)
// // {
// //     LLNode *newNode;
// //     newNode = new LLNode;
// //     newNode->letter = letter;
// //     newNode->label = label;
// //     newNode->firstChild = firstChild;
// //     newNode->rightSibling = rightSibling;
// //     newNode->isWord = isWord;
// //     return newNode;
// // }

// // void LinkedList::getNodes(LinkedList::nodeVisitFunc visit_func, LLNode* start_node, str prefix_context, HashTrie* target_trie)
// // {//traverses the trie in preorder and prints each complete word.
// //     if(start_node == nullptr){return;}

// //     str prefix = prefix_context + start_node->label;

// //     if(start_node->isWord)
// //         visit_func(prefix);
// //         // target_trie->insert(prefix);
// //         // std::cout << prefix << std::endl;

// //     LLNode* nextnode = start_node->firstChild;
// //     while(nextnode != nullptr)
// //     {
// //         getNodes(nextnode, prefix);
// //         nextnode = nextnode->rightSibling;
// //     }
// // }

// str LinkedList::findSubstring(int i, int j, str word)
// {
//     str substring;
//     if(i == j)
//         substring = word[i];
//     else
//         substring = word.substr(i, j);

//     return substring;
// }

// LinkedList::LinkedList() //constructor
// {
//     root = new LLNode('$', "", false, nullptr, nullptr);
// }

// void LinkedList::insert(str word)
// {
//     std::cout << "Inserting " << word << " into trie" << std::endl;

//     if(root->firstChild == nullptr) //trie empty, insert first word
//     {
//         std::cout << "Trie empty" << std::endl;
//         LLNode * node = new LLNode(word[0], word, false, nullptr, nullptr);
//         root->firstChild = node;
//         return;
//     }
//     else //trie not empty, find where to insert
//     {
//         std::cout << "Trie not empty" << std::endl;
//         int i = 0;
//         bool done = false;
//         LLNode *rootchild = root->firstChild;
//         LLNode *prevNode = nullptr;
//         LLNode *parent = root;
//         while(!done)
//         {
//             while(rootchild != nullptr && rootchild->label[i] < word[i]) //check char
//             {
//                 prevNode = rootchild;
//                 rootchild = rootchild->rightSibling;
//             }
//             if(rootchild && rootchild->label[i] == word[i]) //if matches char, continue through label
//             {
//                 bool stop = false; //bool stop to see when to stop
//                 i++;
//                 while(!stop && i < rootchild->label.length() && i < word.length())
//                 {
//                     if(rootchild->label[i] == word[i]) //continue until word[i] does not match
//                     {
//                         i++;
//                     }
//                     else //word[i] doesn't match label[i] anymore, stop
//                     {
//                         stop = true;
//                     }
//                 }
//                 if(stop)
//                 {
//                     str firstChildLabel;
//                     str rightSiblingLabel;
//                     str newLabel = findSubstring(0, i - 1, rootchild->label); //find substring
//                     bool add = false; //bool add
//                     if(rootchild->label[i] > word[i])
//                     {
//                         firstChildLabel = findSubstring(i, word.length() - 1, word);
//                         rightSiblingLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
//                         add = true;
//                     }
//                     else
//                     {
//                         firstChildLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
//                         rightSiblingLabel = findSubstring(i, word.length() - 1, word);
//                     }
//                     rootchild->isWord = false;
//                     rootchild->label = newLabel; //new label for split case
//                     LLNode *rightSib = new LLNode(rightSiblingLabel[0], rightSiblingLabel, true, nullptr, nullptr);
//                     LLNode *leftChild = new LLNode(firstChildLabel[0], firstChildLabel, true, nullptr, rightSib);
//                     if(rootchild->firstChild == nullptr)
//                     {
//                         rootchild->firstChild = leftChild;
//                         done = true;
//                     }
//                     else
//                     {
//                         if(add)
//                         {
//                             rightSib->firstChild = rootchild->firstChild;
//                         }
//                         else
//                         {
//                             leftChild->firstChild = rootchild->firstChild;
//                         }
//                         rootchild->firstChild = leftChild;
//                     }
//                     done = true;
//                 }
//                 else //find prefix
//                 {

//                     if(rootchild->label.length() < word.length()) //rootchild->label is prefix of word
//                     {
//                        if(rootchild->firstChild != nullptr) //go to next level
//                        {
//                            parent = rootchild;
//                            prevNode = nullptr;
//                            rootchild = rootchild->firstChild;
//                            word = findSubstring(i, word.length() - 1, word);
//                            i = 0;
//                        }
//                        else //make new node to be child for rootchild
//                        {
//                            str childLabel = findSubstring(i, word.length() - 1, word);
//                            LLNode *newChild = new LLNode(childLabel[0], childLabel, true, nullptr, nullptr);
//                            rootchild->firstChild = newChild;
//                            done = true;
//                        }
//                     }
//                     else if(rootchild->label.length() == word.length()) //same length
//                     {
//                          rootchild->isWord = true; //set to true
//                          done = true;
//                     }
//                     else
//                     {
//                         str newChildLabel = findSubstring(i, rootchild->label.length() - 1, rootchild->label);
//                         rootchild->label = findSubstring(0, rootchild->label.length() - 1, rootchild->label);
//                         rootchild->isWord = true; //set to true
//                         LLNode * node = new LLNode(newChildLabel[0], newChildLabel, true, rootchild->firstChild, nullptr);
//                         rootchild->firstChild = node;
//                         done = true;
//                     }
//                 }
//             }
//             else
//             {
//                 if(prevNode == nullptr) //new level, make firstChild of level
//                 {
//                     LLNode* node = new LLNode(word[i], word, true, nullptr, rootchild);
//                     parent->firstChild = node;
//                     done = true;
//                 }
//                 else //make to be rightSibling
//                 {
//                     LLNode * node = new LLNode(word[0], word, true, nullptr, rootchild);
//                     prevNode->rightSibling = node;
//                     done = true;
//                 }

//             }
//         }
//         std::cout << "Inserted." << std::endl;
//     }
// }

// void LinkedList::search(str word)
// {
//     LLNode *rootchild = root->firstChild;
//     if(rootchild == nullptr) //empty trie
//     {
//         return;
//     }
//     else //not empty trie, start searcg
//     {
//         int i = 0;
//             while(rootchild != nullptr && rootchild->letter < word[i])
//             {
//                 rootchild = rootchild->rightSibling; //continue through level
//             }
//             if(rootchild == nullptr) //reached end, not found
//             {
//                 std::cout << word << " is not found " << std::endl;
//                 return;
//             }
//             else //continue search
//             {
//                 i++;
//                 bool found = false;
//                 while(!found && i < rootchild->label.length())
//                 {
//                     if(word[i] == rootchild->label[i]) //still matching, continue
//                     {
//                         i++;
//                     }
//                     else
//                     {
//                          rootchild = rootchild->firstChild; //next level
//                          found = true;
//                     }
//                 }
//             }
//         std::cout << word << " found." << std::endl;
//     }
// }