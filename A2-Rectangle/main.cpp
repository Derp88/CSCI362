#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
class shapeObject {
    public:
        int X;
        int Y;
        int radius;
        double xPoints[4] = {0.0,0.0,0.0,0.0};
        double yPoints[4] = {0.0,0.0,0.0,0.0};
};
//Function prototypes
void circleGenerator();
void rectangleGenerator(int);
void setRandomPoint(int, int);
void printCircles();
bool inRange(int, int, int);
bool overlap(int, int, int);
void outputShapeCSV();

//PLEASE NOTE
//THE DRAWING LIBRARY SOMETIMES RENDERS OVERLAPS
//THEY ARE NOT ACTUALLY OVERLAPPING. I CHECKED.

std::vector<shapeObject> listOfShapes;

void circleGenerator(){
    //Generate a random center, starting in the bottom left, adding up to 500. (Bounds 250 in each direction)
    int centerX = -250 + (rand() % 500);
    int centerY = -250 + (rand() % 500);
    int radius = (rand() % 22) + 3; //Generate a random radius. Max length 25, plus 3, so we don't get radius of 0
    //Check to see if our circle would cross over an axis. If so, regen.
    if (inRange(centerY, centerY + radius, 0) || inRange(centerY, centerY - radius, 0) ){
        circleGenerator(); //We had a bad generation, restart
    }else{
        if (overlap(centerX, centerY, radius)){ //Now to check if generating this cirlce would overlap with another one.
            circleGenerator(); //We had a bad generation, restart
        }else{//Check pass
            shapeObject tempCircle;
            tempCircle.X = centerX;
            tempCircle.Y = centerY;
            tempCircle.radius = radius;
            listOfShapes.emplace_back(tempCircle);
        }
    }
}
bool overlap(int x, int y, int radius){
    bool overlapDetected = false;
    for (int i = 0; i < listOfShapes.size(); i++){
        double distance = std::sqrt( std::pow((x - listOfShapes[i].X), 2) + std::pow((y - listOfShapes[i].Y),2));
        int combinedRadius = radius + listOfShapes[i].radius;
        //Check to see if the combined radius is greater than the distance between them, if so, means overlap
        if (combinedRadius >= distance){
            overlapDetected = true;
            std::cout << "Overlap Detected! Comb Radis: " << combinedRadius << " Distance: " << distance << std::endl;
            std::cout << "Circle Old: " << " X: " << listOfShapes[i].X << " Y: " <<  listOfShapes[i].Y << " r: " <<  listOfShapes[i].radius << std::endl;;
            std::cout << "Circle New: " << " X: " << x << " Y: " <<  y << " r: " <<  radius << std::endl;
        }
    }
    return overlapDetected;
}

