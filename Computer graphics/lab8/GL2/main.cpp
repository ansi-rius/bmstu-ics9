#define GL_SILENCE_DEPRECATION  //эпл не любит опенгл :с
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"uniform mat4 matrix;"
"void main()\n"
"{\n"
"gl_Position = matrix * vec4( position, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void drawCylinder(float cylinderHeight, float cylinderRadius);
void dimetria();

typedef struct {
    float x, y, z;
} Point;

vector<Point> vertices;
vector<unsigned int> indices;

int vertCount;

GLuint VAO, VBO, EBO;

int WIDTH = 620, HEIGHT = 620;

float trans_x = 0;
float trans_y = 0;
float trans_z = 0;

float rotate_y = 0.0f;
float rotate_x = 0.0f;
float rotate_z = 0.0f;

float sc_x = 0.5;
float sc_y = 0.5;
float sc_z = 0.5;

int pointsAmount =6, circlesAmount =3;

GLfloat PologonModeValue = GL_LINE;

float fi = (asin(0.625/sqrt(2.0-0.625*0.625))); //62,82
float teta = (asin(0.625/sqrt(2.0))); //41,6

GLfloat TransformationMatrix[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};

GLfloat m[16] = { cos(fi), sin(fi)*sin(teta), sin(fi)*cos(teta), 0,
    0, cos(teta), -sin(teta), 0,
    sin(fi), -cos(fi)*sin(teta), -cos(fi)*cos(teta), 0,
    0, 0, 0, 1
}; //как получилась матрица расписать два поворота по х, у

static double PI = 3.1415926535897932384626433832795;

glm::mat4 project;
glm::mat4 model = glm::translate(glm::mat4(1.f), { trans_x, trans_y, trans_z });
GLuint shaderProgram;

int main(void) {
    if (!glfwInit()) {
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Lab8", NULL, NULL);
    glfwMakeContextCurrent(window);
    //
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scroll_callback);
    
    glewExperimental = GL_TRUE;
    
    glewInit();
    
    glEnable(GL_DEPTH_TEST);
    GLfloat teta = (float)M_PI * 30 / 180;
    GLfloat TransformationMatrix[16] = { cos(fi), sin(fi)*sin(teta), sin(fi)*cos(teta), 0,
        0, cos(teta), -sin(teta), 0,
        sin(fi), -cos(fi)*sin(teta), -cos(fi)*cos(teta), 0,
        0, 0, 0, 1
    };
    project = glm::make_mat4x4(TransformationMatrix);
    
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        //glMultMatrixf(TransformationMatrix);
        drawCylinder(1.0, 0.5);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(0);
        
        glm::mat4 model = glm::translate(glm::mat4(1.f), { 0.4, 0.4, 0.4 });
        
        glMatrixMode(GL_MODELVIEW);
         model = glm::translate(glm::mat4(1.f), { trans_x, trans_y, trans_z });
        model *= glm::rotate(model, glm::radians(rotate_x), {1, 0, 0});
        model *= glm::rotate(model, glm::radians(rotate_y), {0, 1, 0});
        model *= glm::rotate(model, glm::radians(rotate_z), {0, 0, 1});
        model = glm::scale(model, {sc_x, sc_y, sc_z});
        
        //dimetria();
        //glMultMatrixf(TransformationMatrix);
    
        glPolygonMode(GL_FRONT_AND_BACK, PologonModeValue);
        
        model = glm::rotate(model, (-fi), {1, 0, 0});
        model = glm::rotate(model, (-teta), {0, 1, 0});
        //glm::mat4 model = glm::translate(glm::mat4(1.f), { trans_x, trans_y, trans_z });

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "matrix"), 1, GL_FALSE, glm::value_ptr(model));
        
        glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    if(width>height)
    {
        glViewport((width-height)/2, 0, std::min(width,height), std::min(width,height));
    }
    else
        glViewport(0, (height-width)/2, std::min(width,height), std::min(width,height));
};

