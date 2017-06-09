/** Naijagame
 * Created by Olusegun Ojewale 20-03-2017.
 *
**/

#include "ai.h"
#include <algorithm>

const int possiblemoves [24][2] = {{1,2},{1,4},{1,5},{2,1},{2,3},{2,5},{3,2},{3,5},{3,6},{4,1},{4,5},{4,7},{6,5},{6,3},{6,9},{7,4},{7,5},{7,8},{8,9},{8,7},{8,5},{9,5},{9,6},{9,8}};
const int winningpositions[4][3] = {{2,5,8},{4,5,6},{3,5,7},{1,5,9}};

bool IsAwinPosition (char * position) {

        int pp []  = { 0,0,0}; // card positions

        for (int i=0; i < 3; ++i) {
          pp [i] =  (int) ((* (position + i)) -48); //casting from char to int
        }

        sort(pp, pp + 3); // first sort the array

        for  (int i =0 ; i < 4 ; ++i)
          if (winningpositions[i][0] == pp [0] &&   winningpositions[i][1] == pp [1]  && winningpositions[i][2] == pp [2])
                  return true;

        return false;
}


AI::AI() 
{
        cout << "constructor works"<< endl;
}


void AI::setLevel(int level) 
{
        this->intelligenceLevel = level;
}


const char * AI::computemove (const char * mylocations, const char * opponent, bool checkwin = false ) 
{
        // compute where I could potentially move to
        // if im in location 123, and oppnent in loc 7,8,9 , potentially
        // I could move to 4,5 or 6
        // const int possiblemoves [24][2] = {{1,2},{1,4},{1,5},{2,1},{2,3},{2,5},{3,2},{3,5},{3,6},{4,1},{4,5},{4,7},{6,5},{6,3},{6,9},{7,4},{7,5},{7,8},{8,9},{8,7},{8,5},{9,5},{9,6},{9,8}};
        const int TRAILS = 20;
        char list [] = {'1','2','3','4','5','6','7','8','9'};// {"1","2","3","4","5","6","7","8","9"};
        char results  [15][2];
        int matches = 0;

        char mylocation_copy [] = {'0','0','0'}; 

        // create a list and mark out occupied slots
        for (int i = 0; i < 3; i++) {
                int loc =(int)((* (mylocations + i)) - 48);  // convert char to int
                list[loc-1] = '0'; // mark element

                int loc2 = (int)((* (opponent + i)) - 48);
                list[loc2 -1] = '0';
        }

        // now copy out available slots
        char   avail_positions [9];
        int jj = 0;

        for (int i = 0;i < 9; i++) { 
                if (list[i] !='0' ){ 
                        avail_positions [jj++] = list[i];
                        cout << list[i];
                }

        }
        
        cout << ""<<endl;

        /* 
         * this bit should be reworked
         */
        char computed_locations [3] = {'0','0','f'}; //mylocations; 

        // break flag
        bool IS_SET = false;

        for (int myrand1 = 0; myrand1 < 3 ;++ myrand1) 
                for (int myrand2 = 0; myrand2 < jj ;++ myrand2){

                        char change = *(mylocations + myrand1);
                        char change_to = avail_positions[myrand2];

                        int apositionempts = 0;
                        for (int myrand = 0; myrand < 24; ++myrand) {

                                if( (possiblemoves [myrand][0] == (int)change - 48)  && (possiblemoves [myrand][1] == (int)change_to - 48) ||
                                        (possiblemoves [myrand][1] == (int)change - 48)  && (possiblemoves [myrand][0] == (int)change_to - 48)) {
                                        computed_locations[0] = '0' +   myrand1 ;
                                        results[matches][0] = '0' +   myrand1 ;

                                        computed_locations[1] =  change_to;
                                        results[matches][1] = change_to;
                                        matches++;

                                        // set break flag
                                        IS_SET = true;

                                        if ( checkwin == true) {
                                                for (int bb = 0; bb < 3; ++bb)
                                                        mylocation_copy [bb] = (* (mylocations + bb) ) ;

                                                mylocation_copy [myrand1] = change_to;

                                                // now check if the change is a win
                                                if (IsAwinPosition (mylocation_copy)) {
                                                        // set match flag
                                                        computed_locations [2] =  't';

                                                        const char * computed_locations_rtn = computed_locations;
                                                        //cout << "WINNNNNN " << mylocation_copy [0] << mylocation_copy [1] << mylocation_copy [2]<<endl;
                                                        return computed_locations_rtn; 
                                                }
                                        }

                                }
                        }
                }

        if (matches > 0 ) { // randomise return
                int loc =  rand() % matches;
                computed_locations [0] = results[loc][0];
                computed_locations [1] = results[loc][1];
        }
        else { // no match. return same entry given...
                computed_locations [0] = '0';
                computed_locations [1] = *mylocations; 

        }

        const char * computed_locations_rtn = computed_locations;
        /**
         * End of rework
         */

        return  computed_locations_rtn;

}

AI::~AI() {

        // clean up tasks here
        cout << "destructor works"<< endl;
}

