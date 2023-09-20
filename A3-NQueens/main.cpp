#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

bool sorted;
int filledRows;
struct queen{
    int rowY;
    int columnX;  
};


void queenMain(int);
bool isConflict(std::stack<queen>, int);
std::stack<queen> addQueen(int, int, std::stack<queen>);
bool canShiftRight(std::stack<queen>, int);

void outputStack(std::stack<queen>);

bool isConflict(std::stack<queen> checkStack, int numOfQueen){ //Check if the top of the queen stack.
    std::vector<int> occupiedRowY;
    std::vector<int> occupiedColumnX;
    std::vector<int> occupiedDiagonalPos;
    std::vector<int> occupiedDiagonalNeg;
    bool detectedConflict = false;
    while(!checkStack.empty() && !detectedConflict){
        int rowY = checkStack.top().rowY;
        int columnX = checkStack.top().columnX;
        int positiveDiagonal = rowY - columnX;
        int negativeDiagonal = std::abs(rowY-(numOfQueen+1)) - columnX;
        //Check to see if the value we have overlaps anywhere.
        if (std::find(occupiedRowY.begin(), occupiedRowY.end(), rowY) != occupiedRowY.end()){
            detectedConflict = true;
            //std::cout << "Row(y) conflict detected" << std::endl;
        }
        if (std::find(occupiedColumnX.begin(), occupiedColumnX.end(), columnX) != occupiedColumnX.end()){
            detectedConflict = true;
            //std::cout << "Column(x) conflict detected" << std::endl;
        }
        if (std::find(occupiedDiagonalPos.begin(), occupiedDiagonalPos.end(), positiveDiagonal) != occupiedDiagonalPos.end()){
            detectedConflict = true;
            //std::cout << "Positive Diagonal conflict detected" << std::endl;
        }
        if (std::find(occupiedDiagonalNeg.begin(), occupiedDiagonalNeg.end(), negativeDiagonal) != occupiedDiagonalNeg.end()){
            detectedConflict = true;
            //std::cout << "Negative Diagonal conflict detected" << std::endl;
        } 
        occupiedRowY.emplace_back(rowY);
        occupiedColumnX.emplace_back(columnX);
        occupiedDiagonalPos.emplace_back(positiveDiagonal);
        occupiedDiagonalNeg.emplace_back(negativeDiagonal);
        checkStack.pop();
    }
    return detectedConflict;
}
std::stack<queen> addQueen(int columnX, int rowY, std::stack<queen> queenStackToAdd){
    queen newQueen;
    newQueen.columnX = columnX;
    newQueen.rowY = rowY;
    queenStackToAdd.push(newQueen);
    return queenStackToAdd;
}
bool canShiftRight(std::stack<queen> queenStackToCheck, int numOfQueen){
    return (queenStackToCheck.top().columnX < numOfQueen-1); //Return true if we can shift right.
}

void queenMain(int numOfQueen){
    std::stack<queen> queenStack;
    sorted = false;
    filledRows = 0;
    queenStack = addQueen(0,0,queenStack);

    while(!sorted){ //While all the queens have not been sorted
        outputStack(queenStack);
        if (!isConflict(queenStack, numOfQueen)){ //Check if there is no conflict
            filledRows = filledRows + 1;
            if (filledRows == numOfQueen){ //Check to see if all the queens have been places
                sorted = true;
            } else{ //Not all the queens have been placed, time to put down.
                int previousRow = queenStack.top().rowY;
                queenStack = addQueen(0,previousRow+1,queenStack);
            }
        }else if (isConflict && (queenStack.top().columnX < numOfQueen-1)){ //There is an active conflict and e have room to shift the column right
            std::cout << "Shifting right, because we can." << std::endl;
            int currentColumn = queenStack.top().columnX;
            int currentRow = queenStack.top().rowY;
            queenStack.pop(); //Get rid of the old conflicting queen.
            queenStack = addQueen(currentColumn+1,currentRow,queenStack); //Create a new queen one right of the old one.
        }
        else if (isConflict && !(queenStack.top().columnX < numOfQueen-1)){ //Conflict and we cannot shift right.
            while (!(queenStack.top().columnX < numOfQueen-1)){
                queenStack.pop();
                filledRows = filledRows - 1;
            }
            int currentColumn = queenStack.top().columnX;
            int currentRow = queenStack.top().rowY;
            queenStack.pop(); //Get rid of the old conflicting queen.
            queenStack = addQueen(currentColumn+1,currentRow,queenStack); //Create a new queen one right of the old one.
            /*
            queenStack.pop();
            filledRows = filledRows - 1;
            if (queenStack.top().columnX < numOfQueen-1){
                std::cout << "@Moving an old queen!" << std::endl;
                    
                int currentColumn = queenStack.top().columnX;
                int currentRow = queenStack.top().rowY;
                queenStack.pop(); //Get rid of the old conflicting queen.
                queenStack = addQueen(currentColumn+1,currentRow,queenStack); //Create a new queen one right of the old one.
            }*/
        }
    }
    outputStack(queenStack);
}
void outputStack(std::stack<queen> outputStack){
    int counter = 0;
    std::cout << "####Start Stack report####" << std::endl;
    while(!outputStack.empty()){
        std::cout << "Q: " << counter << " Column (X): " << outputStack.top().columnX <<  " Row (Y): " << outputStack.top().rowY << std::endl;
        outputStack.pop();
        counter++;
    }
    std::cout << "####Finished Stack report####" << std::endl;
}

int main(){
    int numOfQueens;
    std::cout << "Input an integer greater than 3: " << std::endl;
    std::cin >> numOfQueens;
    queenMain(numOfQueens);

    return 0;
}