//
//  main.cpp
//  curs
//
//  Created by Anastasia on 15/12/2019.
//  Copyright © 2019 Anastasia. All rights reserved.
//
#include <cmath>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int height;
int width;
int intensity;
char type[10];

int main(int argc, const char * argv[]) {
    
    string filename = "02.bmp"; //(argv[1]);
    string path = "/Users/anemone/Documents/3 курс/5 сем/cursach/curs/curs/input_images/" + filename;
    ifstream infile(path, ios::binary);
    if (!infile.is_open())
    {
        cout << "File " << path << " not found in directory." << endl;
        return 0;
    }
    ofstream img1("/Users/anemone/Documents/3 курс/5 сем/cursach/curs/curs/output_images/02.bmp", ios::binary);
    
    infile >> ::type >> ::width >> ::height >> ::intensity;
    img1 << type << endl << width << " " << height << endl << intensity << endl;
    
    double **pic = new double*[height];
    
    for (int i = 0; i < height; i++)
    {
        pic[i] = new double[width];
    }
    
    for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
        pic[i][j] = (int)infile.get();
    
    
    for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
        img1 << (char)((int)pic[i][j]);
    
    std::cout << "Hello, World!\n";
    return 0;
}
