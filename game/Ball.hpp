//
// Created by super on 2022-11-21.
//

#ifndef COMP3940PROJECT_BALL_HPP
#define COMP3940PROJECT_BALL_HPP

#include <string>

using namespace std;

class Ball {
private:
    double xCoord = 0;
    double yCoord = 0;
    double speedX = 0;
    double speedY = 0;
public:
    // Default Constructor
    Ball() = default;
    // Overloaded Constructor
    Ball(int xCoord, int yCoord):xCoord(xCoord),yCoord(yCoord){};

    // Getters
    double getXCoord(){ return xCoord; }
    double getYCoord(){ return yCoord; }
    double getXSpeed(){return speedX;}
    double getYSpeed(){return speedY;}

    // Setters
    void setXCoord(double X){ xCoord = X; }
    void setYCoord(double Y){ yCoord = Y; }
    void setXSpeed(double X){ speedX = X; }
    void setYSpeed(double Y){ speedY = Y; }

};


#endif //COMP3940PROJECT_BALL_HPP
