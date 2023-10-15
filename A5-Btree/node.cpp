#include "node.h"

//Constructors
Node::Node(){}

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