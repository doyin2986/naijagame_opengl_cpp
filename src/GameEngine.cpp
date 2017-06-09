/** Naijagame
 * Created by Olusegun Ojewale 20-03-2017.
 *
**/

#include "GameEngine.h"
#include <algorithm>


int playing_next = 0 ; //0 first player,  1 for second player
int winner = -1 ;      //0 first player,  1 for second player

const int winningpositions[4][3] = {{2,5,8},{4,5,6},{3,5,7},{1,5,9}};


enum {HUMAN, COMPUTER};
  
  struct _gameplayer {
          int score; 
          int type = 0 ; // 0 human, 1 computer
          int position;  // 0 first player, 1 second player
          int owner = 1;
  };

_gameplayer two_players [2];

// initialise AI
AI ai;

GameEngine::GameEngine() {
        std::cout << "GameEngine initialised";
        two_players[0].type = 1;               // controlled by AI

        // who plays first .... randomize
        srand(time(0));
        playing_next = rand() % 2;

}

GameEngine::~GameEngine() {
        std::cout << "GameEngine destroyed";
}

void GameEngine::reset () {
        srand(time(0));
        playing_next = rand() % 2;
}

void GameEngine::getscores (int * scores) {

        *scores = two_players[0].score;
        *(scores +  1) = two_players[1].score;

}

int  GameEngine::whoson () {
        return playing_next;
}

int GameEngine::aWin(int * position) {

        const int winningpositions[4][3] = {{2,5,8},{4,5,6},{3,5,7},{1,5,9}};

        int pp []  = { 0,0,0};

        int n = 1;
        int i = 0;

        while  (true) {
                for (int j = 0; i < (n * 3 ); ++i, ++j)
                  pp [j] =  (* (position + i)) + 1 ; // + 1 to correct offset

                sort(pp, pp + 3); // first sort the array


                for  (int m =0 ; m < 4 ; ++m)
                  if (winningpositions[m][0] == pp [0] &&   winningpositions[m][1] == pp [1]  && winningpositions[m][2] == pp [2])  {
                          
                          // a win detected, update score
                          if (n == 2) 
                                  two_players [HUMAN].score = two_players [HUMAN].score + 1;
                          else
                                  two_players [COMPUTER].score = two_players [COMPUTER].score + 1;

                        
                          return n;
                        }
        
                if (n == 2) break;
                n++;
        }

  return 0;
}


void GameEngine::nextPlay(){
        if (playing_next == 1) {
                playing_next = 0;
        }
        else {
                playing_next = 1;
        }
}

bool GameEngine::isCurrentPlayerHuman ()  {

        if (two_players[playing_next].type == 1) {
                return true ;
        }
        else { 
                return false;
        }
}


bool GameEngine::validatemove (int x, int y) {

        int possiblemoves [24][2] = {{1,2},{1,4},{1,5},{2,1},{2,3},{2,5},{3,2},{3,5},{3,6}
                ,{4,1},{4,5},{4,7},{6,5},{6,3},{6,9},{7,4},{7,5},{7,8},{8,9},{8,7},{8,5},{9,5},{9,6},{9,8}};

        for (int i=0 ; i < 23; ++i) {
                if ((possiblemoves[i][0] == x && possiblemoves[i][1] == y) || (possiblemoves[i][1] == x && possiblemoves[i][0] == y))
                        return true;
        }

        return false;
}


// method to convert given Integer Array to character array
void convertIntArrayToChar(const int integerArray [], char characterArray [],const int _length = 6, const int _offset = 1) {
       // char  character_array [_length];
        for (int i =0; i < _length; ++i ) {
                characterArray [i] = '0' + (integerArray [i] +  _offset );
                std::cout << characterArray [i];
        }

        std::cout << "conversion to Char done"<<std::endl;

}


void convertCharArrayToInt( int integerArray [], const char characterArray [],const int _length = 6, const int _offset = 1) {
       // char  character_array [_length];
        std::cout << "testing"<<std::endl;
        for (int i =0; i < _length; ++i ) {
                integerArray [i] = (characterArray [i] - 48) - _offset ;
                std::cout << integerArray [i];
        }
}

bool compareCharArrayContent_old(const char c1 [], char c2 [],const int _length = 6) {
        // char  character_array [_length];
        for (int i =0; i < _length; ++i ) {
            std::cout << "comparing " <<c1[i] <<c2[i];
            if ( c1 [i] != c2 [i] )
                    return false;
        }
        return true;
}

