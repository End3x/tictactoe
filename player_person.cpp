#include "player_person.h"

#include <iostream>


player_person::player_person(){
    name = "Noname Jackson";
}

player_person::player_person(std::string playerName){
    name = playerName;
}

//player_person::makeMover(column, row){
//
//}

void player_person::setName(std::string playerName){
    name = playerName;
}

