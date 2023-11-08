#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <cctype>
#include "TimeInterval.h"

std::list<std::string> hashTable[26];

//Function prototypes
int hashWord(std::string);
void insertIntoTable(std::string);
void loadDict(std::string);

bool searchTable(std::string);


int hashWord(std::string inputWord){ //Input should be lowercase
    return int(inputWord[0])-97;
}

void insertIntoTable(std::string inputWord){
    int hashTableIndex = hashWord(inputWord);
    hashTable[hashTableIndex].emplace_back(inputWord);
}
void loadDict(std::string filename){
    std::ifstream inputFile;
    inputFile.open(filename);
    std::string entry;
    
    while (std::getline(inputFile, entry)){
        entry[0] = tolower(entry[0]); //Convert the first char to lowercase
        entry.pop_back(); //Remove trailing whitespace character. :(
        insertIntoTable(entry);
    }
}
bool searchTable(std::string inputWord){
    int hashTableIndex = hashWord(inputWord);
    if (hashTable[hashTableIndex].end() != std::find(hashTable[hashTableIndex].begin(), hashTable[hashTableIndex].end(), inputWord)){
        std::cout << "Found: " << inputWord << std::endl;
        return true;
    }else{
        std::cout << "Could not find: " << inputWord << std::endl;
        return false;
    }
}


int main(int argc, char *argv[]){
    std::string inputFileName(argv[1]);
    loadDict(inputFileName);
    //TimeInterval testInt;
    //testInt.start();
    //std::cout << "Please enter a word" << std::endl;
    
    //testInt.stop();
    std::string test = "world";
    searchTable(test);
    //std::cout << "Execution Time: " << testInt.GetInterval() << " Micro-Seconds" << std::endl;

    return 0;
}