/** Naijagame
 * Created by Olusegun Ojewale 20-03-2017.
 *
**/


#include "Scene.h"
#include "GameEngine.h"
#include <iostream>
#include <time.h>
#include <fstream>


// constructor sets window width and height
// I will make window size fixed so as not to worry about impact of resising on game display

char file_name  [] = "user.kw";

char *_file  = file_name;

void  getPositionMatrix (int positions[], int size_ , const GLfloat source_ [], GLfloat dest_ []) ;


// array stores cards postions on the board
// there are possible positions 0-8 ( i.e 1-9)
// start position is 0,1,2 - 6,7,8
int pos [] = {0,1,2,6,7,8};


// OpenGL Shaders

const GLchar* gl_Position = "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";

const GLchar* lineColor  = {"#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0",
        };

const GLchar* yellowshade = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 1.0f, 0.0f, 1.0f); // The color yellow \n"
        "}\n\0";


const GLchar* fgreenShade = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(0.0f, 1.0f, 0.0f, 1.0f); // The color green \n"
        "}\n\0";


const GLchar* fwinshade = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 0.0f, 1.0f, 0.0f); // The color \n"
        "}\n\0";


double xloc, yloc; // stores mouse x,y locations

// markers for moving cards from a source to a destination. The two values must be greater than -1 before a move can happen
int destinationPosition = -1;
int sourcePosition =  -1;


// matrix for possible 9 points on the board
GLfloat cardsMatrix[] = {

        // top left 1
        -0.8f, 0.8f, 0.0f,
        -0.8f, 0.6f, 0.0f,
        -0.6f, 0.6f, 0.0f,
        -0.8f, 0.8f, 0.0f,
        -0.6f, 0.8f, 0.0f,
        -0.6f, 0.6f, 0.0f,

        // top middle 2
        -0.1f, 0.8f, 0.0f,
        0.1f, 0.8f, 0.0f,
        0.1f, 0.6f, 0.0f,
        -0.1f, 0.8f, 0.0f,
        -0.1f, 0.6f, 0.0f,
        0.1f, 0.6f, 0.0f,

        // top right 3
        0.8f, 0.8f, 0.0f,
        0.6f, 0.8f, 0.0f,
        0.6f, 0.6f, 0.0f,
        0.8f, 0.8f, 0.0f,
        0.8f, 0.6f, 0.0f,
        0.6f, 0.6f, 0.0f,

        // mddile left 4
        -0.8f, 0.1f, 0.0f,
        -0.6f, 0.1f, 0.0f,
        -0.6f, -0.1f, 0.0f,
        -0.8f, 0.1f, 0.0f,
        -0.8f, -0.1f, 0.0f,
        -0.6f, -0.1f, 0.0f,
        //  middle 5
        -0.1f, 0.1f, 0.0f,
        0.1f, 0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        -0.1f, 0.1f, 0.0f,
        -0.1f, -0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,

        // middle right 6
        0.8f, 0.1f, 0.0f,
        0.6f, 0.1f, 0.0f,
        0.6f, -0.1f, 0.0f,
        0.8f, 0.1f, 0.0f,
        0.8f, -0.1f, 0.0f,
        0.6f, -0.1f, 0.0f,

        // bottom left 7
        -0.8f, -0.8f, 0.0f,
        -0.8f, -0.6f, 0.0f,
        -0.6f, -0.6f, 0.0f,
        -0.8f, -0.8f, 0.0f,
        -0.6f, -0.8f, 0.0f,
        -0.6f, -0.6f, 0.0f,

        //  middle bottom 8
        -0.1f, -0.8f, 0.0f,
        0.1f, -0.8f, 0.0f,
        0.1f, -0.6f, 0.0f,
        -0.1f, -0.8f, 0.0f,
        -0.1f, -0.6f, 0.0f,
        0.1f, -0.6f, 0.0f,


        // bottom right 9
        0.8f, -0.6f, 0.0f,
        0.6f, -0.6f, 0.0f,
        0.6f, -0.8f, 0.0f,
        0.8f, -0.6f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.6f, -0.8f, 0.0f,

};


