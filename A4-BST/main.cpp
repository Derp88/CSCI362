#include <iostream>
#include <algorithm>

int kthSmallest;
int inputInts[15] = {6, 17, 20, 41, 45, 52, 57, 65, 71, 76, 79, 87, 92, 95, 99};
int printCounter = 0;
int functionCalls = 0;

struct node{
    int value = 29;
    node* leftChild = nullptr;
    node* rightChild = nullptr;
};
node rootNode;

//Function Prototypes
void insert(node* root, int newValue);
void buildBST(int leftIndex, int rightIndex);
void destroyTree(node* rootNode);
void findKthSmallest(node* rootNode);
void printBST(node* rootNode, std::string path);

void insert(node* root, int newValue){
    //For this we are assuming there is a predefined root.
    node *parentNode = nullptr;
    node* currentNode = root;
    
    node *newNode = new node;
    newNode->value = newValue;
    //Find the right parent node for our new value.
    while (currentNode != nullptr){
        parentNode = currentNode;
        if (newValue < currentNode->value){
            currentNode = currentNode->leftChild;
        }else{
            currentNode = currentNode->rightChild;
        }
    }
    if (newValue < parentNode->value){
        parentNode->leftChild = newNode;
    }else{
        parentNode->rightChild = newNode;
    }
}
void buildBST(int leftIndex, int rightIndex){
    int arrayLength = rightIndex - leftIndex;
    int median = inputInts[leftIndex + (arrayLength/2)];
    if (median != 65){
        insert(&rootNode, median); //Insert the middle node of our array
    }
    if(rightIndex != leftIndex){
        buildBST(leftIndex, leftIndex + (arrayLength/2)-1);
        buildBST(leftIndex + (arrayLength/2)+1,rightIndex);
    }
}
void destroyTree(node* rootNode){
    //No memory leaks today :). Hopefully
    if (rootNode != nullptr){
        destroyTree(rootNode->leftChild);
        destroyTree(rootNode->rightChild);
        delete rootNode;
    }
}
void findKthSmallest(node* rootNode){
    functionCalls++;
    if ((printCounter < kthSmallest) && (rootNode->leftChild != nullptr)){ 
        findKthSmallest(rootNode->leftChild); //Traverse left
    }
    //"Print" section
    if (printCounter < kthSmallest){
        //Only output if we are at the value we want
        if (printCounter == kthSmallest-1){
            std::cout << "Value: " << rootNode->value << "| " <<printCounter+1 << "th smallest element" << std::endl;
        }
        printCounter++;
    }
    if ((printCounter < kthSmallest) && (rootNode->rightChild != nullptr)){
        findKthSmallest(rootNode->rightChild); //Traverse right
    }
}
void printBST(node* rootNode, std::string path){
    //Traverse left
    if (rootNode->leftChild != nullptr){
        printBST(rootNode->leftChild, path + "->left");
    }
    std::cout << rootNode->value << " Path: " << path << std::endl;
    //Traverse right
    if (rootNode->rightChild != nullptr){
        printBST(rootNode->rightChild,  path + "->right");
    }
}

int main(){
    rootNode.value = inputInts[15/2];
    buildBST(0,14);
    std::cout << "Enter the kth smallest number you want to find: ";
    std::cin >> kthSmallest;

    printBST(&rootNode, "root");
    std::cout << "##############" << std::endl;

    findKthSmallest(&rootNode);

    std::cout << "findKthSmallest was called: " << functionCalls << "  times" << std::endl;

    destroyTree(rootNode.rightChild);
    destroyTree(rootNode.leftChild);
    return 0;
}
