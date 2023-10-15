#include <iostream>
//#include <vector>
//#include <set>
#include "node.h"

//Vars
int numOfInts;
std::vector<int> listOfRandomInts;
Node* rootNode = new Node;

//Function prototypes
void generateRandomInts();
void insertInt(int);
Node* findLeafForInt(Node*, int);
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
        //Delete the value we added to our random list from all list
        listOfAllPossibleInts.erase(listOfAllPossibleInts.begin() + randomIndex); 
    }
}

void insertInt(int newNumber){
    //
}

Node* findLeafForInt(Node* searchNode, int searchNumber){
    searchNode->sortKeys(); //Make sure our keys are sorted
    //Find the index of what key we are less than
    if(!searchNode->isLeaf()){
        bool foundSubtree = false;
        //Check and see if our search number is greater than all the keys
        if (searchNumber > searchNode->keys.back()){
            foundSubtree = true;
            findLeafForInt(searchNumber, searchNode->listOfChildren.at(searchNode->keys.size()));
        }else{
            for (int i = 0; i < searchNode->keys.size(); i++){ //For every key
                if(!foundSubtree){ //If we haven't found the correct subtree yet
                    if(searchNumber < searchNode->keys.at(i)){ //Check and see if our search number is less than the current key
                        foundSubtree = true;
                        findLeafForInt(searchNumber, searchNode->listOfChildren.at(i)); //If so, check within the corresponding subtree
                    }
                }
            }
        }
    }else{
        std::cout << "Node found with keys: " << std::endl;
        for (int i = 0; i < searchNode->keys.size(); i++){
            std::cout << searchNode->keys.at(i) << ", ";
        }
        std::cout << std::endl;
        return searchNode;
    }
}
void printTree(Node* rootNode, std::string path){
    
}

int main(){
    std::cout << "Input an integer greater than or equal to 400: ";
    std::cin >> numOfInts;
    generateRandomInts();
    for (int i = 0; i < listOfRandomInts.size(); i++){
        insertInt(i);
    }
    rootNode->keys.emplace_back(17);
    Node* leftChild = new Node;
    leftChild->keys.emplace_back(3);
    leftChild->keys.emplace_back(8);
    Node* rightChild = new Node;
    rightChild->keys.emplace_back(24);
    rightChild->keys.emplace_back(48);
    rootNode->listOfChildren.emplace_back(leftChild);
    rootNode->listOfChildren.emplace_back(rightChild);

    findLeafForInt(18, rootNode);

    return 0;
}