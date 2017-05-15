#ifndef PLAYER_PERSON_H
#define PLAYER_PERSON_H

#include <QObject>
#include <iostream>
#include <string>
#include "player.h"


class player_person: public Player
{

public:

   player_person();

   player_person(std::string playerName );


public slots:

    void setName(std::string playerName);


signals:

};

#endif // PLAYER_PERSON_H
