#include <iostream>

//Function Prototypes
void SelectionSort();
void printList();

int listOfInts[10];

void SelectionSort(){
    int smallestFoundIntIndex;
    for (int currentIndex = 0; currentIndex < 9; currentIndex++){
        smallestFoundIntIndex = currentIndex; //Our current number is the smallest number as we have not compared any yet.
        for (int comparisonIndex = (currentIndex + 1); comparisonIndex < 10; comparisonIndex++){
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
    for (int i = 0; i < 10; i++){
        std::cout << listOfInts[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    int inputInt;
    for (int i = 0; i < 10; i++){
        std::cout << "Entering number " << i+1 << " out of 10" << std::endl;
        std::cin >> inputInt;
        listOfInts[i] = inputInt;
    }
    SelectionSort();
    printList();

    return 0;
}