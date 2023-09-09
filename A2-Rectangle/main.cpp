#include <iostream>
#include <vector>
#include <cmath>
//Function prototypes
void circleGenerator();
void printCircles();
bool inRange(int, int, int);
bool overlap(int, int, int);

class circleObject {
    public:
        int X;
        int Y;
        int radius;
};
std::vector<circleObject> listOfCircles;

void circleGenerator(){
    
    //Step 1, circle generation, generate a random circle center, and radius

    //Generate a random center, starting in the bottom left, adding up to 500. (Bounds 250 in each direction)
    int centerX = -250 + (rand() % 500);
    int centerY = -250 + (rand() % 500);
    //std::cout << "Center at X: " << centerX << " Y: " <<centerY << std::endl;
    //Generate a random radius. Max length 25
    int radius = rand() % 25;
    //std::cout << "Radius of: " << radius << std::endl;
    //Check to see if our circle would cross over an axis. If so, regen.
    if (inRange(centerY, centerY + radius, 0) || inRange(centerY, centerY - radius, 0) ){
        //std::cout << "Bad Gen!" << std::endl;
        circleGenerator(); //We had a bad generation, restart
    }else{
        //std::cout << "Good Gen!" << std::endl;
        //Now to check if generating this cirlce would overlap with another one.
        if (overlap(centerX, centerY, radius)){ //TODO: ADD CONDITION HERE! THIS ALSO NEEDS TO HAVE A WHILE
            circleGenerator(); //We had a bad generation, restart
        }else{
            //Check pass
            circleObject tempCircle;
            tempCircle.X = centerX;
            tempCircle.Y = centerY;
            tempCircle.radius = radius;
            listOfCircles.emplace_back(tempCircle);
        }
    }
}
bool overlap(int x, int y, int radius){
    bool overlapDetected = false;
    for (int i = 0; i < listOfCircles.size(); i++){
        float distance = std::sqrt( std::pow((x - listOfCircles[i].X), 2) + std::pow((y - listOfCircles[i].Y),2));
        int combinedRadius = radius + listOfCircles[i].radius;
        //Check to see if the combined radius is greater than the distance between them, if so, means overlap
        if (combinedRadius >= distance){
            std::cout << "Overlap Detected! Comb Radis: " << combinedRadius << " Distance: " << distance << std::endl;
            std::cout << "Circle Old: ";
            std::cout << " X: " << listOfCircles[i].X;
            std::cout << " Y: " <<  listOfCircles[i].Y;
            std::cout << " r: " <<  listOfCircles[i].radius;
            std::cout << std::endl;
            std::cout << "Circle New: ";
            std::cout << " X: " << x;
            std::cout << " Y: " <<  y;
            std::cout << " r: " <<  radius;
            std::cout << std::endl;
            overlapDetected = true;
        }
    }
    return overlapDetected;
}
void printCircles(){
    for (int i = 0; i < listOfCircles.size(); i++){
        std::cout << "Circle: " << i;
        std::cout << " X: " << listOfCircles[i].X;
        std::cout << " Y: " <<  listOfCircles[i].Y;
        std::cout << " r: " <<  listOfCircles[i].radius;
        std::cout << std::endl;
    }
}
bool inRange(int firstBound, int secondBound, int between){
    if (firstBound < secondBound){
        return (firstBound <= between && between <= secondBound);
    }else{
        return (secondBound <= between && between <= firstBound);
    }
}

int main(){
    int intNumOfRects;
    std::cout << "Enter the number of rectangles you want to generate." << std::endl;
    std::cin >> intNumOfRects;
    for (int i = 0; i < intNumOfRects; i++){
        circleGenerator();
    }
    //printCircles();
    return 0;
}
