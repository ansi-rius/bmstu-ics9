#define GL_SILENCE_DEPRECATION  //эпл не любит опенгл :с
#include <GLFW/glfw3.h>
#include <stdlib.h>  //needed for exit function
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <fstream>

struct circleData {
    int pointsAmount = 6;
    float** pointData;
};

void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawCylinder(float cylinderHeight, circleData circle, float cylinderRadius, circleData *massOfCircles);
void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods);
void dimetria();
circleData* init(float cylinderHeight, circleData circle, float cylinderRadius);
void tweening(circleData circle, float t);
void saveScene();
void loadScene();
void createTexture();
unsigned int Texture;

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
int pointsAmount = 6;

bool repeat = true;
bool lightingOn = true;
bool polygonFill = false;
bool textureOn = true;
int textureID = 0;



int windowWidth = 620;
int windowHeight = 620;

float t;

float fi = (asin(0.625/sqrt(2.0-0.625*0.625))); //62,82
float teta = (asin(0.625/sqrt(2.0))); //41,6

GLfloat m[16] = { cos(fi), sin(fi)*sin(teta), sin(fi)*cos(teta), 0,
                  0, cos(teta), -sin(teta), 0,
                  sin(fi), -cos(fi)*sin(teta), -cos(fi)*cos(teta), 0,
                  0, 0, 0, 1
}; //как получилась матрица расписать два поворота по х, у

GLFWwindow *window;

circleData circle;
circleData *mass;
circleData *mass2;

circleData *massOfP1;
circleData *massOfP2;
circleData *massOfP3;