GLfloat scoreMatrix [] = {

        // bottom score counter
        // first
        -0.08f, -0.93f, 0.0f,
        -0.06f, -0.9f, 0.0f,
        -0.04f, -0.93f, 0.0f,

        // second
        0.00f, -0.93f, 0.0f,
        0.02f, -0.9f, 0.0f,
        0.04f, -0.93f, 0.0f,

        // third
        0.08f, -0.93f, 0.0f,
        0.10f, -0.9f, 0.0f,
        0.12f, -0.93f, 0.0f,



        // top score counter
        -0.08f, 0.9f, 0.0f,
        -0.06f, 0.93f, 0.0f,
        -0.04f, 0.9f, 0.0f,

        // second
        0.00f, 0.9f, 0.0f,
        0.02f, 0.93f, 0.0f,
        0.04f, 0.9f, 0.0f,

        // third
        0.08f, 0.9f, 0.0f,
        0.10f, 0.93f, 0.0f,
        0.12f, 0.9f, 0.0f,
};

GLfloat indicatorMatrix [] = {

        0.90, 0.00f, 0.0f,
        0.96f,0.06f, 0.0f,
        0.96f, -0.06f, 0.0f,

};

GLfloat boardMatrix[] = {

        // diagonal 1 left to right                                                         
         -0.7f, -0.7f, 0.0f,
         0.7f, 0.7f, 0.0f,  
                                       
        // diagonal 2 right to left
         -0.7f, 0.7f, 0.0f,
         0.7f, -0.7f, 0.0f, 
                                       
         // middle horizontal line
         0.7f, 0.0f, 0.0f,
         -0.7f,-0.0f, 0.0f, 

         // vertical middle line
         0.0f, 0.7f, 0.0f,
         0.0f, -0.7f, 0.0f, 

         // veritcal left line 
         -0.7f, 0.7f, 0.0f,
         -0.7f, -0.7f, 0.0f,

         // horizontal top line
         -0.7f, 0.7f, 0.0f,
         0.7f, 0.7f, 0.0f, 

         // veritcal right line
         0.7f, -0.7f, 0.0f, 
         0.7f, 0.7f, 0.0f, 

         // horizontal bottom line                                                          
         -0.7f, -0.7f, 0.0f,
         0.7f, -0.7f, 0.0f, 
}; 


GLfloat cardsPositions [6*18]; // this is used to manage how cards are rendered. It uses 6 spots from possible 9 postions

bool UPDATE_NOW = false;

bool IN_PLAY = true;  //flag to control game interraction

int awinner =  0; // variable to decide of there is a winner . 0 for no winner, 1 if player 1 wins and 2 if its player 2


// shaders
enum { LINE_POSITION, PLAYER1_POSITION, PLAYER2_POSITION, WIN_POSITION, TOGGLE_SHADER };
GLuint gameShaders [5];//Program, gameShaders [PLAYER1_POSITION], gameShaders [PLAYER2_POSITION],gameShaders [WIN_POSITION], gameShaders [TOGGLE_SHADER];
GLuint fragmentsShaders [4];

// couple sof functions definition

/**
 *getPositionMatrix is used  to
 */
void  getPositionMatrix (int positions[], int size_ , const GLfloat source_ [], GLfloat dest_ []) ;

/**
 *areamatch function check if mouse x,y location is an 'action' point
 * for instance, is there a card in the location? Is location a 'vertex'  etc?
 */

int areamatch  (double xaxis, double yaxis );

/**
 *Update card position. Card has moved from postion A to B. There are 9 possible postions, numbered 0..8
**/

void  update (int positions[] , int a, int b);

int getArrayIndexForAvalue (const int _array [], int _value );

/**
 *areYouOnYourCard function is to ensure Player 1cannot move layerr 2 cards.
 */

bool areYouOnYourCard (int player, int _position);

/**
 *Flowmanager controls game flow..
 * */
void flowmanager ( double x, double y);

// sleepcp is platform independent way of implementing a 'sleep'
void sleepcp(int milliseconds);


void initiateAImove ();

// initalise Game
GameEngine game;

Scene::Scene (int WindowWidth, int WindowHeigth, char * title) {
        this -> wWidth  = WindowWidth;
        this -> wHeight = WindowHeigth;
        this -> title   = title;
}
// perform Opengl intialization functions here
//
GLFWwindow* Scene::initWindow(const int resX, const int resY, const char * title) {
        // Init GLFW
        glfwInit();
        // Set all the required options for GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Create a GLFWwindow object that we can use for GLFW's functions
        GLFWwindow* window = glfwCreateWindow(resX, resY, title, nullptr, nullptr);
        glfwMakeContextCurrent(window);

        // Set the required callback functions
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_callback);

        // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
        glewExperimental = GL_TRUE;
        // Initialize GLEW to setup the OpenGL Function pointers
        glewInit();

        // Define the viewport dimensions
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        return window;
}

