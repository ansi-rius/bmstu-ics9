#define GL_SILENCE_DEPRECATION  //эпл не любит опенгл :с
#include <GLFW/glfw3.h>
#include <stdlib.h>  //needed for exit function
#include <iostream>
#include <stdio.h>
#include <cmath>

void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawCube();
void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods);
void dimetria();

int rotate_y = 0;
int rotate_x = 0;
int rotate_z = 0;

float trans_x = 0;
float trans_y = 0;
float trans_z = 0;

float sc_x = 0.5;
float sc_y = 0.5;
float sc_z = 0.5;

float fi = (asin(0.625/sqrt(2.0-0.625*0.625))); //62,82
float teta = (asin(0.625/sqrt(2.0))); //41,6

GLfloat m[16] = { cos(fi), sin(fi)*sin(teta), sin(fi)*cos(teta), 0,
                  0, cos(teta), -sin(teta), 0,
                  sin(fi), -cos(fi)*sin(teta), -cos(fi)*cos(teta), 0,
                  0, 0, 0, 1
}; //как получилась матрица расписать два поворота по х, у

int main(int argc, char const *argv[]) {
    
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    
    //glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(620, 620, "Rorate Cube", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        
        glfwSetKeyCallback(window, keyboard_callback);
        
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //вращение
        
        glTranslatef(0.4, 0.4, 0.4);
        glTranslatef(trans_x, trans_y, trans_z);
        
        glScalef(sc_x, sc_y, sc_z);
        
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        glRotatef(rotate_z, 0.0, 0.0, 1.0);
        
        dimetria(); //проекция через повороты/ротейты
        //glMultMatrixf(m);
        
        drawCube();
        
        
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        
        glTranslatef(-0.6, -0.4, -0.6);
        
        glScalef(0.2, 0.2, 0.2);
        //
        //glRotatef(15, 0.0, -1.0, 0.0);
        //glRotatef(15, -1.0, 0.0, 0.0);
        //
        //dimetria();
        glMultMatrixf(m); //проекция через формулу с лекции
        
        drawCube();
        

        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}


void dimetria() {
    
    //glRotatef(180.0, 0.0, 1.0, 0.0);
    glRotatef(-fi*(180/3.14) , 1.0, 0.0, 0.0);
    glRotatef(-teta*(180/3.14) , 0.0, 1.0, 0.0);
    //glRotatef(180.0 , 0.0, 1.0, 0.0);
}

void drawCube() {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON); // red side - FRONT
        glColor3f(1.0,  0.0,  0.0);
    glVertex3f( 0.4, -0.4, -0.4);
    glVertex3f( 0.4,  0.4, -0.4);
        glColor3f(0.6,  0.6,  0.3);
    glVertex3f(-0.4,  0.4, -0.4);
    glVertex3f(-0.4, -0.4, -0.4);
    glEnd();
    
    glBegin(GL_POLYGON); // green side - BACK
        glColor3f(0.01,  1.0, 0.8);
    glVertex3f( 0.4, -0.4, 0.4);
    glVertex3f( 0.4,  0.4, 0.4);
        glColor3f(0.09,  0.56, 0.21);
    glVertex3f(-0.4,  0.4, 0.4);
    glVertex3f(-0.4, -0.4, 0.4);
    glEnd();
    
    glBegin(GL_POLYGON); // blue side - RIGHT
        glColor3f(0.04,  0.14,  0.6);
    glVertex3f(0.4, -0.4, -0.4);
    glVertex3f(0.4,  0.4, -0.4);
        glColor3f(1.0,  0.0,  1.0);
    glVertex3f(0.4,  0.4,  0.4);
    glVertex3f(0.4, -0.4,  0.4);
    glEnd();
    
    glBegin(GL_POLYGON); // orange side - LEFT
        glColor3f(0.8,  0.9,  0.04);
    glVertex3f(-0.4, -0.4,  0.4);
    glVertex3f(-0.4,  0.4,  0.4);
        glColor3f(0.9,  0.4,  0.02);
    glVertex3f(-0.4,  0.4, -0.4);
    glVertex3f(-0.4, -0.4, -0.4);
    glEnd();
    
    glBegin(GL_POLYGON); // ppl side - TOP
        glColor3f(0.3,  0.0,  0.7);
    glVertex3f( 0.4,  0.4,  0.4);
    glVertex3f( 0.4,  0.4, -0.4);
        glColor3f(0.7,  0.3,  0.9);
    glVertex3f(-0.4,  0.4, -0.4);
    glVertex3f(-0.4,  0.4,  0.4);
    glEnd();
    
    glBegin(GL_POLYGON); // Red side - BOTTOM
        glColor3f(1.0,  0.9,  0.2);
    glVertex3f( 0.4, -0.4, -0.4);
    glVertex3f( 0.4, -0.4,  0.4);
        glColor3f(0.8,  0.9,  0.5);
    glVertex3f(-0.4, -0.4,  0.4);
    glVertex3f(-0.4, -0.4, -0.4);
    glEnd();
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        rotate_x += 5;
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        rotate_x -= 5;
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        rotate_y -= 5;
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        rotate_y += 5;
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
        rotate_z -= 5;
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        rotate_z += 5;
    
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        trans_y += 0.05;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        trans_x -= 0.05;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        trans_x += 0.05;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        trans_y -= 0.05;
   // boolean
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //
}

void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        std::cout << fi << std::endl;
        sc_x += 0.2;
        sc_y += 0.2;
        //sc_z += 0.2;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (sc_x > 0.2 && sc_y > 0.2) {
            std::cout << teta << std::endl;
            sc_x -= 0.2;
            sc_y -= 0.2;
            //sc_z -= 0.2;
        }
    }
}

