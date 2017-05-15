#include "board.h"
#include <iostream>


board::board(){ 

    boardArray = new int*[3];

    for (int i = 0 ; i < 3 ; i++){
        boardArray[i] = new int[3];

        for (int j = 0; j < 3 ; j++){
            boardArray[i][j]= 0;
        }
    }

    displayBoard();

}

int** board::getBoardArray(){
    return boardArray;
}

Player* board::getWinner(){
    return winner;
}

void board::displayBoard(){
        for (int i = 0 ; i < 3 ; i++){
            for (int j = 0; j < 3 ; j++){
                std::cout << boardArray[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }


/*
board::checkForWinner(){

    //Checks Horizontally
    for ( int i = 0 ; i < 3 ; i++ )
    {
        int counter = 0;
        for (int j = 0 ; j < 3 ; j++ )
        {
            counter += boardArray[i][j];
        }
        if ( counter == 3 )
        {
            winner = playerX;
            return true;
        }
        else if ( counter == -3 )
        {
            winner = playerO;
            return true;
        }
    }

    //Checks Vertically
    for ( int i = 0 ; i < 3 ; i++ )
    {
        int counter = 0;
        for (int j = 0 ; j < 3 ; j++ )
        {
            counter += boardArray[j][i];
        }
        if ( counter == 3 )
        {
            winner = playerX;
            return true;
        }
        else if ( counter == -3 )
        {
            winner = playerO;
            return true;
        }
    }


    //Checks Diagonally

    if ( (boardArray[0][0] + boardArray[1][1] + boardArray[2][2]) == 3 ||
         (boardArray[2][0] + boardArray[1][1] + boardArray[0][2]) == 3   )
    {
        winner = playerX;
        return true;
    }
    else if( (boardArray[0][0] + boardArray[1][1] + boardArray[2][2]) == -3 ||
             (boardArray[2][0] + boardArray[1][1] + boardArray[0][2]) == -3   )
    {
        winner = playerO;
        return true;
    }

    return false;

}
*/


bool board::putX( int row , int column )
{
    //TODO Use try-catch
    try{
        if ( row < 0 || row >= 3 || column < 0 || column >= 3)
        {
           throw 99;
        }
        else if ( boardArray[row][column] != 0 ) //if field is already filled
        {
            throw 88;
        }
        else{
            boardArray[row][column] = 1;
            return true;
        }
    }
    catch (int exc)
    {
        if(exc == 99)
        {
            return false;
        }
        else if(exc == 88)
        {
            return false;
        }
    }
    return false;
}

bool board::putO( int row , int column )
{
    try{
        if ( row < 0 || row >= 3 || column < 0 || column >= 3)
        {
            throw 99;
        }
        else if ( boardArray[row][column] != 0 ) //if field is already filled
        {
            throw 88;
        }
        else{
            boardArray[row][column] = -1;

            return true;
        }
    }
    catch(int exc)
    {
        if(exc == 99)
        {
            return false;
        }
        else if(exc == 88)
        {
            return false;
        }
    }
    return false;
}

bool board::checkIfWon(Player *playerX, Player *playerO) //Returns TRUE if someone has won and sets the winner. Returns FALSE otherwise.
{

    //Checks Vertically
    for ( int i = 0 ; i < 3 ; i++ )
    {
        int counter = 0;
        for (int j = 0 ; j < 3 ; j++ )
        {
            counter += boardArray[i][j];
        }
        if ( counter == 3 )
        {
            winner = playerX;
            path.direction = vertical;
            path.winner_set = i;

            std::cout <<  path.direction << " : " << path.winner_set << std::endl;
            return true;
        }
        else if ( counter == -3 )
        {
            winner = playerO;
            path.direction = vertical;
            path.winner_set = i;

            std::cout <<  path.direction << " : " << path.winner_set << std::endl;
            return true;
        }
    }

    //Checks Horizontally
    for ( int i = 0 ; i < 3 ; i++ )
    {
        int counter = 0;
        for (int j = 0 ; j < 3 ; j++ )
        {
            counter += boardArray[j][i];
        }
        if ( counter == 3 )
        {
            winner = playerX;
            path.direction = horizontal;
            path.winner_set = i;

            std::cout << path.direction << " : " << path.winner_set << std::endl;
            return true;
        }
        else if ( counter == -3 )
        {
            winner = playerO;
            path.direction = horizontal;
            path.winner_set = i;

            std::cout <<  path.direction << " : " << path.winner_set << std::endl;
            return true;
        }
    }


    //Checks Diagonally

    if ( (boardArray[0][0] + boardArray[1][1] + boardArray[2][2]) == 3 ||
         (boardArray[0][0] + boardArray[1][1] + boardArray[2][2]) == -3 )
    {
        path.direction = diagonal;
        path.winner_set = 0;

        if ((boardArray[0][0] + boardArray[1][1] + boardArray[2][2]) == 3){
            winner = playerX;
        }else{
            winner = playerO;
        }

        std::cout <<  path.direction << " : " << path.winner_set << std::endl;
        return true;
    }
    else if( (boardArray[2][0] + boardArray[1][1] + boardArray[0][2]) == 3||
             (boardArray[2][0] + boardArray[1][1] + boardArray[0][2]) == -3   )
    {

        path.direction = diagonal;
        path.winner_set = 1;

        if (boardArray[2][0] + boardArray[1][1] + boardArray[0][2] == 3){
            winner = playerX;

        }else{
            winner = playerO;
        }

        std::cout <<  path.direction << " : " << path.winner_set << std::endl;
        return true;
    }

    return false;
}


bool board::playComputer() //plays only with O's
{
    int rows = 3;
    int cols = 3;
    int length = 3;

    int square1 = boardArray[0][0];
    int square2 = boardArray[0][1];
    int square3 = boardArray[0][2];
    int square4 = boardArray[1][0];
    int square5 = boardArray[1][1];
    int square6 = boardArray[1][2];
    int square7 = boardArray[2][0];
    int square8 = boardArray[2][1];
    int square9 = boardArray[2][2];

    //Used sum methods instead of adding the squares manually s that the code is more flexible
    int sumRow1 = sumRow(0,cols);
    int sumRow2 = sumRow(1,cols);
    int sumRow3 = sumRow(2,cols);
    int sumCol1 = sumCol(0,rows);
    int sumCol2 = sumCol(1,rows);
    int sumCol3 = sumCol(2,rows);
    int sumDiag1 = sumDiagDown(length);//square1 + square5 + square9; //downwards
    int sumDiag2 = sumDiagUp(length);//square7 + square5 + square3; //upwards

    //For Rows
    int maxRowValue = getMaxRowValue(rows,cols);
    //int maxRow = getMaxRow(rows,cols); //NOT USED
    int minRowValue = getMinRowValue(rows,cols);
    //int minRow = getMinRow(rows,cols); //NOT USED

    //For Columns
    int maxColValue = getMaxColValue(rows,cols);
    //int maxCol = getMaxCol(rows,cols); //NOT USED
    int minColValue = getMinColValue(rows,cols);
    //int minCol = getMinCol(rows,cols); //NOT USED

    //For Diagonals
    int maxDiagValue = getMaxDiagValue(length);
    //int maxDiagDirection = getMaxDiag(length); //NOT USED
    int minDiagValue = getMinDiagValue(length);
    //int minDiagDirection = getMinDiag(length); //NOT USED

    //Looks for winning move
    if( minDiagValue == -2 || minColValue == -2 || minRowValue == -2 )
    {

        if (sumDiag1 == -2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square1 == 0)
            {
                return putO(0,0);
            }
            else
            {
                return putO(2,2);
            }
        }
        else if (sumDiag2 == -2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square7 == 0)
            {
                return putO(2,0);
            }
            else
            {
                return putO(0,2);
            }
        }
        else if(sumRow1 == -2)
        {
            if(square1 == 0)
            {
                return putO(0,0);
            }
            else if (square3 == 0)
            {
                return putO(0,2);
            }
            else
            {
                return putO(0,1);
            }
        }
        else if (sumRow3 == -2)
        {
            if(square7 == 0)
            {
                return putO(2,0);
            }
            else if (square9 == 0)
            {
                return putO(2,2);
            }
            else
            {
                return putO(2,1);
            }
        }
        else if (sumCol1 == -2)
        {
            if(square1 == 0)
            {
                return putO(0,0);
            }
            else if (square7 == 0)
            {
                return putO(2,0);
            }
            else
            {
                return putO(1,0);
            }
        }
        else if (sumCol3 == -2)
        {
            if(square3 == 0)
            {
                return putO(0,2);
            }
            else if (square9 == 0)
            {
                return putO(2,2);
            }
            else
            {
                return putO(1,2);
            }
        }
        else if (sumRow2 == -2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square4 == 0)
            {
                return putO(1,0);
            }
            else
            {
                return putO(1,2);
            }
        }
        else //if (sumCol2 == -2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square2 == 0)
            {
                return putO(0,1);
            }
            else
            {
                return putO(2,1);
            }
        }
    }
    //Looks for opponents winning move and defends against it
    else if( maxDiagValue == 2 || maxColValue == 2 || maxRowValue == 2 )
    {

        if (sumDiag1 == 2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square1 == 0)
            {
                return putO(0,0);
            }
            else
            {
                return putO(2,2);
            }
        }
        else if (sumDiag2 == 2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square7 == 0)
            {
                return putO(2,0);
            }
            else
            {
                return putO(0,2);
            }
        }
        else if(sumRow1 == 2)
        {
            if(square1 == 0)
            {
                return putO(0,0);
            }
            else if (square3 == 0)
            {
                return putO(0,2);
            }
            else
            {
                return putO(0,1);
            }
        }
        else if (sumRow3 == 2)
        {
            if(square9 == 0)
            {
                return putO(2,2);
            }
            else if (square7 == 0)
            {
                return putO(2,0);
            }
            else
            {
                return putO(2,1);
            }
        }
        else if (sumCol1 == 2)
        {
            if(square7 == 0)
            {
                return putO(2,0);
            }
            else if (square1 == 0)
            {
                return putO(0,0);
            }
            else
            {
                return putO(1,0);
            }
        }
        else if (sumCol3 == 2)
        {
            if(square3 == 0)
            {
                return putO(0,2);
            }
            else if (square9 == 0)
            {
                return putO(2,2);
            }
            else
            {
                return putO(1,2);
            }
        }
        else if (sumRow2 == 2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square6 == 0)
            {
                return putO(1,2);
            }
            else
            {
                return putO(1,0);
            }
        }
        else //if (sumCol2 == 2)
        {
            if(square5 == 0)
            {
                return putO(1,1);
            }
            else if (square2 == 0)
            {
                return putO(0,1);
            }
            else
            {
                return putO(2,1);
            }
        }


    }
    else
    {
        //Looks for move with possible fork
        if( minDiagValue == -1 || minColValue == -1 || minRowValue == -1 )
        {

            if (sumDiag1 == -1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square1 == 0)
                {
                    return putO(0,0);
                }
                else if (square9 == 0)
                {
                    return putO(2,2);
                }
            }
            else if (sumDiag2 == -1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square7 == 0)
                {
                    return putO(2,0);
                }
                else if (square3 == 0)
                {
                    return putO(0,2);
                }
            }
            else if(sumRow1 == -1)
            {
                if(square1 == 0)
                {
                    return putO(0,0);
                }
                else if (square3 == 0)
                {
                    return putO(0,2);
                }
                else if (square2 == 0)
                {
                    return putO(0,1);
                }
            }
            else if (sumRow3 == -1)
            {
                if(square7 == 0)
                {
                    return putO(2,0);
                }
                else if (square9 == 0)
                {
                    return putO(2,2);
                }
                else if (square8 == 0)
                {
                    return putO(2,1);
                }
            }
            else if (sumCol1 == -1)
            {
                if(square1 == 0)
                {
                    return putO(0,0);
                }
                else if (square7 == 0)
                {
                    return putO(2,0);
                }
                else if (square4 == 0)
                {
                    return putO(1,0);
                }
            }
            else if (sumCol3 == -1)
            {
                if(square3 == 0)
                {
                    return putO(0,2);
                }
                else if (square9 == 0)
                {
                    return putO(2,2);
                }
                else if (square6 == 0)
                {
                    return putO(1,2);
                }
            }
            else if (sumRow2 == -1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square4 == 0)
                {
                    return putO(1,0);
                }
                else if (square6 == 0)
                {
                    return putO(1,2);
                }
            }
            else //if (sumCol2 == -1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square2 == 0)
                {
                    return putO(0,1);
                }
                else if (square8 == 0)
                {
                    return putO(2,1);
                }
            }

        }
        //Defends against player from making a move with a possible fork
        else if( maxDiagValue == 1 || maxColValue == 1 || maxRowValue == 1 )
        {
            if (sumDiag1 == 1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square1 == 0)
                {
                    return putO(0,0);
                }
                else if (square9 == 0)
                {
                    return putO(2,2);
                }
            }
            else if (sumDiag2 == 1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square7 == 0)
                {
                    return putO(2,0);
                }
                else if (square3 == 0)
                {
                    return putO(0,2);
                }
            }
            else if(sumRow1 == 1)
            {
                if(square1 == 0)
                {
                    return putO(0,0);
                }
                else if (square3 == 0)
                {
                    return putO(0,2);
                }
                else if (square2 == 0)
                {
                    return putO(0,1);
                }
            }
            else if (sumRow3 == 1)
            {
                if(square7 == 0)
                {
                    return putO(2,0);
                }
                else if (square9 == 0)
                {
                    return putO(2,2);
                }
                else if (square8 == 0)
                {
                    return putO(2,1);
                }
            }
            else if (sumCol1 == 1)
            {
                if(square1 == 0)
                {
                    return putO(0,0);
                }
                else if (square7 == 0)
                {
                    return putO(2,0);
                }
                else if (square4 == 0)
                {
                    return putO(1,0);
                }
            }
            else if (sumCol3 == 1)
            {
                if(square3 == 0)
                {
                    return putO(0,2);
                }
                else if (square9 == 0)
                {
                    return putO(2,2);
                }
                else if (square6 == 0)
                {
                    return putO(1,2);
                }
            }
            else if (sumCol2 == 1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square2 == 0)
                {
                    return putO(0,1);
                }
                else if (square8 == 0)
                {
                    return putO(2,1);
                }
            }
            else //if (sumRow2 == 1)
            {
                if(square5 == 0)
                {
                    return putO(1,1);
                }
                else if (square4 == 0)
                {
                    return putO(1,0);
                }
                else if (square6 == 0)
                {
                    return putO(1,2);
                }
            }

        }

        //Fill in slot otherwise...
        if(square5 == 0) //goes first for the center
        {
            return putO(1,1);
        }
        else if (square1 == 0 || square3 == 0 || square7 == 0 || square9 == 0) //then goes for the corners
        {
            bool played = false;

            while(!played){
                int random = rand() % 4;
                switch(random)
                {
                    case 0 :
                        if(square1 == 0){
                            played = true;
                            return putO(0,0);
                        }
                        break;
                    case 1 :
                        if(square3 == 0){
                            played = true;
                            return putO(0,2);
                        }
                        break;
                    case 2 :
                        if(square7 == 0){
                            played = true;
                            return putO(2,0);
                        }
                        break;
                    default :
                        if(square9 == 0){
                            played = true;
                            return putO(2,2);
                        }
                        break;
                }
            }

        }

        else if (square2 == 0 || square4 == 0 || square6 == 0 || square8 == 0 ) //Goes for edges otherwise
        {
            bool played = false;

            while(!played){
                int random = rand() % 4;
                switch(random)
                {
                    case 0 :
                        if(square2 == 0){
                            played = true;
                            return putO(0,1);
                        }
                        break;
                    case 1 :
                        if(square4 == 0){
                            played = true;
                            return putO(1,0);
                        }
                        break;
                    case 2 :
                        if(square6 == 0){
                            played = true;
                            return putO(1,2);
                        }
                        break;
                    default :
                        if(square8 == 0){
                            played = true;
                            return putO(2,1);
                        }
                        break;
                }
            }
        }
        else {
            return false;
        }
    }

    return false;

}


