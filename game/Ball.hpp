//
// Created by super on 2022-11-21.
//

#ifndef COMP3940PROJECT_BALL_HPP
#define COMP3940PROJECT_BALL_HPP

#include <string>

using namespace std;

class Ball {
private:
    int xCoord = 0;
    int yCoord = 0;
    int speedX = 0;
    int speedY = 0;
public:
    // Default Constructor
    Ball() = default;
    // Overloaded Constructor
    Ball(int xCoord, int yCoord):xCoord(xCoord),yCoord(yCoord){};

    // Getters
    int getXCoord(){ return xCoord; }
    int getYCoord(){ return yCoord; }
    int getXSpeed(){return speedX;}
    int getYSpeed(){return speedY;}

    // Setters
    void setXCoord(int X){ xCoord = X; }
    void setYCoord(int Y){ yCoord = Y; }
    void setXSpeed(int X){ speedX = X; }
    void setYSpeed(int Y){ speedY = Y; }

};


#endif //COMP3940PROJECT_BALL_HPP
