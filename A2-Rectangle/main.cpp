#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
class shapeObject {
    public:
        int X;
        int Y;
        int radius;
        double xPoints[4] = {0.0,0.0,0.0,0.0};
        double yPoints[4] = {0.0,0.0,0.0,0.0};
        double minTheta;
        double maxTheta;
};
class occlusionObject{
    public:
        double minTheta;
        double maxTheta;
};
//Function prototypes
void circleGenerator();
bool overlap(int, int, int);
void rectangleGenerator(int);
void setRandomPoint(int, int);
void caluclateRectangleThetas(int);
bool rectanglesOcclude(shapeObject, shapeObject);
void finalAllOcclusion(int);
void storeOcclusionAngles(double, double);
void sortOcclusionAngles();
void outputTotalOcclusionAngle();
void printCircles();
void outputShapeCSV();
bool inRange(double, double, double);

//PLEASE NOTE
//THE DRAWING LIBRARY SOMETIMES RENDERS OVERLAPS
//THEY ARE NOT ACTUALLY OVERLAPPING. I CHECKED.

std::vector<shapeObject> listOfShapes;
std::vector<occlusionObject> listOfOcclusion;
std::vector<occlusionObject> listOfOcclusionNoOverlap;

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
    while (slope == 0 || std::isnan(slope)){
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
        //Check to see if the combined radius is greater than the distance between them, if so, means overlap (we want this)
        if (listOfShapes[currentShapeInt].radius >= distance){
            foundThirdPoint = true;
            listOfShapes[currentShapeInt].xPoints[2] = point3X;
            listOfShapes[currentShapeInt].yPoints[2] = point3Y;
        }
    }
    listOfShapes[currentShapeInt].xPoints[3] = listOfShapes[currentShapeInt].xPoints[2] + (listOfShapes[currentShapeInt].xPoints[1] - listOfShapes[currentShapeInt].xPoints[0]);
    listOfShapes[currentShapeInt].yPoints[3] = listOfShapes[currentShapeInt].yPoints[2] + (listOfShapes[currentShapeInt].yPoints[1] - listOfShapes[currentShapeInt].yPoints[0]);
    caluclateRectangleThetas(currentShapeInt);
}
void setRandomPoint(int currentShapeInt, int pointToSet){ 
    //Use polar coords first, then to cartesian
    int r = rand() % listOfShapes[currentShapeInt].radius;
    int theta = rand() % 360;
    double thetaRadians = theta * (M_PI/180);
    listOfShapes[currentShapeInt].xPoints[pointToSet] = listOfShapes[currentShapeInt].X + r * cos(thetaRadians);
    listOfShapes[currentShapeInt].yPoints[pointToSet] = listOfShapes[currentShapeInt].Y + r * sin(thetaRadians);
}

