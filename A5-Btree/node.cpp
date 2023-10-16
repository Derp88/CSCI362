#include "node.h"
#include <algorithm>

//Constructors
Node::Node(){
    Node::parentNode = nullptr;
}

//Methods
bool Node::isLeaf(){
    if(Node::listOfChildren.size() == 0){
        return true;
    }else{
        return false;
    }
}
bool Node::isRoot(){
    if(Node::parentNode == nullptr){
        return true;
    }else{
        return false;
    }
}
void Node::sortKeys(){
    std::sort(Node::keys.begin(), Node::keys.end());
}