bool board::putOinRowWhereEmpty(int rowNumber, int cols) //puts an O in an empty slot of a row(NOT USED but can be used in future for further development)
{
    bool isPut = false;
    for(int i = 0 ; i < cols ; i++ )
    {
        if(boardArray[rowNumber][i] == 0)
        {
            isPut = putO(rowNumber,i);
            break;
        }
    }
    return isPut;
}

bool board::putOinColWhereEmpty(int colNumber, int rows) //puts an O in an empty slot of a column(NOT USED but can be used in future for further development)
{
    bool isPut = false;
    for(int i = 0 ; i < rows ; i++ )
    {
        if(boardArray[i][colNumber] == 0)
        {
            isPut = putO(colNumber,i);
            break;
        }
    }
    return isPut;
}

bool board::putOinDiagWhereEmpty(int direction, int length){ //puts an O in an empty slot of a diagonal(NOT USED but can be used in future for further development)

    bool isPut = false;

    if(direction > 0){ //upwards
        for(int i = 0 ; i < length ; i++)
        {
            if(boardArray[i][i] == 0)
            {
                isPut = putO(i,i);
                break;
            }
        }
    }
    else { //downwards

        int temp = length - 1;
        for(int i = 0 ; i < length ; i++)
        {
            if(boardArray[temp][i] == 0)
            {
                isPut = putO(temp,i);
                break;
            }
            temp--;
        }
    }
    return isPut;
}

