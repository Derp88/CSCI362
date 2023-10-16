#include "node.h"
#include <algorithm>
#include <iostream>

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
void Node::printKeys(){
    std::cout << "N:{ ";
    for (int i = 0; i < Node::keys.size(); i++){
        std::cout << Node::keys.at(i) << ", ";
    }
    std::cout << "}";
}