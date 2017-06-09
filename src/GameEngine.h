/** Naijagame
 * Created by Olusegun Ojewale 20-03-2017.
 *
**/

#include "ai.h"
#include <iostream>
#include <fstream>

using namespace std;

class GameEngine {
public:
        // constructor
        GameEngine ();
        
        //Destructor
        ~ GameEngine ();

        int whoson ();
        void reset ();
        void nextPlay ();
        void getscores (int * scores);
        bool isCurrentPlayerHuman ();
        bool validatemove (int x, int y) ;
        void initiateAImove ();
        int aWin ( int * position);

       // int scores ();

        //methods
        void compute_AI_NextMove (const int i, int postion [] );
        void capturemove ( char * _file, int * data);

private:
        int intelligenceLevel = 1;

};

