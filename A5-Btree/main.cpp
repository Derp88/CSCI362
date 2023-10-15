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
    if (searchNode->isLeaf()){
        std::cout << "Node found with keys: " << std::endl;
        for (int i = 0; i < searchNode->keys.size(); i++){
            std::cout << searchNode->keys.at(i) << ", ";
        }
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
void printTree(Node* rootNode, std::string path){
    
}

int main(){
    /*std::cout << "Input an integer greater than or equal to 400: ";
    std::cin >> numOfInts;
    generateRandomInts();
    for (int i = 0; i < listOfRandomInts.size(); i++){
        insertInt(i);
    }*/
    rootNode->keys.emplace_back(17);

    Node* leftChild = new Node;
    leftChild->keys.emplace_back(3);
    leftChild->keys.emplace_back(8);

    Node* leftGrandchild1 = new Node;
    leftGrandchild1->keys.emplace_back(1);
    leftGrandchild1->keys.emplace_back(2);
    Node* leftGrandchild2 = new Node;
    leftGrandchild2->keys.emplace_back(6);
    leftGrandchild2->keys.emplace_back(7);
    Node* leftGrandchild3 = new Node;
    leftGrandchild3->keys.emplace_back(12);
    leftGrandchild3->keys.emplace_back(14);
    leftGrandchild3->keys.emplace_back(16);
    leftChild->listOfChildren.emplace_back(leftGrandchild1);
    leftChild->listOfChildren.emplace_back(leftGrandchild2);
    leftChild->listOfChildren.emplace_back(leftGrandchild3);

    Node* rightChild = new Node;
    rightChild->keys.emplace_back(28);
    rightChild->keys.emplace_back(48);

    Node* rightGrandchild1 = new Node;
    rightGrandchild1->keys.emplace_back(25);
    rightGrandchild1->keys.emplace_back(26);
    Node* rightGrandchild2 = new Node;
    rightGrandchild2->keys.emplace_back(29);
    rightGrandchild2->keys.emplace_back(45);
    Node* rightGrandchild3 = new Node;
    rightGrandchild3->keys.emplace_back(52);
    rightGrandchild3->keys.emplace_back(53);
    rightGrandchild3->keys.emplace_back(55);
    rightGrandchild3->keys.emplace_back(68);

    rightChild->listOfChildren.emplace_back(rightGrandchild1);
    rightChild->listOfChildren.emplace_back(rightGrandchild2);
    rightChild->listOfChildren.emplace_back(rightGrandchild3);

    rootNode->listOfChildren.emplace_back(leftChild);
    rootNode->listOfChildren.emplace_back(rightChild);

    findLeafForInt(rootNode, 17);

    return 0;
}