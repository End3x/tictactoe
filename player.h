#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player {

protected:
    std::string name;
    int score;

public:



    std::string getName();

    int getScore();

};

#endif // PLAYER_H