void caluclateRectangleThetas(int currentShapeInt){
    double thetaList[4];
    for (int i = 0; i < 4; i++){
        double theta = (180/M_PI) * (std::atan2(listOfShapes[currentShapeInt].yPoints[i], listOfShapes[currentShapeInt].xPoints[i]));
        theta = std::fmod((theta + 360), 360.00);
        thetaList[i] = theta;
    }
    std::sort(std::begin(thetaList), std::end(thetaList));
    listOfShapes[currentShapeInt].minTheta = thetaList[0];
    listOfShapes[currentShapeInt].maxTheta = thetaList[3];
}
bool rectanglesOcclude(shapeObject firstRect, shapeObject secondRect){
    bool overlap = false;
    if (inRange(firstRect.minTheta, firstRect.maxTheta, secondRect.minTheta)){
        overlap = true;
    }
    if (inRange(firstRect.minTheta, firstRect.maxTheta, secondRect.maxTheta)){
        overlap = true;
    }
    
    return overlap;
}
void finalAllOcclusion(int intNumOfRects){
    double largestMinTheta = 0.0;
    double smallestMaxTheta = 0.0;
    //For every rectangle, check against every other rectangle
    for (int currentRec = 0; currentRec < intNumOfRects ; currentRec++){
        for (int comparisonRec = 0; comparisonRec < intNumOfRects ; comparisonRec++){
            if (currentRec != comparisonRec){ //Do not want to check against ourself
                if (rectanglesOcclude(listOfShapes[currentRec], listOfShapes[comparisonRec])){ //Check to see if there is an overlap
                    if (listOfShapes[currentRec].minTheta > listOfShapes[comparisonRec].minTheta){//Check to see which rectangle has the largest minTheta
                        largestMinTheta = listOfShapes[currentRec].minTheta;
                    }else{
                        largestMinTheta = listOfShapes[comparisonRec].minTheta;
                    }

                    if (listOfShapes[currentRec].maxTheta < listOfShapes[comparisonRec].maxTheta){//Check to see which rectangle has the smallest maxTheta
                        smallestMaxTheta = listOfShapes[currentRec].maxTheta;
                    }else{
                        smallestMaxTheta = listOfShapes[comparisonRec].maxTheta;
                    }
                    storeOcclusionAngles(largestMinTheta, smallestMaxTheta);
                }
            }
        }
    }
}
void storeOcclusionAngles(double minTheta, double maxTheta){
    occlusionObject newOcclusionObj;
    newOcclusionObj.minTheta = minTheta;
    newOcclusionObj.maxTheta = maxTheta;
    listOfOcclusion.emplace_back(newOcclusionObj);
}
bool compareMinThetas(occlusionObject first, occlusionObject second){
    return (first.minTheta < second.minTheta);
}
void sortOcclusionAngles(){
    std::sort(listOfOcclusion.begin(), listOfOcclusion.end(), compareMinThetas);
    listOfOcclusionNoOverlap.emplace_back(listOfOcclusion[0]);
    for (int i = 1; i < listOfOcclusion.size(); i++){
        if (listOfOcclusionNoOverlap.back().maxTheta < listOfOcclusion[i].minTheta){ //If our last value in our combined list is less than our current start value
            listOfOcclusionNoOverlap.emplace_back(listOfOcclusion[i]);               //Add it to the combined list
        } else if(listOfOcclusionNoOverlap.back().maxTheta == listOfOcclusion[i].minTheta){ //Catch in case both have the same value
            listOfOcclusionNoOverlap.back().maxTheta = listOfOcclusion[i].maxTheta;
        }
        if (listOfOcclusion[i].maxTheta > listOfOcclusionNoOverlap.back().maxTheta){ //Our current max theta is larger than the one in the list
            listOfOcclusionNoOverlap.back().maxTheta = listOfOcclusion[i].maxTheta;  //So, set the combined list to the larger max theta
        }
    }
}
/* Not used anymore, but keeping in to show previous method not using c++ build in sorting algo.
void sortOcclusionAnglesOLD(){
    for (int curRect = 0; curRect < listOfOcclusion.size(); curRect++){
        for (int compRect = 0; compRect < listOfOcclusion.size(); compRect++){
            //Check to make sure we don't compare against ourself
            if (curRect != compRect){
                bool overlap = false;
                if(inRange(listOfOcclusion[compRect].minTheta, listOfOcclusion[compRect].maxTheta, listOfOcclusion[curRect].minTheta)){
                    overlap = true;
                }
                if(inRange(listOfOcclusion[compRect].minTheta, listOfOcclusion[compRect].maxTheta, listOfOcclusion[curRect].maxTheta)){
                    overlap = true;
                }
                if(overlap){
                    if(listOfOcclusion[curRect].minTheta > listOfOcclusion[compRect].minTheta){
                        listOfOcclusion[curRect].minTheta = listOfOcclusion[compRect].minTheta;
                    }
                    if(listOfOcclusion[curRect].maxTheta < listOfOcclusion[compRect].maxTheta){
                        listOfOcclusion[curRect].maxTheta = listOfOcclusion[compRect].maxTheta;
                    }
                    listOfOcclusion.erase(listOfOcclusion.begin() + compRect);
                    sortOcclusionAnglesOLD(); //If there is an overlap, we might need to sort again after expanding.
                }
            }
        }
    }
}*/
void outputTotalOcclusionAngle(){
    sortOcclusionAngles();
    double totalAngle = 0;
    for (int i = 0; i < listOfOcclusionNoOverlap.size(); i++){
        double displacment = listOfOcclusionNoOverlap[i].maxTheta - listOfOcclusionNoOverlap[i].minTheta;
        totalAngle = totalAngle + displacment;
        std::cout << "Item [" << i << "]: MIN: " << listOfOcclusionNoOverlap[i].minTheta << " MAX: " << listOfOcclusionNoOverlap[i].maxTheta << " TOTAL: " << totalAngle <<std::endl;
    }
    /* Old method, kept just in case. (Also works, just slower)
    double totalAngleOLD = 0;
    sortOcclusionAnglesOLD();
    for (int i = 0; i < listOfOcclusion.size(); i++){
        double displacmentOLD = listOfOcclusion[i].maxTheta - listOfOcclusion[i].minTheta;
        totalAngleOLD = totalAngleOLD + displacmentOLD;
    }
    std::cout << "***Total Occlusion Angle is: " << totalAngleOLD << " OLD METHOD" << std::endl;
    */
    std::cout << "***Total Occlusion Angle is: " << totalAngle << std::endl;
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
bool inRange(double firstBound, double secondBound, double between){
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
    finalAllOcclusion(intNumOfRects);
    outputTotalOcclusionAngle();
    outputShapeCSV();
    system("python3 csvViewer.py");

    return 0;
}