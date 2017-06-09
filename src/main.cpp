/** Naijagame
 * Created by Olusegun Ojewale 20-03-2017.
 *
**/

#include "Scene.h"
#include <iostream>
#include <string>
#include <stdio.h>

int main ( int argc, char *argv[] ) {
        
        std::string title_ = "Naija Game";
        char * title = &title_[0];

        Scene gameScene(1400,800, title);
        gameScene.init();
        gameScene.start();
}