bool compareCharArrayContent(const char a[], char b [],const int _length = 6) {
           // char  character_array [_length];
        if ((( a[0] == b[0] && a[1] == b [1] && a[2] == b[2])// ||
           /*( a[1] == b[0] && a[0] == b [1] && a[2] == b[2]) ||
           ( a[0] == b[0] && a[1] == b [2] && a[2] == b[1]) ||
           ( a[1] == b[0] && a[2] == b [1] && a[0] == b[2]) ||
           ( a[2] == b[0] && a[1] == b [1] && a[0] == b[2]) ||
           ( a[2] == b[0] && a[0] == b [1] && a[1] == b[2])*/)
                                &&
           ((a[3] == b[3] && a[4] == b [4] && a[5] == b[5]) //||
           /*( a[4] == b[3] && a[3] == b [4] && a[5] == b[5]) ||
           ( a[3] == b[3] && a[4] == b [5] && a[5] == b[4]) ||
           ( a[4] == b[3] && a[5] == b [4] && a[3] == b[5]) ||
           ( a[5] == b[3] && a[4] == b [4] && a[3] == b[5]) ||
           ( a[5] == b[3] && a[3] == b [4] && a[4] == b[5])*/))
                return true;
        else
                return false;
}


bool readinfo (char *  _file, char * c2) {
        ifstream infile;
        char data [9];

        bool flag;

        infile.open(_file);
        while (infile >> data) {
          // write the data at the screen.
          //std::cout << "OJezzzzzz comparing " << c2[0] << c2[1] << c2 [2] << c2 [3] <<  c2[4] << c2[5] << c2 [6]<<" and " << data <<endl; 
          if ( compareCharArrayContent (c2, data )){
                  std::cout << "wwww match/convertIntArrayToCharh"<< c2[0]<<data[6]<<c2[1]<<data[7]<<c2[2]<<data[8]<<std::endl;
                  c2 [0] = data [6];
                  c2 [1] = data [7];
                  c2 [2] = data [8];

                  flag = true;
                  break;
          }
        }
        infile.close();

        return flag;
}

// method to compute next AI move
void GameEngine::compute_AI_NextMove ( const int level, int postion [] ) {
        // break positon array down to two char * arrays , first player (0,3) , second player 4,6
        //
        char dbname [] =  "user.kw";
        char * filename = dbname;
        char c2 [6];

        char char_postion [6];
        char char_postion2 [3];
        convertIntArrayToChar(postion, char_postion);

        std::cout << "samples  "<< *((&char_postion[3]) + 1);// << " and " << char_postion[5]<<std::endl;

        char_postion2 [0] = char_postion[3];
        char_postion2 [1] = char_postion[4];
        char_postion2 [2] = char_postion[5];

        std::cout << "samples 2 "<< &char_postion2 ;// << " and " << char_postion[5]<<std::endl;

        //call AI move
        const char * result_copy = ai.computemove( & char_postion[0], & char_postion2 [0], true);
        char result [3];

        result [0] =  result_copy[0];
        result [1] =  result_copy[1];
        result [2] =  result_copy[2];

        if (result[2] == 't') { // a win move 

                int loc =  (* result) - 48;
                int loc2 = (* (result + 1)) -48;
                std::cout << loc <<loc2<<std::endl;
                std::cout << postion [loc] <<std::endl;
                postion [loc ]  = loc2 - 1 ;
                std::cout << postion [loc] <<std::endl;
                
                return;

        }

        //check knowledge base to see if a match exists
        convertIntArrayToChar (postion, c2,6,0);
        std::cout << "u do am " << c2[5];
        if ( readinfo (filename, c2) ) {
                convertCharArrayToInt (postion, c2,6,0);
                return;
        }

        // use calculated move

        int loc =  (int) ((* (result)) -48);
        int loc2 = (int) ((* (result + 1)) -48);
        std::cout << loc <<loc2<<std::endl;
        std::cout << postion [loc] <<std::endl;
        postion [loc ]  = loc2 - 1 ; 
        std::cout << postion [loc] <<std::endl;


}

void GameEngine::capturemove ( char * _file, int * data) {
        ofstream myfile;
        myfile.open (_file,ios::out | ios::app | ios::binary);

        myfile << data [3] << data [4]  << data [5]  << data [0]  << data [1]  << data [2]  << data [6]  << data [7]  << data [8] ;  // save user move as  a computer move

        myfile  << "\n";

        myfile.close();

}


int quick_test() {
        int tt [] = { 0,1,2,6,7,8};
        GameEngine game;
        game.compute_AI_NextMove (1,tt);
        std::cout << "whos on "<< game.whoson();
        game.nextPlay();
        std::cout << "whos on "<< game.whoson(); 
}

