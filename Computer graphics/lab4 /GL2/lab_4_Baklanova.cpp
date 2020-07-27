#include <iostream>
#define GL_SILENCE_DEPRECATION  //эпл не любит опенгл :с
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <cmath>
#include <math.h>

#define PI 3.14159265

struct point{
    int x, y, n;
};

union pixel{
    unsigned int a;
    char b[4];
};

double posx, posy =0;
int px, py=0, bound= 540;
int a=1080;
int b=1080;
bool filtration, fillment=false;
int zoom=2; //у мака разрешение (2880 x 1800), я изначально делала умножая массив буффера на 4 (на 1 пиксель стандартных экранов, у меня помещается 4 пикселя, как я поняла) но чтобы не громоздить программу, просто увеличила зум. Для просмотра на винде поменять зум на 1 и везде, где в вычислениях индекса у меня отнималось -150, надо сделать примерно -50(?) (цифра может отличаться, на винде не пробовала запуск
union pixel* buff;
int line_color=255, color =255| 250<<16 | 250<<8 | 255<<24, bound_color =255 | 255 <<8, polygon_color=155<<16 | 155<<8 | 155<<24 | 25;
bool flag=false;

int sign(int a) {return 1-2*(a>>31&1);};
int find_center();
void loop_draw();
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void brezenham(int x0, int y0, int x1, int y1);
void filter(int x0, int y0, int x1, int y1);
void build(int x, int y);

std::vector<point> polygon;

int main(int argc, const char *argv[]){
    if (!glfwInit()){
        std::cout << "faild\n";
        return 0;
    }
    
    GLFWwindow* window = glfwCreateWindow(a, b, "lol", NULL, NULL);
    
    if (!window){
        std::cout<< "faild\n";
        return 0;
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    buff= new union pixel[a*b];
    
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        loop_draw();
        
        glFlush();
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    
    delete [] buff;
    
    
    return(0);
}

void loop_draw(){
//    for (int i=0; i< a*b*4; buff[i].a=color, i++);
    //заполняю фон
    for (int i=0; i<a*b; i++) {
        buff[i].a=color;
    }
    for (int i=0; i< polygon.size(); i++){
        int s0=(i==0? polygon[(polygon.size()-1)].y : polygon[(i-1)%(polygon.size())].y);
        int s1=polygon[i].y;
        int s2=polygon[(i+1)%polygon.size()].y;
        flag=false;
        if (s1-s0>0 && s1-s2>0 || s1-s0<0 && s1-s2<0) flag=true;
        if (fillment) brezenham(polygon[i].x, polygon[i].y, polygon[(i+1)%polygon.size()].x, polygon[(i+1)%polygon.size()].y);
        if (fillment && filtration) filter(polygon[i].x, polygon[i].y, polygon[(i+1)%polygon.size()].x, polygon[(i+1)%polygon.size()].y);
    }
    
    for (int y=1; y<b-1; buff[(a-y++)*a+bound].a=bound_color); //прямая
    
    
    glRasterPos2f(-1, -1);
    glPixelZoom(zoom, zoom);
    glDrawPixels(a, b, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buff);
    
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
    px= xpos;
    py= ypos;
    //buff[a*b*4 - 4*a*py + 2*px].a = 0;
    return;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (action==0 && mods==0){
        polygon.push_back((point) {px, py, (int)polygon.size()});
        bound=find_center();
    }
    return;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    //std::cout<< key<< std::endl;
    if( action == 1) return;
    switch (key ){
        case 66: // b
            fillment^=true;
            break;
        case 82: // r
            polygon.clear();
            fillment=false;
            filtration=false;
            break;
        case 61: //+
            zoom++;
            break;
        case 70: // f
            filtration^=true;
            break;
        case 45:// -
            zoom--;
            abs(zoom);
            break;
        case GLFW_KEY_ESCAPE:
            if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED){
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            break;
        default:
            break;
    }
    return;
}

void filter(int x1, int y1, int x2, int y2){
    int dx= (x2- x1);
    int dy= (y2- y1);
    int sx= x1< x2? 1: -1;
    int sy= y1 < y2? 1: -1;
    if (dx==0) return; //значит перпендикулярно линии
    double tg= (double) dy/dx;
    bool intense = tg>0;
    bool swp = -1>tg || tg>1;
    if (swp) std::swap(x1,y1), std::swap(x2,y2), std::swap(dx,dy), std::swap(sx,sy);
    dx= abs(dx);
    dy= abs(dy);
    int I = 255;
    int e = I*dx;
    int m= 2*dy*I;
    double w = 2*e;
    int error= dx- dy;
    
    int choose_color = fillment? polygon_color : line_color;
    
    //рисую ребра
    while (x1!= x2 || y1!= y2) {
        int error2= error* 2;
        //buff[(a-y1-150)*a+x1].a=choose_color;
        
        if (filtration){
            if (swp) buff[(a- x1- 150)* a+ y1].b[0]= (unsigned char)(!intense ? e/(2*dx) : 255 - e/(2*dx));
            else buff[(a- y1- 150)* a+ x1].b[0]=(unsigned char)((intense) ? e/(2*dx) : 255 - e/(2*dx));
        }else {
            
        }
        //else buff[(a- y1- 150)* a+ x1].a=255; //линии
        //std::cout <<(double)(e/(2*dx)) << std::endl;
        if (error2> -dy){
            error-= dy;
            x1+= sx;
            e+=m;
            
        }
        if (error2< dx){
            error+= dx;
            y1+= sy;
            e-=w;
         
        }
        
        
    }
    return;
}


void brezenham(int x1, int y1, int x2, int y2){
    int dx= (x2- x1);
    int dy= (y2- y1);
    int sx= x1< x2? 1: -1;
    int sy= y1 < y2? 1: -1;
    if (dx==0) return; //значит перпендикулярно линии
    double tg= (double) dy/dx;
    //bool intense = tg>0;
    //bool swp = false;
    //if (filtrarion) swp = -1>tg || tg>1;
    //if (swp && filtrarion) std::swap(x1,y1), std::swap(x2,y2), std::swap(dx,dy), std::swap(sx,sy);
    dx= abs(dx);
    dy= abs(dy);
    int I = 255;
    int e = I*dx;
    int m= 2*dy*I;
    double w = 2*e;
    int error= dx- dy;
    
    int choose_color = fillment? polygon_color : line_color;
    
    //std::cout<< fillment << " " << filtrarion << std::endl;
    
    buff[(a-x2-150)*a+y2].a=255;
    
    if (fillment && flag) build(x1, y1);
    
    //рисую ребра
    while (x1!= x2 || y1!= y2) {
        int error2= error* 2;
        buff[(a-y1-150)*a+x1].a=choose_color;
        
        if (error2> -dy){
            error-= dy;
            x1+= sx;
        }
        if (error2< dx){
            error+= dx;
            y1+= sy;
            if (fillment) build(x1, y1);
        }
        
        
    }
    return;
}

void build(int x, int y){
    int dx= sign(bound-x);
    x+=dx;
    dx= sign(bound-x);
    for (; x!=bound; x+=dx ){
         buff[(a-y-150)*a+x].a=  buff[(a-y-150)*a+x].a == color ||  buff[(a-y-150)*a+x].a == line_color? polygon_color : color;
    }
    return;
}

int find_center(){
    int min=1200, max=-1;
    for (std::vector<point>::iterator it=polygon.begin(); it!=polygon.end(); ++it){
        min=(*it).x<min ? (*it).x : min;
        max=(*it).x>max ? (*it).x : max;
    }
    return (int) (max+min)/2;
}
