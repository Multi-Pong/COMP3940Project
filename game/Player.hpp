//
// Created by WillO on 2022-11-14.
//

#ifndef COMP3940PROJECT_PLAYER_HPP
#define COMP3940PROJECT_PLAYER_HPP


class Player {
private:
    int posX;
    int posY;
    int id;
public:
    Player(int id = 0, int posX = 0, int posY = 0) : id(id), posX(posX), posY(posY){};
    int getX(){return posX;};
    int getY(){return posY;};
    int getID(){return id;};
    void setX(int x){posX = x;};
    void setY(int y){posY = y;};
    void setID(int ID){id = ID;};
};


#endif //COMP3940PROJECT_PLAYER_HPP