int main(int argc, char const *argv[]) {
    
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    
    //glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    window = glfwCreateWindow(620, 620, "Rorate Cube", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHT1);

    mass = init(1.0, circle, 0.5);
    mass2 = init(1.0, circle, 0.5);
    
    createTexture();

    while (!glfwWindowShouldClose(window))
    {
        if (textureOn) {
            glEnable(GL_TEXTURE_2D);
            //glBindTexture(GL_TEXTURE_2D, textureID);
            //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        } else {
            glDisable(GL_TEXTURE_2D);
        }
        
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        
        glfwSetKeyCallback(window, keyboard_callback);
        
        glClearColor(0, 0, 0, 0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //вращение
        
        //glTranslatef(0.4, 0.4, 0.4);
        
        glTranslatef(trans_x, trans_y, trans_z);
        
        glScalef(sc_x, sc_y, sc_z);
        
        glRotatef(rotate_x, 1.0, 0.0, 0.0);  //повороты подломаны???
        glRotatef(rotate_y, 0.0, 1.0, 0.0);
        glRotatef(rotate_z, 0.0, 0.0, 1.0);
        
        
        dimetria(); //проекция через повороты/ротейты
        //glMultMatrixf(m);
        
        /*
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
        //drawCube();*/
        if (t >= 1) {
            repeat = true;
        }
        if (t <= 0) {
            repeat = false;
        }
        
        if (repeat) {
            t -= 0.005;
        } else {
            t += 0.005;
        }
       // std::cout << t << std::endl;
        
        tweening(circle, t);
        
        
        //
        //std::cout << img << std::endl;
        
        drawCylinder(1.0, circle, 0.5, mass);
        
        if (lightingOn) {
            glEnable(GL_LIGHTING);
            glEnable(GL_NORMALIZE);
            
            glPushMatrix();
            glLoadIdentity();
           
            GLfloat light1_diffuse[] = {0.04,  0.14,  0.6};
            GLfloat light1_position[] = {0.0, 0.0, 1.0, 1.0};
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
            glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
            
            glPopMatrix();
        } else {
            glDisable(GL_LIGHTING);
        }
        
      //  glDisable(GL_LIGHTING);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

circleData *massOfCircles;

circleData* init(float cylinderHeight, circleData circle, float cylinderRadius) {
    massOfCircles = new circleData[circlesAmount]; //массив из 4 элементов, каждый из которых содержит кол-во точек 1 кольца и координаты хуz каждой точки
    for (int ii=0; ii<circlesAmount; ii++) {
        massOfCircles[ii].pointData = new float*[circle.pointsAmount];
        for (int i=0; i<circle.pointsAmount; i++) {
            massOfCircles[ii].pointData[i] = new float[3];
        }
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
            //
            
        }
        dy += dh;
    }
    t=0;
    massOfP1 = new circleData[circlesAmount];
    massOfP2 = new circleData[circlesAmount];
    massOfP3 = new circleData[circlesAmount];
    int a = 0;
    float b = 0.1;
    
    for (int ii=0; ii<circlesAmount; ii++) {
        
        massOfP1[ii].pointData = new float*[circle.pointsAmount];
        massOfP2[ii].pointData = new float*[circle.pointsAmount];
        massOfP3[ii].pointData = new float*[circle.pointsAmount];
        for (int i=0; i<circle.pointsAmount; i++) {
            massOfP1[ii].pointData[i] = new float[3];
            massOfP2[ii].pointData[i] = new float[3];
            massOfP3[ii].pointData[i] = new float[3];
            
            massOfP1[ii].pointData[i][0] = -i*a;
            massOfP1[ii].pointData[i][1] = -i*a;
            massOfP1[ii].pointData[i][2] = -i*a;
            
            massOfP2[ii].pointData[i][0] = i*a;
            massOfP2[ii].pointData[i][1] = i*a;
            massOfP2[ii].pointData[i][2] = i*a;
        }
    }
    for (int i=0; i<circle.pointsAmount; i++) {
        massOfP3[0].pointData[i][0] = 0;
        massOfP3[0].pointData[i][1] = -1;
        massOfP3[0].pointData[i][2] = 0;
        
        massOfP3[2].pointData[i][0] = 0;
        massOfP3[2].pointData[i][1] = 1;
        massOfP3[2].pointData[i][2] = 0;
        
        
        
        if (massOfCircles[1].pointData[i][0]<0) {
            massOfP3[1].pointData[i][0] = massOfCircles[1].pointData[i][0] - 1;
        } else {
            massOfP3[1].pointData[i][0] = massOfCircles[1].pointData[i][0] + 1;
        }
        massOfP3[1].pointData[i][1] = massOfCircles[1].pointData[i][1];
        massOfP3[1].pointData[i][2] = massOfCircles[1].pointData[i][2];
    }

    
    return massOfCircles;
}


void tweening(circleData circle, float t) {
//    std::cout << t << std::endl;
    
    for(int j=0; j<circlesAmount; j++) {
        for(int i=0; i<circle.pointsAmount; i++) { //пробег по точкам j-го круга
            //
            mass[j].pointData[i][0] = mass2[j].pointData[i][0]*(1-t)*(1-t)*(1-t) + 3*massOfP1[j].pointData[i][0]*t*(1-t)*(1-t) + 3*massOfP2[j].pointData[i][0]*t*t*(1-t) + massOfP3[j].pointData[i][0]*t*t*t;
            mass[j].pointData[i][1] = mass2[j].pointData[i][1]*(1-t)*(1-t)*(1-t) + 3*massOfP1[j].pointData[i][1]*t*(1-t)*(1-t) + 3*massOfP2[j].pointData[i][1]*t*t*(1-t) + massOfP3[j].pointData[i][1]*t*t*t;
            mass[j].pointData[i][2] = mass2[j].pointData[i][2]*(1-t)*(1-t)*(1-t) + 3*massOfP1[j].pointData[i][2]*t*(1-t)*(1-t) + 3*massOfP2[j].pointData[i][2]*t*t*(1-t) + massOfP3[j].pointData[i][2]*t*t*t;
        }
    }
    return;
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
           // glVertex3f(mass[j].pointData[i][0], mass[j].pointData[i][1], mass[j].pointData[i][2]);
        }
        glEnd();
        dy += dh;
        
    }
    
    for (int j=0; j<circlesAmount-1; j++) {
        for (int i=0; i<circle.pointsAmount-1; i++) {
            glBegin(GL_POLYGON);
                glColor3f(0.0,  0.0,  0.7);
            glTexCoord2f(0.0f, 0.0f);
                glVertex3f(mass[j].pointData[i+1][0], mass[j].pointData[i+1][1], mass[j].pointData[i+1][2]);
            glTexCoord2f(1.0f, 0.0f);
                glVertex3f(mass[j].pointData[i][0], mass[j].pointData[i][1], mass[j].pointData[i][2]);
            glTexCoord2f(1.0f, 1.0f);
                glVertex3f(mass[j+1].pointData[i][0], mass[j+1].pointData[i][1], mass[j+1].pointData[i][2]);
            glEnd();
            
            glBegin(GL_POLYGON);
                glColor3f(0.04,  0.14,  0.6);
//
            glTexCoord2f(1.0f, 0.0f);
                glVertex3f(mass[j].pointData[i+1][0], mass[j].pointData[i+1][1], mass[j].pointData[i+1][2]);
            glTexCoord2f(0.0f, 1.0f);
                glVertex3f(mass[j+1].pointData[i][0], mass[j+1].pointData[i][1], mass[j+1].pointData[i][2]);
            glTexCoord2f(1.0f, 1.0f);
                glVertex3f(mass[j+1].pointData[i+1][0], mass[j+1].pointData[i+1][1], mass[j+1].pointData[i+1][2]);
            glEnd();
        }
    }
    for (int j=0; j<circlesAmount-1; j++) {
            glBegin(GL_POLYGON);
            glColor3f(0.3,  0.0,  0.7);
//        glTexCoord2f(mass[j+1].pointData[circle.pointsAmount-1][0], mass[j+1].pointData[circle.pointsAmount-1][1]);
        glTexCoord2f(0.0f, 0.0f);
            glVertex3f(mass[j].pointData[circle.pointsAmount-1][0], mass[j].pointData[circle.pointsAmount-1][1], mass[j].pointData[circle.pointsAmount-1][2]);
//        glTexCoord2f(mass[j].pointData[0][0], mass[j].pointData[0][1]);
        glTexCoord2f(1.0f, 0.0f);
            glVertex3f(mass[j].pointData[0][0], mass[j].pointData[0][1], mass[j].pointData[0][2]);
        
//        glTexCoord2f(mass[j].pointData[circle.pointsAmount-1][0], mass[j].pointData[circle.pointsAmount-1][1]);
        glTexCoord2f(1.0f, 1.0f);
            glVertex3f(mass[j+1].pointData[circle.pointsAmount-1][0], mass[j+1].pointData[circle.pointsAmount-1][1], mass[j+1].pointData[circle.pointsAmount-1][2]);
            glEnd();
            
            glBegin(GL_POLYGON);
            glColor3f(0.04,  0.14,  0.6);
//        glTexCoord2f(mass[j].pointData[0][0], mass[j].pointData[0][1]);
        glTexCoord2f(0.0f, 0.0f);
            glVertex3f(mass[j].pointData[0][0], mass[j].pointData[0][1], mass[j].pointData[0][2]);
//        glTexCoord2f(mass[j+1].pointData[circle.pointsAmount-1][0], mass[j+1].pointData[circle.pointsAmount-1][1]);
        glTexCoord2f(1.0f, 0.0f);
            glVertex3f(mass[j+1].pointData[circle.pointsAmount-1][0], mass[j+1].pointData[circle.pointsAmount-1][1], mass[j+1].pointData[circle.pointsAmount-1][2]);
        glTexCoord2f(1.0f, 1.0f);
//        glTexCoord2f(mass[j+1].pointData[0][0], mass[j+1].pointData[0][1]);
            glVertex3f(mass[j+1].pointData[0][0], mass[j+1].pointData[0][1], mass[j+1].pointData[0][2]);
            glEnd();
    }
    
    for(int j=0; j<circlesAmount; j++) {
        glBegin(GL_POLYGON);
        for(int i=0; i<circle.pointsAmount-1; i++) { //пробег по точкам j-го круга
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.0f, mass[2].pointData[i][1], 0.0f);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(mass[j].pointData[i][0], mass[j].pointData[i][1], mass[j].pointData[i][2]);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(mass[j].pointData[i+1][0], mass[j].pointData[i+1][1], mass[j].pointData[i+1][2]);
        }
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, mass[2].pointData[pointsAmount-1][1], 0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(mass[j].pointData[pointsAmount-1][0], mass[j].pointData[pointsAmount-1][1], mass[j].pointData[pointsAmount-1][2]);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(mass[j].pointData[0][0], mass[j].pointData[0][1], mass[j].pointData[0][2]);
        glEnd();
    }
    glEnable(GL_NORMALIZE);
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
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        polygonFill = false;
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        polygonFill = true;
    }
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
        lightingOn = !lightingOn;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        saveScene();
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        loadScene();
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        textureOn = !textureOn;
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
using namespace std;

void saveScene() {
    std::ofstream st("../scene.txt");
    st << windowWidth << " " << windowHeight << endl;
    st << polygonFill  << " " << textureOn << " " << lightingOn << endl;
    st << circlesAmount << " " << pointsAmount << endl;
    st << rotate_x << " " << rotate_y << " " << rotate_z << endl;
    st << t << endl;
    st.close();
}

void loadScene() {
    std::ifstream st("../scene.txt");
    st >> windowWidth >> windowHeight;
    st >> polygonFill >> textureOn >> lightingOn;
    st >> circlesAmount >> pointsAmount;
    st >> rotate_x >> rotate_y >> rotate_z;
    st >> t;
    st.close();
    
    glfwSetWindowSize(window, windowWidth, windowWidth);
}



void createTexture() {
    FILE* img;
    int offset;
    img = fopen("/Users/anemone/Desktop/grafony/lab6/GL2/stone.bmp", "rb");
    fseek(img, 0x0a, SEEK_SET);
    fread(&offset, 4, 1, img);
    fseek(img, (long)offset, SEEK_SET);
    unsigned char *data = new unsigned char[786486];
    fread(data, 786486, 1, img);
    fclose(img);
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
}
