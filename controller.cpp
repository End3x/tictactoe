#include "controller.h"
#include <QObject>
#include <iostream>
#include <QDebug>
#include <QString>
#include  "player_person.h"
#include "board.h"
#include <ctime>
#include <Highscore.h>



using namespace std;


void controller::setGameMode_pvp(game_type selected){
    game_mode = selected;
    std::cout << game_mode << std::endl;
}


void controller::delay(int time){
    clock_t start_time = clock();
    int counter = 1;
    while(clock() < start_time+time *1000){
        if (clock() == start_time + counter*1000)
            std::cout << "(" << counter << ")" << std::endl;
        counter++;
    }
}

controller::controller(QObject *parent) : QObject(parent)
{

}

void controller::clearBoard(){
    for ( int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){

            boardObj.getBoardArray()[i][j] = 0;
        }
    }
    boardObj.displayBoard();
}


bool controller::setMove(int x, int y,bool playerX_turn){


    if(!checkIfWon()){
        std::cout << "no winners" << std::endl;
        if(playerX_turn){

            return boardObj.putX(x,y);
        }else{
            return boardObj.putO(x,y);
        }

        boardObj.displayBoard();
    }else{
        std::cout << "we have a winner" << std::endl;
        return false;
    }

}




void controller::setPlayer(QString playerName, bool playerX){
    if(playerX){
        player_X = new player_person(playerName.toUtf8().constData());
        std::cout << "player_X" << player_X->getName() << std::endl;
    }else{
        player_O = new player_person(playerName.toUtf8().constData());
        std::cout << "player_O" << player_O->getName() << std::endl;
    }


}

void controller::setComputer(){
    player_O = new player_computer();
    std::cout << "computer is named: " << player_O->getName() << std::endl;
}


QString controller::getName_playerX(){
    return QString::fromStdString(player_X->getName());
}


QString controller::getName_playerO(){
    return QString::fromStdString(player_O->getName());
}

void controller::setComputerMove(){
    // TODO: her skal vi legge inn en delay funksjon som gjør at computer ikke legger neste trekk så kjapt.
    if(!checkIfWon()){

        boardObj.playComputer();
    }
}


int controller::getBoardArray(int x, int y){
    return boardObj.getBoardArray()[x][y];
}

bool controller::checkIfWon(){
    return boardObj.checkIfWon(player_X,player_O);
}

int controller::getWinnerDirection(){
    return boardObj.path.direction;
}

int controller::getWinnerSet(){
    return boardObj.path.winner_set;
}

QString controller::getWinnerName(){
    controller::updateScoreInHighscore();
    return QString::fromStdString(boardObj.getWinner()->getName());
}

bool controller::checkIfDraw(){
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            if (boardObj.getBoardArray()[i][j] == 0){
                return false;
            }
        }
    }

    scoreboard.updateScore(boardObj.getWinner()->getName(), 0);
    return true;
}



void controller::showScoresFromHighscore(){
    scoreboard.showScores();
}

void controller::updateScoreInHighscore(){
    scoreboard.updateScore(boardObj.getWinner()->getName(), 10);
}


QString controller::getHighscoreEntriesNames(int i ){
    if(scoreboard.entries.size() > i){
        return QString::fromStdString(scoreboard.entries[i].name);
    }else{
        return "<emplty>";
    }

}

int controller::getHighscoreEntriesScore(int i ){
    if(scoreboard.entries.size() > i){
        return scoreboard.entries[i].score;
    }else{

        return 0;
    }

}

/*std::vector<Highscore::Entry> Highscore::getScores(){

}*/








