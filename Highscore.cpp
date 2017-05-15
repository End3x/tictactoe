#include "Highscore.h"

Highscore::Highscore(){

    if(!fileExist()){                   //checks if file already exists
        std::ofstream outfile;               //if it doesn't, it creates the file
        outfile.open(filename);
        outfile.close();
        return;
    }
    std::ifstream infile;                    //opens the file to read only
    infile.open(filename);
    std::string line, usr_name, usr_score;

    while(getline(infile, line)){       //copies each line in the file to string
        std::string::size_type pos = line.find(':');    //finds position of the dividing symbol
        Entry e;
        if(pos != std::string::npos)    //if it's not an empty line in the file
        {
            e.name = line.substr(0, pos);   //copies content before dividing symbol as player name
            e.score = std::atoi(line.substr(pos+1, std::string::npos).c_str()); //copies after symbol as score, to int
            e.done = true;
        }
        entries.push_back(e);       //pushes the Entry to the back of the vector
    }
    infile.close();     //close filestream

}

void Highscore::addInFiles(int index, Entry e){ //Function adds a player to the back of the file, used when first time playing
    std::fstream outfile;                //Opens in fstream in order to keep the content and do edits
    outfile.open(filename);
    outfile.seekg(std::ios::beg);   //sets pointer(?) to beginning of file
    for(int i=0;i<index-1;++i){
        outfile.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //jumps lines to reach the bottom
    }
    std::stringstream scoren;
    scoren << e.name << ":" << e.score;     //using stringstream in order to keep it clean and add more to string
    outfile << scoren.str() << std::endl;
    outfile.close();
}

bool Highscore::fileExist(){       //function to check if file exists
    std::ifstream f(filename);   //opens file to read only
    bool g = f.good();
    f.close();
    return g;        //returns whether state of stream is good or not (whether exists or not)
}


void Highscore::updateFile(Entry e, int index){ //function to update file
    std::string usr_name = e.name;
    int usr_score = e.score;
    int n_leng = usr_name.length();
    int s_len = 1, dec_counter = 10;
    while(usr_score >= dec_counter){ //checks how many decimals in score-value
        ++s_len;
        dec_counter *= 10;
    }
    std::fstream f_file;                 //sets file to read and write
    std::string line, tmp;
    int indexer=0;
    f_file.open(filename);          //opens file
    while(getline(f_file, line)){   //runs until stopped or unable to find new line
        tmp = line.substr(0, n_leng);   //copies content in the interval as user name
        if(tmp == usr_name){                //checks if name from line matches name from active user
            if(indexer == index){           //checks if user's position is unchanged
                std::string ss = usr_score + "";     //if so, then it only updates the score
                line.replace(n_leng+2, s_len, ss);
                return;                         //exits function
            }
            break;          //if user has moved up, breaks from loop
        }
        ++indexer;          //counts the position being checked
    }
    f_file.close();         //close file
    replaceContent();       //because user has new position, goes to another function
}



void Highscore::printScores(){
    int llll = entries.size();
    for(int i=0;i<llll;i++){
        std::cout << entries[i].name << " : " << entries[i].score << std::endl;
    }
}


void Highscore::replaceContent(){      //function to replace all file-content with vector-content
                            //this is easier than to traverse the file and change each position up or down
    std::ofstream outfile;
    outfile.open(filename, std::ofstream::out | std::ofstream::trunc);  //opens file to clear it
    std::stringstream line;
    int entry_count = 5;                                    //only 5 highest scores are stored in file
    if(entries.size() < 5) entry_count = entries.size();    //if less than 5 scores, uses amount of entries in vector

    for(int i=0; i<entry_count; i++){                   //for-loop to go through each entry in Entry-vector
        line << entries[i].name << ":" << entries[i].score;     //copies each Entry with dividing symbol after name
        outfile << line.str() << std::endl;                      //inserts line into lowest line in file
        line.str("");                                       //clears the stringstream for next Entry
    }
    outfile.close();                                    //close file
}


void Highscore::updateScore(std::string name, int point){   //default function to update users score

    int index_n = findPlace(name);          //checks which position user is in, if any
    if(index_n == -1) addEntry(name, point);    //if user doesn't exist, is added by addEntry-function
    else{
        if(point == 0){                     //if the user didn't receive a point, the streak is broken
            entries[index_n].done = true;   //the player-object is set to finished
            updateBoard();                  //calls the updateBoard-functiom
            cleanVector();                  //calls the cleanVector-function
            return;                         //exits the function all together
        }else{                                  //if the player did get a point
            entries[index_n].score += point;    //adds that point to the player's score
            updateBoard();                      //calls updateBoard-function
        }
    }
}


