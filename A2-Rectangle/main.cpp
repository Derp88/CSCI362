#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
//Function prototypes
void circleGenerator();
void printCircles();
bool inRange(int, int, int);
bool overlap(int, int, int);
void outputCircleCSV();

//PLEASE NOTE
//THE DRAWING LIBRARY SOMETIMES RENDERS OVERLAPS
//THEY ARE NOT ACTUALLY OVERLAPPING. I CHECKED.

class circleObject {
    public:
        int X;
        int Y;
        int radius;
};
std::vector<circleObject> listOfCircles;

void circleGenerator(){
    //Generate a random center, starting in the bottom left, adding up to 500. (Bounds 250 in each direction)
    int centerX = -250 + (rand() % 500);
    int centerY = -250 + (rand() % 500);
    //Generate a random radius. Max length 25
    int radius = (rand() % 24) + 1; //Plus 1, so we don't get radius of 0
    //Check to see if our circle would cross over an axis. If so, regen.
    if (inRange(centerY, centerY + radius, 0) || inRange(centerY, centerY - radius, 0) ){
        circleGenerator(); //We had a bad generation, restart
    }else{
        //Now to check if generating this cirlce would overlap with another one.
        if (overlap(centerX, centerY, radius)){
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
        double distance = std::sqrt( std::pow((x - listOfCircles[i].X), 2) + std::pow((y - listOfCircles[i].Y),2));
        int combinedRadius = radius + listOfCircles[i].radius;
        //Check to see if the combined radius is greater than the distance between them, if so, means overlap
        if (combinedRadius >= distance){
            overlapDetected = true;
            std::cout << "Overlap Detected! Comb Radis: " << combinedRadius << " Distance: " << distance << std::endl;
            std::cout << "Circle Old: " << " X: " << listOfCircles[i].X << " Y: " <<  listOfCircles[i].Y << " r: " <<  listOfCircles[i].radius << std::endl;;
            std::cout << "Circle New: " << " X: " << x << " Y: " <<  y << " r: " <<  radius << std::endl;
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
void outputCircleCSV(){
    std::ofstream outputFile;
    outputFile.open("output.csv");
    for (int i = 0; i < listOfCircles.size(); i++){
        outputFile << listOfCircles[i].X << "," << listOfCircles[i].Y << "," << listOfCircles[i].radius << "\n";
    }
    outputFile.close();
}
bool inRange(int firstBound, int secondBound, int between){
    if (firstBound < secondBound){
        return (firstBound <= between && between <= secondBound);
    }else{
        return (secondBound <= between && between <= firstBound);
    }
}

int main(){
    srand(time(NULL));
    int intNumOfRects;
    std::cout << "Enter the number of rectangles you want to generate." << std::endl;
    std::cin >> intNumOfRects;
    for (int i = 0; i < intNumOfRects; i++){
        circleGenerator();
    }
    //printCircles();
    outputCircleCSV();
    system("python3 csvViewer.py");
    return 0;
}
