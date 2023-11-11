#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include "TimeInterval.h"

std::vector<std::string> hashTable[26];
std::string altWord;

//Function prototypes
int hashWord(std::string);
void insertIntoTable(std::string);
void loadDict(std::string);

bool searchTable(std::string);
void searchIndex2Letters(std::string);
bool searchTableSimilar(std::string);


int hashWord(std::string inputWord){ //Input should be lowercase
    return int(inputWord[0])-97; //97 is the ASCII value for lowercase a
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
        return true;
    }else{
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
bool searchTableSimilar(std::string inputWord){
    int inputLength = inputWord.size();
    int hashTableIndex = hashWord(inputWord);
    std::vector<std::string> alternatives;
    std::vector<std::string> alternativesRightSize;
    alternatives = hashTable[hashTableIndex];
    for(int i = 0; i < alternatives.size(); i++){
        int alternativeLength = alternatives[i].size();
        if(std::abs(alternativeLength - inputLength) < 2){ //Add to new list of valid size options
            alternativesRightSize.emplace_back(alternatives[i]);
        }
    }
    //If there are alts with the right size, continue, else, return false
    switch(alternativesRightSize.size()){
        case 0: //No matches
            return false;
        case 1: //1 word match
            altWord = alternativesRightSize[0];
            return true;
        default: //More than one word matches
            std::vector<int> numOfSameLetters; //Is a vector that matches alternativesRightSize and gives each entry a score on how many letters are the same.
            for (int i = 0; i < alternativesRightSize.size(); i++){ //For every possible word
                numOfSameLetters.emplace_back(0); //Initalize the score values to 0
                for (int j = 0; j < alternativesRightSize[i].size(); j++){//For evey letter in the alt word
                    //If the letter in the alt word is present in the input word, increase numOfSameLetters by one
                    if(inputWord.find(alternativesRightSize[i].at(j)) != std::string::npos){
                        //std::cout << "For word: " << alternativesRightSize[i] <<" Found the letter: " << alternativesRightSize[i].at(j) << " inside of " << inputWord << std::endl;
                        numOfSameLetters[i]++; //Increase score
                    }
                }
            }
            //Find the highest scoring index. The alt word at the same index is the true suggestion.
            int largestIndex = 0;
            for (int i = 0; i < numOfSameLetters.size(); i++){
                if(numOfSameLetters[i] > numOfSameLetters[largestIndex]){
                    largestIndex = i;
                }
            }
            altWord = alternativesRightSize[largestIndex];

            return true;
    }
    
}

int main(int argc, char *argv[]){
    std::string inputFileName(argv[1]);
    loadDict(inputFileName);

    std::string inputWord;
    std::string choice;
    std::cout << "Please enter a word (lowercase letters only)" << std::endl;
    std::cin >> inputWord;
    if (searchTable(inputWord)){ //Search the table for the word
        std::cout << "TRUE | Found: " << inputWord << std::endl;
        searchIndex2Letters(inputWord); //Case 1
    }else{
        if (searchTableSimilar(inputWord)){
            std::cout << "Did you mean " << altWord << "?  (yes or no)"<< std::endl;
            std::cin >> choice;
            if(choice == "yes"){
                std::cout << "TRUE | Found: " << altWord << std::endl;
                searchIndex2Letters(altWord);
            }else{
                std:: cout << "False | Invalid alternative word" << std::endl;
            }
        }else{
            std::cout  << "False | Could not find: " << inputWord << std::endl;
        }
    }
    
    return 0;
}