void Scene::init () {

        // Build and compile our shader program
        // // Vertex shader
        this -> appWindow =  initWindow (wWidth, wHeight, title);

        GLuint fragment_Gl_Position = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(fragment_Gl_Position, 1, &gl_Position, NULL);
        glCompileShader(fragment_Gl_Position);
        // Check for compile time errors
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(fragment_Gl_Position, GL_COMPILE_STATUS, &success);

        fragmentsShaders [LINE_POSITION] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentsShaders [LINE_POSITION], 1, &lineColor, NULL);
        glCompileShader(fragmentsShaders [LINE_POSITION]);
        // Check for compile time errors
        glGetShaderiv(fragmentsShaders [LINE_POSITION], GL_COMPILE_STATUS, &success);


        // Fragment2 shader
        fragmentsShaders [PLAYER1_POSITION] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentsShaders [PLAYER1_POSITION], 1, &fgreenShade, NULL);
        glCompileShader(fragmentsShaders [PLAYER1_POSITION]);
        // Check for compile time errors
        glGetShaderiv(fragmentsShaders [PLAYER1_POSITION], GL_COMPILE_STATUS, &success);


        // Fragment2 shader
        fragmentsShaders [PLAYER2_POSITION] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentsShaders [PLAYER2_POSITION], 1, &yellowshade, NULL);
        glCompileShader(fragmentsShaders [PLAYER2_POSITION]);
        // Check for compile time errors
        glGetShaderiv(fragmentsShaders [PLAYER2_POSITION], GL_COMPILE_STATUS, &success);


        // win  shader
        fragmentsShaders [WIN_POSITION] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentsShaders [WIN_POSITION], 1, &fwinshade, NULL);
        glCompileShader(fragmentsShaders [WIN_POSITION]);
        // Check for compile time errors
        glGetShaderiv(fragmentsShaders [WIN_POSITION], GL_COMPILE_STATUS, &success);


        // Link shaders
        gameShaders [LINE_POSITION] = glCreateProgram();
        glAttachShader(gameShaders [LINE_POSITION], fragment_Gl_Position);
        glAttachShader(gameShaders [LINE_POSITION], fragmentsShaders [LINE_POSITION]);
        glLinkProgram(gameShaders [LINE_POSITION]);

        gameShaders [PLAYER1_POSITION] = glCreateProgram();
        glAttachShader(gameShaders [PLAYER1_POSITION], fragment_Gl_Position);
        glAttachShader(gameShaders [PLAYER1_POSITION], fragmentsShaders [PLAYER1_POSITION]);
        glLinkProgram(gameShaders [PLAYER1_POSITION]);


        gameShaders [PLAYER2_POSITION] = glCreateProgram();
        glAttachShader(gameShaders [PLAYER2_POSITION], fragment_Gl_Position);
        glAttachShader(gameShaders [PLAYER2_POSITION], fragmentsShaders [PLAYER2_POSITION]);
        glLinkProgram(gameShaders [PLAYER2_POSITION]);


        gameShaders [WIN_POSITION] = glCreateProgram();
        glAttachShader(gameShaders [WIN_POSITION], fragment_Gl_Position);
        glAttachShader(gameShaders [WIN_POSITION], fragmentsShaders [WIN_POSITION]);
        glLinkProgram(gameShaders [WIN_POSITION]);

        glDeleteShader(fragment_Gl_Position);
        glDeleteShader(fragmentsShaders [LINE_POSITION]);
        glDeleteShader(fragmentsShaders [PLAYER1_POSITION]);
        glDeleteShader(fragmentsShaders [PLAYER2_POSITION]);
        glDeleteShader(fragmentsShaders [WIN_POSITION]);

        return;
}

void Scene::aWin(int i) {

        IN_PLAY = false;
}

