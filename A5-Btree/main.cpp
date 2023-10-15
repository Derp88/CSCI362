#include <iostream>
//#include <vector>
//#include <set>
#include "node.h"

//Vars
int numOfInts;
std::vector<int> listOfRandomInts;
//Node
//struct node{
//    std::multiset<int> keys;
//    std::vector<node*> listOfChildren;
//};

//Function prototypes
void generateRandomInts();

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



int main(){
    std::cout << "Input an integer greater than or equal to 400: ";
    std::cin >> numOfInts;
    generateRandomInts();
    return 0;
}