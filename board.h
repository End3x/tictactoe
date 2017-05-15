#ifndef BOARD_H
#define BOARD_H

#include <player.h>



class board{
    int** boardArray;

    Player *winner;

    enum winner_direction{
        horizontal,
        vertical,
        diagonal
    };

    struct winning_path{
        winner_direction direction;
        int winner_set;
    };




public:

    winning_path path;

    board();

    Player* getWinner();

    int** getBoardArray();

    void displayBoard();

    bool putX( int row , int column );

    bool putO( int row , int column );

    bool checkIfWon(Player *playerX, Player *playerO);

    bool playComputer();

    bool putOinRowWhereEmpty(int rowNumber, int cols);

    bool putOinColWhereEmpty(int colNumber, int rows);

    bool putOinDiagWhereEmpty(int direction, int length);

    int sumRow(int rowNumber, int cols);

    int sumCol(int colNumber, int rows);

    int sumDiagDown(int length);

    int sumDiagUp(int length);

    int getMaxRowValue(int rows, int cols);

    int getMaxRow(int rows, int cols);

    int getMaxColValue(int rows, int cols);

    int getMaxCol(int rows, int cols);

    int getMaxDiagValue(int length);

    int getMaxDiag(int length);

    int getMinRowValue(int rows, int cols);

    int getMinRow(int rows, int cols);

    int getMinColValue(int rows, int cols);

    int getMinCol(int rows, int cols);

    int getMinDiagValue(int length);

    int getMinDiag(int length);
};

#endif // BOARD_H
