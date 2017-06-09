/** Naijagame
 * Created by Olusegun Ojewale 20-03-2017.
 *
**/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;

class AI {
public:
        // constructor
        AI ();
        
        //Destructor
        ~ AI ();

        //methods
        void setLevel(int );
        const char * computemove (const char *, const char * , bool checkwin);

private:
        int intelligenceLevel = 1;

};

