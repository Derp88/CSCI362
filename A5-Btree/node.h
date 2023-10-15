#ifndef NODE_H_EXISTS
#define NODE_H_EXISTS

#include <vector>
#include <set>
class Node{
    public:
        std::multiset<int> keys;
        std::vector<Node*> listOfChildren;
        Node* parentNode;
        Node();
        bool isLeaf();
        bool isRoot();
};

#endif