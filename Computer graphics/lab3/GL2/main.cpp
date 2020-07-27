#define GL_SILENCE_DEPRECATION  //эпл не любит опенгл :с
#include <GLFW/glfw3.h>
#include <stdlib.h>  //needed for exit function
#include <iostream>
#include <stdio.h>
#include <cmath>

struct circleData {
    int pointsAmount = 6;
    float** pointData;
};

void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawCylinder(float cylinderHeight, circleData circle, float cylinderRadius, circleData *massOfCircles);
void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods);
void dimetria();
circleData* init(float cylinderHeight, circleData circle, float cylinderRadius);

int rotate_y = 0;
int rotate_x = 0;
int rotate_z = 0;

float trans_x = 0;
float trans_y = 0;
float trans_z = 0;

float sc_x = 0.5;
float sc_y = 0.5;
float sc_z = 0.5;

int circlesAmount = 3;

float fi = (asin(0.625/sqrt(2.0-0.625*0.625))); //62,82
float teta = (asin(0.625/sqrt(2.0))); //41,6

GLfloat m[16] = { cos(fi), sin(fi)*sin(teta), sin(fi)*cos(teta), 0,
                  0, cos(teta), -sin(teta), 0,
                  sin(fi), -cos(fi)*sin(teta), -cos(fi)*cos(teta), 0,
                  0, 0, 0, 1
}; //как получилась матрица расписать два поворота по х, у


circleData circle;
circleData *mass;
circleData *massOfCircles;

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
    
    mass = init(1.0, circle, 0.5);
    
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
        
        glRotatef(rotate_x, 1.0, 0.0, 0.0);  //повороты подломаны???
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        glRotatef(rotate_z, 0.0, 0.0, 1.0);
        
        
        dimetria(); //проекция через повороты/ротейты
        //glMultMatrixf(m);
        
        
        glLineWidth(2);
        glColor3f(0.9,0.6, 0.3);
        glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0.7, 0.0, 0.0);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0, 0.7, 0);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0, 0, 0.7);
        glEnd();
        //drawCube();
        
        drawCylinder(1.0, circle, 0.5, mass);
        
        
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
        
        //drawCube();
        drawCylinder(1.0, circle, 0.5, mass);
        

        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

circleData* init(float cylinderHeight, circleData circle, float cylinderRadius) {
    
    circleData *massOfCircles = new circleData[circlesAmount]; //массив из 4 элементов, каждый из которых содержит кол-во точек 1 кольца и координаты хуz каждой точки
    
    for (int ii=0; ii<circlesAmount; ii++) {
        massOfCircles[ii].pointData = new float*[circle.pointsAmount];
        for (int i=0; i<circle.pointsAmount; i++)
            massOfCircles[ii].pointData[i] = new float[3];
    }
    
    
    float dh = cylinderHeight / circlesAmount;
    float dy = 0.0;
    for(int j=0; j<circlesAmount; j++) {
        
        for(int i=0; i<circle.pointsAmount; i++) { //пробег по точкам j-го круга
            float degInRad = ((3.14159*2)*i)/circle.pointsAmount;
            massOfCircles[j].pointData[i][0] = cos(degInRad)*cylinderRadius;
            massOfCircles[j].pointData[i][1] = dy+dh-0.6;
            massOfCircles[j].pointData[i][2] = sin(degInRad)*cylinderRadius;
            std::cout << massOfCircles[j].pointData[i][0] << std::endl;
            std::cout << massOfCircles[j].pointData[i][1] << std::endl;
            std::cout << massOfCircles[j].pointData[i][2] << std::endl;
        }
        dy += dh;
    }
    return massOfCircles;
}

void dimetria() {
    
    //glRotatef(180.0, 0.0, 1.0, 0.0);
    glRotatef(-fi*(180/3.14) , 1.0, 0.0, 0.0);
    glRotatef(-teta*(180/3.14) , 0.0, 1.0, 0.0);
    //glRotatef(180.0 , 0.0, 1.0, 0.0);
}