int board::sumRow(int rowNumber, int cols){ //Counts points in a row

    int counter = 0;
    for(int j = 0 ; j < cols ; j++)
    {
        if(boardArray[rowNumber][j] == 1)
        {
            counter++;
        }
        else if(boardArray[rowNumber][j] == -1)
        {
            counter--;
        }
    }
    return counter;
}

int board::sumCol(int colNumber, int rows){ //Counts points in a column

    int counter = 0;
    for(int i = 0 ; i < rows ; i++)
    {
        if(boardArray[i][colNumber] == 1)
        {
            counter++;
        }
        else if(boardArray[i][colNumber] == -1)
        {
            counter--;
        }
    }
    return counter;
}

int board::sumDiagDown(int length){ //Counts points in a diagonal going downwards

    int counter = 0;
    for(int i = 0 ; i < length ; i++)
    {
        if(boardArray[i][i] == 1)
        {
            counter++;
        }
        else if(boardArray[i][i] == -1)
        {
            counter--;
        }
    }
    return counter;
}

int board::sumDiagUp(int length){ //Counts points in a diagonal going upwards

    int counter = 0;
    int temp = length - 1;
    for(int i = 0 ; i < length ; i++)
    {
        if(boardArray[temp][i] == 1)
        {
            counter++;
        }
        else if(boardArray[temp][i] == -1)
        {
            counter--;
        }
        temp--;
    }
    return counter;
}

