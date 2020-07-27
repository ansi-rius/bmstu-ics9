#define GL_SILENCE_DEPRECATION  //эпл не любит опенгл :с
#include <GLFW/glfw3.h>
#include <stdlib.h>  //needed for exit function
#include <iostream>
#include <stdio.h>
#include <cmath>

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
void cursorEnterCallback(GLFWwindow *window, int entered);
void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

float red = 0.0;
float radius = 0.3;
bool ballRight = true;
bool ballDown = true;
int accept = 0;

float x = 0.5;
float y = -0.33;
float speed = 0.03;

int main(void) {
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(480, 480, "Opengl ex", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    //
    glfwSetCursorPosCallback(window, cursorPositionCallback );
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    glfwSetKeyCallback( window, keyCallback);
    
    //
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    const float DEG2RAD = 3.14159 / 180;
    
    //float r = 0.0;
    float green = 0.3;
    float blue = 0.6;
    
    while(!glfwWindowShouldClose(window)) {
        //Setup view
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glDisable( GL_DEPTH_TEST );
        glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //Movement
        if (accept==1) {
            glfwPollEvents();
            continue;
        }
        if (ballRight) {
            if (x > -1 + radius) {
                x -= speed;
            }
            else {
                ballRight = false;
            }
        }
        else {
            if(x < 1 - radius) {
                x += speed;
                //r = fmod(r + 0.0001, 1);
            }
            else {
                ballRight = true;
                //r = fmod(r + 0.0001, 1);
            }
        }
        if (ballDown) {
            if (y > -1 + radius) {
                y -= speed;
                //r = fmod(r + 0.0001, 1);
            }
            else {
                ballDown = false;
            }
        }
        else {
            if(y < 1 - radius) {
                y += speed;
                //r = fmod(r + 0.0001, 1);
            }
            else {
                ballDown = true;
            }
        }
        
        //Color
        //r = fmod(r + 0.01, 1);
        //g = fmod(g + 0.02, 1);
        //b = fmod(b + 0.03, 1);
        //Drawing
        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
        for(int i = 0; i <360; i++) {
            float degInRad = i * DEG2RAD;
            glVertex2f((cos(degInRad)*radius) + x, (sin(degInRad)*radius) + y);
        }
        glEnd();
        
        //Swap buffer and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate;
    exit(EXIT_SUCCESS);
}

static void cursorPositionCallback( GLFWwindow *window, double xPos, double yPos) {
    //std::cout << xPos << " : " << yPos << std::endl;
}

void cursorEnterCallback(GLFWwindow *window, int entered) {
    if (entered) {
        std::cout << "Entrd" << std::endl;
    }
    else {
        std::cout << "Left" << std::endl;
    }
}

void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        std::cout << "Right button pressed" << std::endl;
        red = fmod(red + 0.1, 1);
        radius += 0.05;
    }
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        std::cout << "Right button released" << std::endl;
        radius -= 0.05;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Left button pressed" << std::endl;
        
        ballRight = !ballRight;
        ballDown = !ballDown;
        radius += 0.05;
        
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        std::cout << "Left button released" << std::endl;
        radius -= 0.05;
    }
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        accept++;
        accept%=2;
    }
}
