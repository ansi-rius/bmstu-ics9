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

struct point {
    float xx;
    float yy;
    float zz;
};

struct line {
    float xx1;
    float yy1;
    float zz1;
    float xx2;
    float yy2;
    float zz2;
};

void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawCylinder(float cylinderHeight, circleData circle, float cylinderRadius, circleData *massOfCircles);
void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods);
void dimetria();
circleData* init(float cylinderHeight, circleData circle, float cylinderRadius);
void cyrus_back(line mainLine, circleData *massOfCircles);

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

bool cyrus = false;

GLfloat m[16] = { cos(fi), sin(fi)*sin(teta), sin(fi)*cos(teta), 0,
    0, cos(teta), -sin(teta), 0,
    sin(fi), -cos(fi)*sin(teta), -cos(fi)*cos(teta), 0,
    0, 0, 0, 1
}; //как получилась матрица расписать два поворота по х, у


circleData circle;
circleData *mass;
circleData *massOfCircles;
line mainLine;
point p1;
point p2;

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
    
    scanf("%f",&mainLine.xx1);
    scanf("%f",&mainLine.yy1);
    scanf("%f",&mainLine.zz1);

    scanf("%f",&mainLine.xx2);
    scanf("%f",&mainLine.yy2);
    scanf("%f",&mainLine.zz2);
    /*
    mainLine.xx1 = -1.0; // -1.0 -0.2 -0.9 0.9 0.6 0.5
    mainLine.yy1 = -0.2;
    mainLine.zz1 = -0.9;
    mainLine.xx2 = 0.9;
    mainLine.yy2 = 0.6;
    mainLine.zz2 = 0.5;
    
    mainLine.xx1 = 0.9; // 0.9 0.9 -0.1 0.5 -0.9 0.5
    mainLine.yy1 = 0.9; //1.0 0.0 0.0 0.0 0.0 0.0
    mainLine.zz1 = -0.1;
    mainLine.xx2 = 0.5;
    mainLine.yy2 = -0.9;
    mainLine.zz2 = 0.5;*/
    
    cyrus_back(mainLine, mass);
    
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
        
        glTranslatef(0.0, 0.0, 0.0);
        
        glScalef(sc_x, sc_y, sc_z);
        
        glRotatef(rotate_x, 1.0, 0.0, 0.0);  //повороты подломаны???
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        glRotatef(rotate_z, 0.0, 0.0, 1.0);
        
        //drawLine();
        //drawCylinder(1.0, circle, 0.2, mass);
        
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
        
        glTranslatef(trans_x, trans_y, trans_z);
        glTranslatef(0.0, 0.0, 0.0);
        glLineWidth(4);
        
        if (!cyrus) {
            glBegin(GL_LINES); // red side - FRONT
            glColor3f(1.0,  0.0,  0.0);
            glVertex3f( mainLine.xx1, mainLine.yy1, mainLine.zz1);
            glVertex3f( mainLine.xx2, mainLine.yy2, mainLine.zz2);
            glEnd();
        } else
            if (cyrus) {
                glTranslatef(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // red side - FRONT
                glColor3f(0.0,  0.0,  1.0);
                glVertex3f( p1.xx, p1.yy, p1.zz);
                glVertex3f( p2.xx, p2.yy, p2.zz);
                glEnd();
            }
        
        //dimetria(); //проекция через повороты/ротейты
        //glMultMatrixf(m);
        glLoadIdentity();
        glScalef(sc_x, sc_y, sc_z);
        
        glRotatef(rotate_x, 1.0, 0.0, 0.0);  //повороты подломаны???
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        glRotatef(rotate_z, 0.0, 0.0, 1.0);
        
        glTranslatef(trans_x, trans_y, trans_z);
        
        //drawCube();*/
        glTranslatef(0.0, 0.0, 0.0);
        drawCylinder(1.0, circle, 0.5, mass);
        
        
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void cyrus_back(line mainLine,circleData *massOfCircles) {
    int k = circle.pointsAmount + 2; //8
    float x1, x2, x3, y1, y2, y3, z1, z2, z3;
    point normals[k];
    point f[k]; //точка, лежащая на i-ой плоскости
    point w[k];
    float d_scalar;
    float w_scalar;
    float t_down = 0;
    float t_up = 1;
    float t;
    float A,B,C,D;
    
    point directr;
    directr.xx = mainLine.xx2 - mainLine.xx1;
    directr.yy = mainLine.yy2 - mainLine.yy1;
    directr.zz = mainLine.zz2 - mainLine.zz1;
    float minX=0, maxX=0, minY=0, maxY=0, minZ=0, maxZ=0;
    //нормали боковых граней
    for (int i=0; i<k-2; i++) {
        x1 = massOfCircles[0].pointData[i][0];
        y1 = massOfCircles[0].pointData[i][1];
        z1 = massOfCircles[0].pointData[i][2];
        
        x2 = massOfCircles[0].pointData[i+1][0];
        y2 = massOfCircles[0].pointData[i+1][1];
        z2 = massOfCircles[0].pointData[i+1][2];
        
        
        x3 = massOfCircles[circlesAmount-1].pointData[i][0];
        y3 = massOfCircles[circlesAmount-1].pointData[i][1];
        z3 = massOfCircles[circlesAmount-1].pointData[i][2];
        
        minX = fmin(minX, x1);
        minX = fmin(minX, x2);
        maxX = fmax(maxX, x1);
        maxX = fmax(maxX, x2);
        
        minY = fmin(minY, y1);
        minY = fmin(minY, y3);
        maxY = fmax(maxY, y1);
        maxY = fmax(maxY, y3);
        
        minZ = fmin(minZ, z1);
        minZ = fmin(minZ, z2);
        maxZ = fmax(maxZ, z1);
        maxZ = fmax(maxZ, z2);
        
        A = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
        B = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
        C = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
        D = x1*(y2*z3-y3*z2) + x2*(y3*z1-y1*z3) + x3*(y1*z2-y2*z1);
        
//        if (D/A < 0) {
            normals[i].xx = A;
            normals[i].yy = B;
            normals[i].zz = C;
//        } else {
//            normals[i].xx = -A;
//            normals[i].yy = -B;
//            normals[i].zz = -C;
//        }
        
        f[i].xx = x1;
        f[i].yy = y1;
        f[i].zz = z1;
    }
    //нормаль дна
    x1 = massOfCircles[0].pointData[0][0];
    y1 = massOfCircles[0].pointData[0][1];
    z1 = massOfCircles[0].pointData[0][2];
    
    x2 = massOfCircles[0].pointData[1][0];
    y2 = massOfCircles[0].pointData[1][1];
    z2 = massOfCircles[0].pointData[1][2];
    
    x3 = massOfCircles[0].pointData[2][0];
    y3 = massOfCircles[0].pointData[2][1];
    z3 = massOfCircles[0].pointData[2][2];
    
    A = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    B = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    C = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    D = x1*(y2*z3-y3*z2) + x2*(y3*z1-y1*z3) + x3*(y1*z2-y2*z1);
    
    if (D/B > 0) {
        normals[k-2].xx = A;
        normals[k-2].yy = B;
        normals[k-2].zz = C;
    } else {
        std::cout << "nize nula dno" << std::endl;
        normals[k-2].xx = -A;
        normals[k-2].yy = -B;
        normals[k-2].zz = -C;
    }
    
    f[k-2].xx = x1;
    f[k-2].yy = y1;
    f[k-2].zz = z1;
    //нормаль крышки
    x1 = massOfCircles[circlesAmount-1].pointData[0][0];
    y1 = massOfCircles[circlesAmount-1].pointData[0][1];
    z1 = massOfCircles[circlesAmount-1].pointData[0][2];
    
    x2 = massOfCircles[circlesAmount-1].pointData[1][0];
    y2 = massOfCircles[circlesAmount-1].pointData[1][1];
    z2 = massOfCircles[circlesAmount-1].pointData[1][2];
    
    x3 = massOfCircles[circlesAmount-1].pointData[2][0];
    y3 = massOfCircles[circlesAmount-1].pointData[2][1];
    z3 = massOfCircles[circlesAmount-1].pointData[2][2];
    
    A = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    B = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    C = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    D = x1*(y2*z3-y3*z2) + x2*(y3*z1-y1*z3) + x3*(y1*z2-y2*z1);
    
    if (D/B > 0) {
        normals[k-1].xx = A;
        normals[k-1].yy = B;
        normals[k-1].zz = C;
    } else {
        std::cout << "nize nula" << std::endl;
        normals[k-1].xx = -A;
        normals[k-1].yy = -B;
        normals[k-1].zz = -C;
    }
    
    f[k-1].xx = x1;
    f[k-1].yy = y1;
    f[k-1].zz = z1;
    //нормали посчитаны //граничные точки плоскостей записаны
    
    //началось веселье
    for (int i=1; i<k; i++) {
        w[i].xx = mainLine.xx1 - f[i].xx;
        w[i].yy = mainLine.yy1 - f[i].yy;
        w[i].zz = mainLine.zz1 - f[i].zz;
        //скалярное произв (directr, n[i])
        d_scalar = directr.xx * normals[i].xx + directr.yy * normals[i].yy + directr.zz * normals[i].zz;
        //скалярное произв (w[i], n[i])
        w_scalar = w[i].xx * normals[i].xx + w[i].yy * normals[i].yy + w[i].zz * normals[i].zz;
        
        if (d_scalar == 0) {
            if (w_scalar < 0) continue;
            continue;
        }
        t = -w_scalar/d_scalar;
        std::cout << "t = " << t << std::endl;
        if (d_scalar > 0) {
            if (t <= 1) {
                std::cout << t << " down " << t_down << std::endl;
                t_down = fmax(t, t_down);
                std::cout << "----down= " << t_down << std::endl;
            }
            //continue;
        }
        if (d_scalar < 0) {
            if (t >= 0)  {
                std::cout << t << " up " << t_up << std::endl;
                t_up = fmin(t, t_up);
                std::cout << "----up= " << t_up << std::endl;
            }
            
            //std::cout << "------- " << t_up << std::endl;
        }
    }
    
    p1.xx = (mainLine.xx1 + (mainLine.xx2 - mainLine.xx1)*t_down);
    p1.yy = (mainLine.yy1 + (mainLine.yy2 - mainLine.yy1)*t_down);
    p1.zz = (mainLine.zz1 + (mainLine.zz2 - mainLine.zz1)*t_down);
    
    p2.xx = (mainLine.xx1 + (mainLine.xx2 - mainLine.xx1)*t_up);
    p2.yy = (mainLine.yy1 + (mainLine.yy2 - mainLine.yy1)*t_up);
    p2.zz = (mainLine.zz1 + (mainLine.zz2 - mainLine.zz1)*t_up);
    
    if (p1.xx < p2.xx) {
        if (p2.xx < minX) {
            p2.xx = 0;
            p1.xx = 0;
            p2.yy = 0;
            p1.yy = 0;
            p2.zz = 0;
            p1.zz = 0;
        }
    } else
        if (p1.xx >= p2.xx) {
            if (p2.xx > maxX) {
                p2.xx = 0;
                p1.xx = 0;
                p2.yy = 0;
                p1.yy = 0;
                p2.zz = 0;
                p1.zz = 0;
            }
        }
    
    
    std::cout << p1.xx << " " << p1.yy << " " << p1.zz << std::endl;
    std::cout << p2.xx << " " << p2.yy << " " << p2.zz << std::endl;
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
            //            std::cout << massOfCircles[j].pointData[i][0] << std::endl;
            //            std::cout << massOfCircles[j].pointData[i][1] << std::endl;
            //            std::cout << massOfCircles[j].pointData[i][2] << std::endl;
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
            glColor3f(0.3,  0.0,  0.7);
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
            glVertex3f(massOfCircles[j].pointData[i+1][0], massOfCircles[j].pointData[i+1][1], massOfCircles[j].pointData[i+1][2]);
            glVertex3f(massOfCircles[j+1].pointData[i][0], massOfCircles[j+1].pointData[i][1], massOfCircles[j+1].pointData[i][2]);
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
        glVertex3f(massOfCircles[j].pointData[0][0], massOfCircles[j].pointData[0][1], massOfCircles[j].pointData[0][2]);
        glVertex3f(massOfCircles[j+1].pointData[circle.pointsAmount-1][0], massOfCircles[j+1].pointData[circle.pointsAmount-1][1], massOfCircles[j+1].pointData[circle.pointsAmount-1][2]);
        glVertex3f(massOfCircles[j+1].pointData[0][0], massOfCircles[j+1].pointData[0][1], massOfCircles[j+1].pointData[0][2]);
        glEnd();
    }
    /*   for (int j=0; j<circlesAmount-1; j++) {
     glBegin(GL_POLYGON);
     glColor3f(0.3,  0.0,  0.7);
     glVertex3f(massOfCircles[j].pointData[0][0], massOfCircles[j].pointData[0][1], massOfCircles[j].pointData[0][2]);
     glVertex3f(massOfCircles[j].pointData[circle.pointsAmount-1][0], massOfCircles[j].pointData[circle.pointsAmount-1][1], massOfCircles[j].pointData[circle.pointsAmount-1][2]);
     glVertex3f(massOfCircles[j+1].pointData[0][0], massOfCircles[j+1].pointData[0][1], massOfCircles[j+1].pointData[0][2]);
     glEnd();
     
     glBegin(GL_POLYGON);
     glColor3f(0.04,  0.14,  0.6);
     glVertex3f(massOfCircles[j].pointData[circle.pointsAmount-1][0], massOfCircles[j].pointData[circle.pointsAmount-1][1], massOfCircles[j].pointData[circle.pointsAmount-1][2]);
     glVertex3f(massOfCircles[j+1].pointData[0][0], massOfCircles[j+1].pointData[0][1], massOfCircles[j+1].pointData[0][2]);
     glVertex3f(massOfCircles[j+1].pointData[circle.pointsAmount-1][0], massOfCircles[j+1].pointData[circle.pointsAmount-1][1], massOfCircles[j+1].pointData[circle.pointsAmount-1][2]);
     glEnd();
     }*/
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
        
        mass = init(1.0, circle, 0.5);
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS){
        
        circle.pointsAmount--;
        
        mass = init(1.0, circle, 0.5);
        
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS){
        circlesAmount++;
        
        mass = init(1.0, circle, 0.5);
        
        
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS){
        circlesAmount--;
        
        mass = init(1.0, circle, 0.5);
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS){
        //cyrus_back(mainLine);
        cyrus = true;
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS){
        //cyrus_back(mainLine);
        cyrus = false;
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