void rectangleGenerator(int currentShapeInt){
    //Gen 2 random points on the circle
    setRandomPoint(currentShapeInt, 0);
    setRandomPoint(currentShapeInt, 1);
    //Get the slope from these 2 lines.
    double rise = (listOfShapes[currentShapeInt].yPoints[1] - listOfShapes[currentShapeInt].yPoints[0]);
    double run = (listOfShapes[currentShapeInt].xPoints[1] - listOfShapes[currentShapeInt].xPoints[0]);
    double slope = rise/run;
    //double slope = ((listOfShapes[currentShapeInt].yPoints[1] - listOfShapes[currentShapeInt].yPoints[0]) / (listOfShapes[currentShapeInt].xPoints[1] - listOfShapes[currentShapeInt].xPoints[0]));
    while (slope == 0 || std::isnan(slope)){
        std::cout << "FULL TERM " << ((listOfShapes[currentShapeInt].yPoints[1] - listOfShapes[currentShapeInt].yPoints[0]) / (listOfShapes[currentShapeInt].xPoints[1] - listOfShapes[currentShapeInt].xPoints[0])) << std::endl;
        setRandomPoint(currentShapeInt, 0);
        setRandomPoint(currentShapeInt, 1);
        rise = (listOfShapes[currentShapeInt].yPoints[1] - listOfShapes[currentShapeInt].yPoints[0]);
        run = (listOfShapes[currentShapeInt].xPoints[1] - listOfShapes[currentShapeInt].xPoints[0]);
        slope = rise/run;
    }
    double perpSlope = (1/-slope);

    //Find where perpSlop and circle intersect
    bool foundThirdPoint = false;
    while (!foundThirdPoint){
        double point3X = listOfShapes[currentShapeInt].xPoints[0] + (rand() % listOfShapes[currentShapeInt].radius);
        double point3Y = (perpSlope * (point3X - listOfShapes[currentShapeInt].xPoints[0])) + listOfShapes[currentShapeInt].yPoints[0];
        double distance = std::sqrt( std::pow((point3X - listOfShapes[currentShapeInt].X), 2) + std::pow((point3Y - listOfShapes[currentShapeInt].Y),2)); //Find distance from third point to center 
        //Check to see if the combined radius is greater than the distance between them, if so, means overlap
        if (listOfShapes[currentShapeInt].radius >= distance){
            std::cout << "Third point Detected!" << std::endl; //<< combinedRadius << " Distance: " << distance << std::endl;
            foundThirdPoint = true;
            listOfShapes[currentShapeInt].xPoints[2] = point3X;
            listOfShapes[currentShapeInt].yPoints[2] = point3Y;
        }else{
            std::cout << "Third point Fail. RAD: " << listOfShapes[currentShapeInt].radius << "DIS: " << distance << " P3X: " << point3X << " P3Y:" << point3Y << " PERP SLOPE: " << perpSlope << " SLOPE: " << slope
            << " X1: " << listOfShapes[currentShapeInt].xPoints[0] << " X2: " << listOfShapes[currentShapeInt].xPoints[1] << " Y1: " << listOfShapes[currentShapeInt].yPoints[0] << " Y2: " << listOfShapes[currentShapeInt].yPoints[1];
            std::cout << std::endl;
        }
    }
    listOfShapes[currentShapeInt].xPoints[3] = listOfShapes[currentShapeInt].xPoints[2] + (listOfShapes[currentShapeInt].xPoints[1] - listOfShapes[currentShapeInt].xPoints[0]);
    listOfShapes[currentShapeInt].yPoints[3] = listOfShapes[currentShapeInt].yPoints[2] + (listOfShapes[currentShapeInt].yPoints[1] - listOfShapes[currentShapeInt].yPoints[0]);
}
void setRandomPoint(int currentShapeInt, int pointToSet){ 
    //Use polar coords first, then to cartesian
    int r = rand() % listOfShapes[currentShapeInt].radius;
    int theta = rand() % 360;
    double thetaRadians = theta * (M_PI/180);
    listOfShapes[currentShapeInt].xPoints[pointToSet] = listOfShapes[currentShapeInt].X + r * cos(thetaRadians);
    listOfShapes[currentShapeInt].yPoints[pointToSet] = listOfShapes[currentShapeInt].Y + r * sin(thetaRadians);
    std::cout << "Point set at: X: " << listOfShapes[currentShapeInt].xPoints[pointToSet] << " Y: " << listOfShapes[currentShapeInt].yPoints[pointToSet] << std::endl;
    //std::cout << "On Circle of: X: " << listOfShapes[currentShapeInt].X << " Y: " << listOfShapes[currentShapeInt].Y << " radius: " <<listOfShapes[currentShapeInt].radius << std::endl;
}

void printCircles(){
    for (int i = 0; i < listOfShapes.size(); i++){
        std::cout << "Circle: " << i;
        std::cout << " X: " << listOfShapes[i].X;
        std::cout << " Y: " <<  listOfShapes[i].Y;
        std::cout << " r: " <<  listOfShapes[i].radius;
        std::cout << std::endl;
    }
}
void outputShapeCSV(){
    std::ofstream outputFile;
    outputFile.open("output.csv");
    for (int i = 0; i < listOfShapes.size(); i++){
        outputFile << listOfShapes[i].X << "," << listOfShapes[i].Y << "," << listOfShapes[i].radius << 
        "," << listOfShapes[i].xPoints[0] << "," << listOfShapes[i].xPoints[1] << "," << listOfShapes[i].xPoints[2] << "," << listOfShapes[i].xPoints[3] <<
        "," << listOfShapes[i].yPoints[0] << "," << listOfShapes[i].yPoints[1] << "," << listOfShapes[i].yPoints[2] << "," << listOfShapes[i].yPoints[3] <<
        "\n";
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
        rectangleGenerator(i); //Now to make a rectangle with this circle.
    }
    //printCircles();
    outputShapeCSV();
    system("python3 csvViewer.py");
    return 0;
}
