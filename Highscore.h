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

    std::string filename = "Scoreboard.txt";     //Name of file to keep the scores

    struct Entry{                           //struct to keep scores
        std::string name;                        //string to hold player's name
        int score;                          //int to hold the score
        bool done;                          //bool to tell whether a player is done or not
    };

    std::vector<Entry> entries;

public:
    Highscore();

    void addInFiles(int index, Entry e);

    bool fileExist();

    void updateFile(Entry e, int index);

    void printScores();

    void replaceContent();

    void updateScore(std::string name, int point);

    void addEntry(std::string name, int score);

    int findPlace(int score);

    int findPlace(std::string name);

    void updateBoard();

    void cleanVector();

    void cleanScores(std::string name);

    std::vector<Entry> getScores();

    void getScore();
};

#endif // HIGHSCORE_H