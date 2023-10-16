#ifndef NODE_H_EXISTS
#define NODE_H_EXISTS

#include <vector>
class Node{
    public:
        std::vector<int> keys; 
        std::vector<Node*> listOfChildren;
        Node* parentNode;
        Node();
        bool isLeaf();
        bool isRoot();
        void sortKeys();
        void sortChildren();
        void printKeys();
};

#endif