void Scene::start() {

        int workcounter = 0; // this is used to animate a win
        const int INDICATOR_INDEX = 3; // used as VBO VAO index value for 'indicator' arrow- who's playing next

        GLuint VBO[4], VAO[4];
        const int POINTS = 16;

        //pointer to store score count...
        int * playscore;

        glGenVertexArrays(4, VAO);
        glGenBuffers(4, VBO);

        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO [LINE_POSITION]);

        getPositionMatrix (pos, 2 , cardsMatrix, cardsPositions);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(boardMatrix), boardMatrix, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
        glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframes only
        
        // triangle
        glBindVertexArray(VAO [PLAYER1_POSITION]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER,6*72, cardsPositions, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
        glBindVertexArray(1); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


        // score
        glBindVertexArray(VAO [PLAYER2_POSITION]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(scoreMatrix), scoreMatrix, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
        glBindVertexArray(2); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


        // indicator
        glBindVertexArray(VAO[3]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(indicatorMatrix), indicatorMatrix, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
        glBindVertexArray(2); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)




        // Game loop
        gameShaders [TOGGLE_SHADER] = gameShaders [PLAYER2_POSITION];
    while (!glfwWindowShouldClose(appWindow))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        workcounter ++;
        if ( workcounter  > 2) workcounter = 0; // reset 

        //if (IN_PLAY)  glfwPollEvents(); // only allow user event when play is on
        glfwPollEvents(); // capture user events ... mouse move, keypress etc


        if (IN_PLAY || UPDATE_NOW) {
                UPDATE_NOW  = false;
                getPositionMatrix (pos, 2 , cardsMatrix, cardsPositions);

                glBindVertexArray(VAO [PLAYER1_POSITION]);

                glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
                glBufferData(GL_ARRAY_BUFFER,6*72, cardsPositions, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
                glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

                // check if its a win
                awinner =  game.aWin (pos);
                if (awinner > 0 )  IN_PLAY = false;// if a win , suspend play
        }

        // if there is a winner then animate
        // sleep for 1 second and flash color change
        if (!IN_PLAY ) {
                 sleepcp(500);
                 if  (workcounter == 1) { 
                         if (awinner == 1) gameShaders [TOGGLE_SHADER] = gameShaders [PLAYER2_POSITION];
                         if (awinner == 2) gameShaders [TOGGLE_SHADER] = gameShaders [PLAYER1_POSITION];

                }
                        
                 else
                         gameShaders [TOGGLE_SHADER] = gameShaders [WIN_POSITION];
        }


        // get play scores...
        game.getscores (playscore);


        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw  lines
        glUseProgram(gameShaders [LINE_POSITION]);
        glBindVertexArray(VAO [LINE_POSITION]);
        glDrawArrays( GL_LINES, 0, POINTS);
        glBindVertexArray(0);

        //draw 3 playing caards
        // flash color change if there is a win
        if (awinner == 2)
                glUseProgram(gameShaders [TOGGLE_SHADER]);
        else
                glUseProgram(gameShaders [PLAYER1_POSITION]);

        glBindVertexArray(VAO [PLAYER1_POSITION]);
        glDrawArrays( GL_TRIANGLES, 18, 6*3);
        glBindVertexArray(0);


        // show score for player A 
        glBindVertexArray(VAO [PLAYER2_POSITION]);
        glDrawArrays( GL_TRIANGLES, 0, 3* playscore [0]);
        glBindVertexArray(2);

        // flash color change if there is a win
        if (awinner == 1)
                glUseProgram(gameShaders [TOGGLE_SHADER]);
        else
                glUseProgram(gameShaders [PLAYER2_POSITION]);

        glBindVertexArray(VAO [PLAYER1_POSITION]);
        glDrawArrays( GL_TRIANGLES, 0, 6*3);
        glBindVertexArray(0);

        // show score for player B
        glBindVertexArray(VAO [PLAYER2_POSITION]);
        glDrawArrays( GL_TRIANGLES, 9, 3* playscore [1]);
        glBindVertexArray(2);


        if (IN_PLAY ) { // only show indicator arrow when game is in play
                if (game.whoson() == 1)
                        glUseProgram(gameShaders [PLAYER2_POSITION]);
                else
                        glUseProgram(gameShaders [PLAYER1_POSITION]);

                glBindVertexArray(VAO[INDICATOR_INDEX]);
                glDrawArrays( GL_TRIANGLES, 0, 3);
                glBindVertexArray(3);
        }

        // Swap the screen buffers
        glfwSwapBuffers(appWindow);


        // check if auto AI is enabled and if computer can play
        if (IN_PLAY) initiateAImove();
    }
        // clean up
        glDeleteVertexArrays(4, VAO);
        glDeleteBuffers(4, VBO);
}


// Is called whenever a key is pressed/released via GLFW
void Scene::mouse_callback(GLFWwindow* window, int button,  int action, int mode)
{
        if (!IN_PLAY) return;

        glfwGetCursorPos(window, &xloc, &yloc); // get clicked x,y location

        if (button == 0 && action == 0) {  // respond to only single,left click
                flowmanager (xloc,yloc);
                // sleepcp(3000);
                flowmanager (xloc,yloc);
        } 

}

// called whenever a key is pressed/released via GLFW
void Scene::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
        //std::cout << key << std::endl;
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

        if (!IN_PLAY) {

            // a win detected.. reset game on key presss
            game.reset();

            // reset card postions too
            //correct 
            pos [0] = 0;
            pos [1] = 1;
            pos [2] = 2;
            pos [3] = 6;
            pos [4] = 7;
            pos [5] = 8;

            IN_PLAY = true; // set flag to enable game  start/continuation
        }

}