int board::getMaxRowValue(int rows, int cols){ //Gets the highest score value for X-es from rows

    int maxRowValue = -3;
    int temp = 0;
    for(int i = 0 ; i < rows ; i++)
    {
        temp = sumRow(i, cols);
        if (temp > maxRowValue)
        {
            maxRowValue = temp;
        }
    }
    return maxRowValue;
}

int board::getMaxRow(int rows, int cols){ //Gets the row that has the highest score for X-es (NOT USED but can be used in future for further development)

    int maxRowValue = -3;
    int maxRow = -1;
    int temp = 0;
    for(int i = 0 ; i < rows ; i++)
    {
        temp = sumRow(i, cols);
        if (temp > maxRowValue)
        {
            maxRowValue = temp;
            maxRow = i;
        }
    }
    return maxRow;
}

int board::getMaxColValue(int rows, int cols){ //Gets the highest score value for X-es from columns

    int maxColValue = -3;
    int temp = 0;
    for(int i = 0 ; i < cols ; i++)
    {
        temp = sumCol(i, rows);
        if (temp > maxColValue)
        {
            maxColValue = temp;
        }
    }
    return maxColValue;
}

int board::getMaxCol(int rows, int cols){ //Gets the column that has the highest score for X-es (NOT USED but can be used in future for further development)

    int maxColValue = -3;
    int maxCol = -1;
    int temp = 0;
    for(int i = 0 ; i < cols ; i++)
    {
        temp = sumCol(i, rows);
        if (temp > maxColValue)
        {
            maxColValue = temp;
            maxCol = i;
        }
    }
    return maxCol;
}