void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode) {
    GLfloat rotateStep = 5.0f;
    GLfloat valueStep = 1.0f;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_D:
                trans_x += 0.05;
                break;
            case GLFW_KEY_A:
                trans_x -= 0.05;
                break;
            case GLFW_KEY_S:
                trans_y -= 0.05;
                break;
            case GLFW_KEY_W:
                trans_y += 0.05;
                break;
            case GLFW_KEY_Q:
                rotate_z += rotateStep;
                break;
            case GLFW_KEY_E:
                rotate_z -= rotateStep;
                break;
            case GLFW_KEY_LEFT:
                rotate_y += 5;
                break;
            case GLFW_KEY_RIGHT:
                rotate_y -= 5;
                break;
            case GLFW_KEY_UP:
                rotate_x += 5;
                break;
            case GLFW_KEY_DOWN:
                rotate_x -= 5;
                break;
            case GLFW_KEY_C:
                pointsAmount -= valueStep;
                break;
            case GLFW_KEY_V:
                pointsAmount += valueStep;
                break;
            case GLFW_KEY_R:
                circlesAmount -= valueStep;
                break;
            case GLFW_KEY_F:
                circlesAmount += valueStep;
                break;
            case GLFW_KEY_1:
                PologonModeValue = GL_FILL;
                break;
            case GLFW_KEY_2:
                PologonModeValue = GL_LINE;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    sc_x += 0.5 * yoffset;
    sc_y += 0.5 * yoffset;
    sc_z += 0.5 * yoffset;
}

void drawCylinder(float cylinderHeight, float cylinderRadius) {
    //points, circles
    glPolygonMode(GL_FRONT_AND_BACK, PologonModeValue);
    
//    double externalRad = 2.0 * PI / roundValue;
//    double interiorRad = 2.0 * PI / shapesValue;
    float dh = cylinderHeight / circlesAmount;
    float dy = 0.0;
    
    //vertices.resize(2*(roundValue * (shapesValue + 1) + 1));
    vertices.resize(pointsAmount*circlesAmount);
    indices.clear();
    
    vertCount = 0;
    
    for(int j=0; j<circlesAmount; j++) {
        for(int i=0; i<pointsAmount; i++) { //пробег по точкам j-го круга
            float degInRad = ((3.14159*2)*i)/pointsAmount;
            vertices[vertCount].x = cos(degInRad)*cylinderRadius;;
            vertices[vertCount].y = dy+dh-0.6;
            vertices[vertCount].z = sin(degInRad)*cylinderRadius;
            vertCount++;
        }
        dy += dh;
    }
    
    indices.clear();
    
//    for (int i=0; i<pointsAmount; i++) {
//
//    }
    
    for (int i = 0; i < circlesAmount-1; ++i) {
        for (int j = 0; j < pointsAmount; ++j) {
            indices.push_back(i*pointsAmount + j);
            cout << i*pointsAmount + j << " ";
            //indices.push_back(i*pointsAmount + j + 1);
            //cout << i*pointsAmount + j + 1 << " ";
            indices.push_back((i + 1)*pointsAmount + j);
            cout << (i + 1)*pointsAmount + j << " " << endl;;
            //indices.push_back((i + 1)*pointsAmount + j + 1);
            //cout << (i + 1)*pointsAmount + j + 1 << endl;
        }
        indices.push_back(i*pointsAmount);
        cout << i*pointsAmount << " " << endl;;
    }
    indices.push_back(pointsAmount*circlesAmount-pointsAmount);
    
    
//    indices.push_back(0);
//    indices.push_back(1);
//    //indices.push_back(7);
//    indices.push_back(7);
//    indices.push_back(6);
    //indices.push_back(1);
//    for(int i = 0; i < indices.size(); i++)
//        cout << indices[i] << ' ';
    
    
    
    //    glBindVertexArray(VAO);
    //
    //    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Point), &vertices[0], GL_DYNAMIC_DRAW);
    //
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
    //
    //    GLuint posAttr = glGetAttribLocation(shaderProgram, "pos");;
    //    glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)(0*sizeof(GLfloat)));
    //    glEnableVertexAttribArray(posAttr);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Point), &vertices[0], GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)(0*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    
}


void dimetria() {
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-fi*(180/3.14) , 1.0, 0.0, 0.0);
    glRotatef(-teta*(180/3.14) , 0.0, 1.0, 0.0);
    //glTranslatef(-0.9, -0.7, -0.5);
    model = glm::rotate(model, (-fi*(180.f/3.14f)), {1, 0, 0});
    model = glm::rotate(model, (-teta*(180.f/3.14f)), {0, 1, 0});
    //model *= glm::rotate(model, glm::radians(rotate_x), {1, 0, 0});
    //glScaled(0.2, 0.2, 0.2);
}