void getPositionMatrix (int positions[], int size_ , const GLfloat source_ [], GLfloat rtn_ []) {
        int m = 0;

        for (int i = 0; i < 6 ; ++ i) {
                int j = positions [i];
                for (int k = ( j * 18); k < ( j * 18) + 18; ++k ) {
                        rtn_ [m++] = source_ [k];
                }
        }
        return ;
}

void  update (int positions[] , int a, int b) {
        for (int i =0 ; i < 6; ++i )
        {
                if (positions [i] == a) {
                        positions [i] = b;
                        return;
                }
        }
}

int areamatch  (double xaxis, double yaxis ) {

        //std::cout << "area match is on" <<std::endl;

        if ((xaxis < 300 ) && ( xaxis > 100) && (yaxis < 190) && ( yaxis > 50))
                return 1;

        if ((xaxis < 300 ) && ( xaxis > 100) && (yaxis < 450) && ( yaxis > 350))
                return 4;

        if ((xaxis < 800 ) && ( xaxis > 600) && (yaxis < 190) && ( yaxis > 50))
                return 2;


        if ((xaxis < 800 ) && ( xaxis > 600) && (yaxis < 450) && ( yaxis > 350))
                return 5;

        if ((xaxis < 1300 ) && ( xaxis > 1100) && (yaxis < 190) && ( yaxis > 50))
                return 3;

        if ((xaxis < 1300 ) && ( xaxis > 1100) && (yaxis < 450) && ( yaxis > 350))
                return 6;

        if ((xaxis < 300 ) && ( xaxis > 100) && (yaxis < 700) && ( yaxis > 600))
                return 7;

        if ((xaxis < 800 ) && ( xaxis > 600) && (yaxis < 700) && ( yaxis > 600))
                return 8;

        if ((xaxis < 1300 ) && ( xaxis > 1100) && (yaxis < 700) && ( yaxis > 600))
                return 9;

        return 0;
}

int getArrayIndexForAvalue (const int _array [], int _value ) {
        for (int i = 0; i < 6;  ++i) {
                if (_array [i] == _value ) {
                        return i;
                }
        }
}

bool areYouOnYourCard (int player , int _position) {
        if ((player == 1) && (getArrayIndexForAvalue ( pos, _position) < 3 )) {
                return true;
        }

        if ((player == 0) && (getArrayIndexForAvalue ( pos, _position) > 2 )) {
                return true;
        }

        return false;
        
}

void flowmanager (double xloc, double yloc) {

        int allocation = areamatch ( xloc,  yloc) -1 ;
        bool A_LOC_SET = false;

        //std::cout << "who is playing??..." << game.isCurrentPlayerHuman();

        if (allocation > -1 && game.isCurrentPlayerHuman ()) {

                int pos_copy [9];

                for (int i =0 ; i < 6; ++i )
                {
                        if (pos [i] == allocation) {
                                sourcePosition =  allocation;
                                A_LOC_SET  = true;
                        }

                        pos_copy [i] = pos [i];
                }


                if (!(A_LOC_SET) && sourcePosition > -1)
                   destinationPosition = allocation;

                if  (( sourcePosition > -1) && (destinationPosition > -1) &&
                           (game.validatemove(sourcePosition + 1, destinationPosition + 1 ))  && (areYouOnYourCard (game.whoson(),sourcePosition) ))
                {
                   //std::cout << "settting  now!! " << std::endl;

                   update (pos, sourcePosition,destinationPosition);
                   destinationPosition = -1;
                   sourcePosition = -1;
                   UPDATE_NOW = true;

                   // add updated user move
                   pos_copy [6] = pos [3];
                   pos_copy [7] = pos [4];
                   pos_copy [8] = pos [5];

                   // capture move to storage  
                   game.capturemove ( _file,pos_copy);  
                   game.nextPlay();

                }

        }
        //std::cout << "ALOC: " <<sourcePosition << " BLOC: "<< destinationPosition<< " allocation " << allocation<< std::endl;
}

//void Scene::initiateAImove () {
void initiateAImove () {
        if (! game.isCurrentPlayerHuman ()) {

           // is computer is playing
           game.compute_AI_NextMove(1,pos);

           sleepcp(3000);// wait for 3 seconds before rendering play

           UPDATE_NOW = true; // set update flag
           game.nextPlay();
        }
}


void sleepcp(int milliseconds) // cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
            // do nothing
    }
}
