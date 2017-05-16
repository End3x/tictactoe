#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <board.h>
#include <player_person.h>
#include <Player_computer.h>
#include <Highscore.h>

class controller : public QObject
{
    Q_OBJECT
    board boardObj;
    Player *player_X;
    Player *player_O;
    Highscore scoreboard;

    enum game_type{
        pvp,
        pvc
    };

    game_type game_mode;

public:
    explicit controller(QObject *parent = 0);

public slots:

    void setGameMode_pvp(game_type game_mode);

    int getWinnerDirection();

    int getWinnerSet();

    bool setMove(int x, int y,bool playerX_turn);

    void clearBoard();

    void setPlayer(QString playerName, bool playerX);

    void setComputer();

    QString getName_playerX();

    QString getName_playerO();

    void setComputerMove();

    int getBoardArray(int x, int y);

    void delay(int x);

    bool checkIfWon();

    QString getWinnerName();

    bool checkIfDraw();

    //std::vector<Highscore::Entry> controller::getScores();

    void showScoresFromHighscore();

    void updateScoreInHighscore();

    QString getHighscoreEntriesNames(int i );

    int getHighscoreEntriesScore(int i );



};

#endif // CONTROLLER_H