int board::getMaxDiagValue(int length){ //Gets the highest score value for X-es diagonally

    int downwardsValue = sumDiagDown(length);
    int maxValue = downwardsValue;
    int upwardsValue = sumDiagUp(length);

    if (upwardsValue > downwardsValue)
    {
        maxValue = upwardsValue;
    }
    return maxValue;
}

int board::getMaxDiag(int length){ // returns direction for diagonal with highest score for X-es returns -1 for downwards and 1 for upwards (NOT USED but can be used in future for further development)

    int downwardsValue = sumDiagDown(length);
    int upwardsValue = sumDiagUp(length);

    int maxDirection = -1;

    if (upwardsValue > downwardsValue)
    {
        maxDirection = 1;
    }

    return maxDirection;
}


int board::getMinRowValue(int rows, int cols){ //Gets the highest score value for Os from rows

    int minRowValue = 3;
    int temp = 0;
    for(int i = 0 ; i < rows ; i++)
    {
        temp = sumRow(i, cols);
        if (temp < minRowValue)
        {
            minRowValue = temp;
        }
    }
    return minRowValue;
}

int board::getMinRow(int rows, int cols){ //Gets the row that has the highest score for Os (NOT USED but can be used in future for further development)

    int minRowValue = 3;
    int minRow = -1;
    int temp = 0;
    for(int i = 0 ; i < rows ; i++)
    {
        temp = sumRow(i, cols);
        if (temp < minRowValue)
        {
            minRowValue = temp;
            minRow = i;
        }
    }
    return minRow;
}

