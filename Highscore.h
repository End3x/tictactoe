#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <cstdlib>





class Highscore
{


public:

    struct Entry{                           //struct to keep scores
        std::string name;                        //string to hold player's name
        int score;                          //int to hold the score
        bool done;                          //bool to tell whether a player is done or not
    };

    std::vector<Entry> entries;



    Highscore();

    void updateScore(std::string name, int point);

    std::vector<Highscore::Entry> getScores();

    //void getScores();

    void showScores();

    friend class controller;



private:

    std::string filename = "Scoreboard.txt";     //Name of file to keep the scores

    void addInFiles(int index, Entry e);

    bool fileExist();

    void updateFile(Entry e, int index);

    void printScores();

    void replaceContent();

    void addEntry(std::string name, int score);

    int findPlace(int score);

    int findPlace(std::string name);

    void updateBoard();

    void cleanVector();

    void cleanScores(std::string name);

    std::vector<std::string> updateBoard(std::vector<std::string> board1);









};

#endif // HIGHSCORE_H
