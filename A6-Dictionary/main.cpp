#include <iostream>
#include "TimeInterval.h"

struct nodeLL{
    std::string word;
    nodeLL* child = nullptr;
};
nodeLL hashTable[26];

//Function prototypes
int hashWord(std::string);
nodeLL* getLinkedListEnd(nodeLL*);
void insertIntoTable(std::string);


int hashWord(std::string inputWord){ //Input should be lowercase
    return int(inputWord[0])-97;
}
nodeLL* getLinkedListEnd(nodeLL* startNode){
    if(startNode->child != nullptr){
        getLinkedListEnd(startNode->child);
    }
    return startNode;
}

void insertIntoTable(std::string inputWord){
    int hashTableIndex = hashWord(inputWord);
    //If the node at the index is null set it, if not append instead
    if(hashTable[hashTableIndex].word.empty()){
        std::cout << "This hash index is empty." << std::endl;
        hashTable[hashTableIndex].word = inputWord;
    }else{
        //Get end of linked list
        //getLinkedListEnd(hashTable[hashTableIndex]);
    }
}


int main(){
    TimeInterval testInt;
    testInt.start();
    //std::cout << "Please enter a word" << std::endl;

    insertIntoTable("potato");
    insertIntoTable("potato");
    
    testInt.stop();
    std::cout << "Execution Time: " << testInt.GetInterval() << " Micro-Seconds" << std::endl;

    return 0;
}