int board::getMinColValue(int rows, int cols){ //Gets the highest score value for Os from columns

    int minColValue = 3;
    int temp = 0;
    for(int i = 0 ; i < cols ; i++)
    {
        temp = sumCol(i, rows);
        if (temp < minColValue)
        {
            minColValue = temp;
        }
    }
    return minColValue;
}

int board::getMinCol(int rows, int cols){ //Gets the column that has the highest score for Os (NOT USED but can be used in future for further development)

    int minColValue = 3;
    int minCol = -1;
    int temp = 0;
    for(int i = 0 ; i < cols ; i++)
    {
        temp = sumCol(i, rows);
        if (temp < minColValue)
        {
            minColValue = temp;
            minCol = i;
        }
    }
    return minCol;
}

int board::getMinDiagValue(int length){ //Gets the highest score value for Os diagonally

    int downwardsValue = sumDiagDown(length);
    int minValue = downwardsValue;
    int upwardsValue = sumDiagUp(length);

    if (upwardsValue < downwardsValue)
    {
        minValue = upwardsValue;
    }
    return minValue;
}

int board::getMinDiag(int length){ // returns direction for diagonal with highest score for Os returns -1 for downwards and 1 for upwards (NOT USED but can be used in future for further development)

    int downwardsValue = sumDiagDown(length);
    int upwardsValue = sumDiagUp(length);

    int minDirection = -1;

    if (upwardsValue < downwardsValue)
    {
        minDirection = 1;
    }

    return minDirection;
}

