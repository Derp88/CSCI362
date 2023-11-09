#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include "TimeInterval.h"

std::vector<std::string> hashTable[26];

//Function prototypes
int hashWord(std::string);
void insertIntoTable(std::string);
void loadDict(std::string);

bool searchTable(std::string);
void searchIndex2Letters(std::string);


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
bool searchTable(std::string inputWord){ //AKA Case 1 check
    int hashTableIndex = hashWord(inputWord);
    if (hashTable[hashTableIndex].end() != std::find(hashTable[hashTableIndex].begin(), hashTable[hashTableIndex].end(), inputWord)){
        std::cout << "TRUE | Found: " << inputWord << std::endl;
        return true;
    }else{
        std::cout << "FALSE | Could not find: " << inputWord << std::endl;
        return false;
    }
}
void searchIndex2Letters(std::string inputWord){
    TimeInterval time;
    time.start();
    int hashTableIndex = hashWord(inputWord);
    for (int i = 0; i < hashTable[hashTableIndex].size(); i++){
        if(hashTable[hashTableIndex].size() > 1){ //Make sure the word we are checking has more than 1 letter
            if (hashTable[hashTableIndex].at(i) != inputWord){ //Make sure we aren't checking the same word
                if(hashTable[hashTableIndex].at(i)[1] == inputWord[1]){
                    time.stop();
                    std::cout << "Found a match in : " << time.GetInterval() << " Microseconds: "<< hashTable[hashTableIndex].at(i) <<std::endl;
                }
            }
        }
    }
}

int main(int argc, char *argv[]){
    std::string inputFileName(argv[1]);
    loadDict(inputFileName);

    std::string inputWord;
    std::cout << "Please enter a word" << std::endl;
    std::cin >> inputWord;
    if (searchTable(inputWord)){ //Search the table for the word
        searchIndex2Letters(inputWord);
    }

    return 0;
}