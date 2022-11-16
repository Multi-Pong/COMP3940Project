//
// Created by WillO on 2022-11-14.
//

#ifndef COMP3940PROJECT_PLAYER_HPP
#define COMP3940PROJECT_PLAYER_HPP

#include <ostream>

using namespace std;

class Player {
private:
    int posX;
    int posY;
    int id;
public:
    Player(int id = 0, int posX = 0, int posY = 0) : id(id), posX(posX), posY(posY) {};

    int getX() const { return posX; };

    int getY() const { return posY; };

    int getID() const { return id; };

    void setX(int x) { posX = x; };

    void setY(int y) { posY = y; };

    void setID(int ID) { id = ID; };

    friend ostream &operator<<(ostream &os, const Player &player) {
        os << "Player id: " << player.getID() << endl;
        os << "Player x: " << player.getX() << endl;
        os << "Player y: " << player.getY() << endl;
        return os;
    }
};


#endif //COMP3940PROJECT_PLAYER_HPP