void Highscore::addEntry(std::string name, int score){      //function to first add user to Entry-vector
        Entry e;                        //creates the Entry-object
        e.name = name;
        e.score = score;
        e.done = false;

        entries.push_back(e);               //puts Entry in back of Entry-vector
        cleanScores(name);                  //sets all other players to finished
        updateBoard();                      //updates scoreboard. This is for when less than 5 people have played.
}


int Highscore::findPlace(int score){           //function to find users position based on score
    int siz = entries.size();       //holds length of Entry-vector
    for(int i=0;i<siz;i++){             //for-loop checks trough Entry-vector elements from top to bottom
        if(score > entries[i].score)    //if user's score is higher than the currently checked
            return i;                   //returns position of that Entry
    }
    return siz-1;                         //if score is lowest in vector, returns last position in vector
}

int Highscore::findPlace(std::string name){         //function to find user's position based on name
    int siz = entries.size();       //is very much similar to the function above
    for(int i=0;i<siz;i++){
        if(entries[i].name == name && entries[i].done == false)     //if element-name matches user name
            return i;                   //returns position
    }
    return -1;                          //if user is not in vector, returns -1
}

void Highscore::updateBoard(){     //updates scoreboard to reflect scores in vector
    int v_len = entries.size();     //stores size of entries-vector
    for(int i=v_len-1;i>=0;i--){        //first for-loop starts at the back of the vector
        for(int j=i;j>=0;j--){          //second for-loop starts one element in front of first loop
            if(entries[i].score > entries[j].score){    //if score behind is higher than in front
                std::iter_swap(entries.begin()+i, entries.begin()+j);   //swaps the two entries
            }
        }
    }
    replaceContent();       //empties the file and inserts entries from the vector
}


void Highscore::cleanVector(){     //removes all entries not on the scoreboard
    int v_len = entries.size();     //stores entries-vector size
    if(v_len < 5) return;           //if vector is shorter than 5, quits function
    else{
        for(int i=v_len-1; i>4;i--){    //starts at the back of the vector and does not touch top 5 entries
            entries.erase(entries.begin()+i);   //erases all other entries after fifth element
        }
    }
}


void Highscore::cleanScores(std::string name){  //function to set all inactive players to finished
    int v_len = entries.size();     //stores size of entries-vector
    int index = findPlace(name);    //finds index of where the player is using name
    for(int i=0;i<v_len;i++){       //for-loop to traverse the whole vector
        if(i != index) entries[i].done = true;  //sets all entries to "done" except the located one
    }
}


std::vector<Highscore::Entry> Highscore::getScores(){
    cleanVector();
    return entries;
}


/*void Highscore::getScore(){
    //stringstream ss;
    int v_len = entries.size();
    if(v_len > 5) v_len = 5;
    for(int i=0;i<v_len;i++){
        std::cout << " " << entries[i].name << "\t\t| " << entries[i].score << std::endl;
    }
    //return ss.str();
}*/


void Highscore::showScores(){
    std::vector<std::string> board;


    std::string headline = "------------High Score------------";
    std::string categories = "|Nr:| Name:     | Score:         |";
    std::string line = "----------------------------------";
    std::string f1 = "| 1 |           |                |";
    std::string f2 = "| 2 |           |                |";
    std::string f3 = "| 3 |           |                |";
    std::string f4 = "| 4 |           |                |";
    std::string f5 = "| 5 |           |                |";


    board.push_back(f1);
    board.push_back(f2);
    board.push_back(f3);
    board.push_back(f4);
    board.push_back(f5);

    board= updateBoard(board);
    std::stringstream ss;



    std::cout << headline << std::endl << categories << std::endl << line << std::endl;
    for(int i=0;i<5;i++){
        std::cout << board[i] << std::endl;
    }

    //std::cout << ss.str();
}



std::vector<std::string> Highscore::updateBoard(std::vector<std::string> board1){
    std::vector<std::string> board = board1;
    int nnnn = entries.size();

    if (nnnn < 1 ){return board;}

    if (entries.size() > 5){nnnn = 5;}

    for(int i=0;i<nnnn;i++){
        std::string tmp_name = entries[i].name;
        int nam_l = tmp_name.length();
        std::stringstream tmp_score;
        tmp_score << entries[i].score;



        board[i].replace(6, nam_l, tmp_name);
        board[i].replace(18, tmp_score.str().length(), tmp_score.str());
        tmp_score.str("");
    }

    return board;

}






