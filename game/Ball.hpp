//
// Created by super on 2022-11-21.
//

#ifndef COMP3940PROJECT_BALL_HPP
#define COMP3940PROJECT_BALL_HPP

#include <string>

using namespace std;

class Ball {
private:
    int xCoord;
    int yCoord;
public:
    // Default Constructor
    Ball() = default;
    // Overloaded Constructor
    Ball(int xCoord, int yCoord):xCoord(xCoord),yCoord(yCoord){};

    // Getters
    int getXCoord(){ return xCoord; }
    int getYCoord(){ return yCoord; }

    // Setters
    void setXCoord(int X){ xCoord = X; }
    void setYCoord(int Y){ yCoord = Y; }

};


#endif //COMP3940PROJECT_BALL_HPP