void drawCylinder(float cylinderHeight, circleData circle, float cylinderRadius, circleData *massOfCircles) {
    
    float dh = cylinderHeight / circlesAmount;
    float dy = 0.0;
    for(int j=0; j<circlesAmount; j++) {
        glBegin(GL_POLYGON);
        for(int i=0; i<circle.pointsAmount; i++) { //пробег по точкам j-го круга
            glVertex3f(massOfCircles[j].pointData[i][0], massOfCircles[j].pointData[i][1], massOfCircles[j].pointData[i][2]);
        }
        glEnd();
        dy += dh;
        
    }
    
    for (int j=0; j<circlesAmount-1; j++) {
        for (int i=0; i<circle.pointsAmount-1; i++) {
            glBegin(GL_POLYGON);
                glColor3f(0.3,  0.0,  0.7);
            glVertex3f(massOfCircles[j].pointData[i][0], massOfCircles[j].pointData[i][1], massOfCircles[j].pointData[i][2]);
                glVertex3f(massOfCircles[j].pointData[i+1][0], massOfCircles[j].pointData[i+1][1], massOfCircles[j].pointData[i+1][2]);
            
                glVertex3f(massOfCircles[j+1].pointData[i][0], massOfCircles[j+1].pointData[i][1], massOfCircles[j+1].pointData[i][2]);
            glEnd();
            
            glBegin(GL_POLYGON);
                glColor3f(0.04,  0.14,  0.6);
             glVertex3f(massOfCircles[j+1].pointData[i][0], massOfCircles[j+1].pointData[i][1], massOfCircles[j+1].pointData[i][2]);
                glVertex3f(massOfCircles[j].pointData[i+1][0], massOfCircles[j].pointData[i+1][1], massOfCircles[j].pointData[i+1][2]);
            
                glVertex3f(massOfCircles[j+1].pointData[i+1][0], massOfCircles[j+1].pointData[i+1][1], massOfCircles[j+1].pointData[i+1][2]);
            glEnd();
        }
    }
    for (int j=0; j<circlesAmount-1; j++) {
            glBegin(GL_POLYGON);
            glColor3f(0.3,  0.0,  0.7);
        glVertex3f(massOfCircles[j].pointData[circle.pointsAmount-1][0], massOfCircles[j].pointData[circle.pointsAmount-1][1], massOfCircles[j].pointData[circle.pointsAmount-1][2]);
            glVertex3f(massOfCircles[j].pointData[0][0], massOfCircles[j].pointData[0][1], massOfCircles[j].pointData[0][2]);

        
            glVertex3f(massOfCircles[j+1].pointData[circle.pointsAmount-1][0], massOfCircles[j+1].pointData[circle.pointsAmount-1][1], massOfCircles[j+1].pointData[circle.pointsAmount-1][2]);
            glEnd();
            
            glBegin(GL_POLYGON);
            glColor3f(0.04,  0.14,  0.6);
        glVertex3f(massOfCircles[j+1].pointData[circle.pointsAmount-1][0], massOfCircles[j+1].pointData[circle.pointsAmount-1][1], massOfCircles[j+1].pointData[circle.pointsAmount-1][2]);
            glVertex3f(massOfCircles[j].pointData[0][0], massOfCircles[j].pointData[0][1], massOfCircles[j].pointData[0][2]);
        
            glVertex3f(massOfCircles[j+1].pointData[0][0], massOfCircles[j+1].pointData[0][1], massOfCircles[j+1].pointData[0][2]);
            glEnd();
    }
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
    //
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //
    if (key == GLFW_KEY_C && action == GLFW_PRESS){
        circle.pointsAmount++;
        delete massOfCircles;
        delete mass;
        mass = init(1.0, circle, 0.5);
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS){
        
        circle.pointsAmount--;
        delete massOfCircles;
        delete mass;
        mass = init(1.0, circle, 0.5);

    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS){
        circlesAmount++;
        delete massOfCircles;
        delete mass;
        mass = init(1.0, circle, 0.5);

        
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS){
        glPushMatrix();
        glLoadIdentity();
        glEnable(GL_LIGHTING);
        // двухсторонний расчет освещения
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        // автоматическое приведение нормалей к
        // единичной длине
        glEnable(GL_NORMALIZE);
        
        GLfloat light1_diffuse[] = {0.4, 0.7, 0.2};
        GLfloat light1_position[] = {0.0, 0.0, 1.0, 1.0};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glPopMatrix();
    }
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

