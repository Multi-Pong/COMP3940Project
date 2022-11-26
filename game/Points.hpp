//
// Created by super on 2022-11-21.
//

#ifndef COMP3940PROJECT_POINTS_HPP
#define COMP3940PROJECT_POINTS_HPP


#include <string>

using namespace std;

class Points {
private:
    int teamOnePoints;
    int teamTwoPoints;
public:
    // Default Constructor
    Points() = default;
    // Overloaded Constructor
    Points(int teamOneP, int teamTwoP):teamOnePoints(teamOneP),teamTwoPoints(teamTwoP){};

    // Getters
    int getTeamOnePoints(){ return teamOnePoints; }
    int getTeamTwoPoints(){ return teamTwoPoints; }

    // Setters
    void setTeamOnePoints(int point){ teamOnePoints = point; }
    void setTeamTwoPoints(int point){ teamTwoPoints = point; }

    void incrementTeamOnePoints(){ ++teamOnePoints; }
    void incrementTeamTwoPoints(){ ++teamTwoPoints; }

};


#endif //COMP3940PROJECT_POINTS_HPP
