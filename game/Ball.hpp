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
    float radius;
    string color;
public:
    // Default Constructor
    Ball() = default;
    // Overloaded Constructor
    Ball(int xCoord, int yCoord, float radius, string color):xCoord(xCoord),yCoord(yCoord),radius(radius),color(color){};

    // Getters
    int getXCoord(){ return xCoord; }
    int getYCoord(){ return yCoord; }
    float getRadius() { return radius; }
    string getColor() { return color; }

    // Setters
    void setXCoord(int X){ xCoord = X; }
    void setYCoord(int Y){ yCoord = Y; }
    void setRadius(float rad){ radius = rad; }
    void setColor(string col){ color = col; }

};


#endif //COMP3940PROJECT_BALL_HPP
