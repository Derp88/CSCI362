#include <iostream>
//#include <vector>
//#include <set>
#include "node.h"

//Vars
int numOfInts;
std::vector<int> listOfRandomInts;
Node* rootNode = new Node;
const int treeOrderInt = 5;

//Function prototypes
void generateRandomInts();
void insertInt(int);
Node* findLeafForInt(Node*, int);
void splitNode(Node*);
void printTree(Node*, std::string);

void generateRandomInts(){
    int upperBound = numOfInts * 3;
    //Generate a list of all possible numbers
    std::vector<int> listOfAllPossibleInts;
    for (int i = 0; i < upperBound+1; i++){
        listOfAllPossibleInts.emplace_back(i);
    }
    //Pop random indexes from the list of all ints
    srand (time(NULL));
    for (int i = 0; i < numOfInts; i++){
        int randomIndex = rand() % listOfAllPossibleInts.size();
        int randomInt = listOfAllPossibleInts.at(randomIndex);
        listOfRandomInts.emplace_back(randomInt);
        std::cout << randomInt << ", ";
        //Delete the value we added to our random list from all list
        listOfAllPossibleInts.erase(listOfAllPossibleInts.begin() + randomIndex); 
    }
    std::cout << std::endl;
}

void insertInt(int newNumber){
    std::cout << "#########" << std::endl;
    rootNode->printKeys();
    for (int i=0; i < rootNode->listOfChildren.size(); i++){
        std::cout << i << ": ";
        rootNode->listOfChildren.at(i)->printKeys();
    }
    //Find the corresponding leaf for the new number
    Node* newLeaf = findLeafForInt(rootNode, newNumber);
    newLeaf->keys.emplace_back(newNumber);
    newLeaf->sortKeys();
    if (newLeaf->keys.size() > treeOrderInt-1){ //We have inserted too many keys into a leaf
        splitNode(newLeaf);
    }
}
void splitNode(Node* nodeToSplit){
    nodeToSplit->sortKeys();
    int medianIndex = (nodeToSplit->keys.size())/2;
    int median = nodeToSplit->keys.at(medianIndex);
    Node* paretNodeOfSplit;
    if (!nodeToSplit->isRoot()){ //If we are not root(aka we have a parent), promote the median to it
        paretNodeOfSplit = nodeToSplit->parentNode;
    }else{//We do not have a parent, so we must create a new parent.
        std::cout << "### Making a new parent node." << std::endl;
        paretNodeOfSplit = new Node;
        rootNode = paretNodeOfSplit; //This new parent is also the new root
    }
    //Add the new median to the parent, sort the parent
    paretNodeOfSplit->keys.emplace_back(median); 
    paretNodeOfSplit->sortKeys();
    //Now to split the child in two
    Node* newChild = new Node;
    for (int i = medianIndex + 1; i < nodeToSplit->keys.size(); i++){ //Add everything past the median to our new child node
        newChild->keys.emplace_back(nodeToSplit->keys.at(i));
    }
    //Add our new child to the parent
    if (nodeToSplit->isRoot()){ //Only add the old node if we had to make a new root
        paretNodeOfSplit->listOfChildren.emplace_back(nodeToSplit); 
    }
    newChild->parentNode = paretNodeOfSplit;
    nodeToSplit->parentNode = paretNodeOfSplit;
    paretNodeOfSplit->listOfChildren.emplace_back(newChild); 
    //Delete the median and everything greater/right of it from the old node
    for (int i = 0; i < medianIndex+1; i++){
        nodeToSplit->keys.pop_back();
    }
}

Node* findLeafForInt(Node* searchNode, int searchNumber){
    searchNode->sortKeys(); //Make sure our keys are sorted
    if (searchNode->isLeaf()){
        return searchNode;
    }else{
        int subTreeCounter = 0;
        for (int i = 0; i < searchNode->keys.size(); i++){
            if (searchNumber > searchNode->keys.at(subTreeCounter)){
                subTreeCounter++;
            }
        }
        return findLeafForInt(searchNode->listOfChildren.at(subTreeCounter), searchNumber);
    }
}
void printTree(Node* rootNode){
    std::cout << "ROOT NODE: ";
    rootNode->printKeys();
    for (int i=0; i < rootNode->listOfChildren.size(); i++){
        std::cout << i << ": ";
        rootNode->listOfChildren.at(i)->printKeys();
    }
}

int main(){
    std::cout << "Input an integer greater than or equal to 400: ";
    std::cin >> numOfInts;
    generateRandomInts();
    for (int i = 0; i < listOfRandomInts.size(); i++){
        insertInt(listOfRandomInts.at(i));
    }
    printTree(rootNode);

    return 0;
}