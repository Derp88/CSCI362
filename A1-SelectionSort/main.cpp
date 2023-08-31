#include <iostream>
#include <vector>

//Function Prototypes
void SelectionSort();
void printList();

std::vector<int> listOfInts;

void SelectionSort(){
    int smallestFoundIntIndex;
    for (int currentIndex = 0; currentIndex < listOfInts.size()-1; currentIndex++){
        smallestFoundIntIndex = currentIndex; //Our current number is the smallest number as we have not compared any yet.
        for (int comparisonIndex = (currentIndex + 1); comparisonIndex < listOfInts.size(); comparisonIndex++){
            if (listOfInts[comparisonIndex] < listOfInts[smallestFoundIntIndex]){ //If the number we are comparing against is smaller then the smallest number we have found(cont).
                smallestFoundIntIndex = comparisonIndex; //Set our newest smallest number to it.
            }
        }
        //Swaps values at our current index and the index of the smallest found number non-sorted number
        int tempCurrentVal = listOfInts[currentIndex];
        listOfInts[currentIndex] = listOfInts[smallestFoundIntIndex];
        listOfInts[smallestFoundIntIndex] = tempCurrentVal;
    }
}

void printList(){
    std::cout << "Your list: ";
    for (int i = 0; i < listOfInts.size(); i++){
        std::cout << listOfInts[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    int inputInt;
    while (inputInt != 0){
        std::cout << "Entering a number, enter 0 to stop." << std::endl;
        std::cin >> inputInt;
        if (inputInt != 0){
            listOfInts.emplace_back(inputInt);
        }
    }
    SelectionSort();
    printList();

    return 0;
}