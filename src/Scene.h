/** Naijagame
 * Created by Olusegun Ojewale 20-03-2017.
 *
**/

#include <iostream>
#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Scene {
        public:
                Scene(int windowWidth, int windowHeight, char *  title) ;
                void init ();
                void  start ();
                void  aWin (int i = 0);
                //void initiateAImove ();
                void  end ();
        private:
                static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
                static void mouse_callback(GLFWwindow* window, int button,  int action, int mode);
                GLFWwindow* initWindow(const int resX, const int resY,const char * title);
                
                int wWidth;
                int wHeight;
                char * title;
                GLFWwindow * appWindow;
};
