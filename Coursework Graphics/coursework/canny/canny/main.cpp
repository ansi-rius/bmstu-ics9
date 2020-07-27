//
//  main.cpp
//  canny
//
//  Created by Anastasia on 03.02.2020.
//  Copyright © 2020 Anastasia. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
#include <vector>
#include "/Users/anemone/Downloads/bitmap/bitmap_image.hpp"

using namespace std;
void gaussian_kernel(float **gauss, float sigma);
bitmap_image applyFilter(bitmap_image image, int height, int width, float **gauss);
float gaussian_model(float x, float y, float sigma);
float getFilteredValue(float **filteredColor);
bitmap_image grayscale(bitmap_image image, int height, int width);
bitmap_image gradientComputing(bitmap_image image, int height, int width);
bitmap_image convolve(bitmap_image image, float **g);

int main()
{
   bitmap_image image("/Users/anemone/Desktop/hell1/canny/input_images/VeIIZp3sujM-2.bmp");
    
   if (!image)
   {
      printf("Error - Failed to open: input.bmp\n");
      return 1;
   }

   //unsigned int total_number_of_pixels = 0;

   const unsigned int height = image.height();
   const unsigned int width  = image.width();

   //for (int y = 0; y < height; ++y)
   //{
   //   for (int x = 0; x < width; ++x)
   //   {
   //      rgb_t colour;
   //       image.get_pixel(x, y, colour);
   //       image.set_pixel(x, y, '0', '0', colour.blue);
   //   }
   //}
    //image.set_pixel(0, 0, 255, 0, 0);
   //printf("Number of pixels with red >= 111: %d\n",height*width);
    
    //-------------------------
    float sigma = 1.5;
    //-------------------------
   
    
    //1) Smooth with Gaussian Filter
    //Convolve the input image with Gaussian kernel(filter) in order to remove high-freq noises. It is useful to remove small-scale textures effectively. Because Gaussian kernel is separable, use 2D separable convolution for faster computation.
    
    //matrix for filtration initialized
    float **gauss = new float*[5];
    for (int i = 0; i < 5; i++) {
        gauss[i] = new float[5];
    }
    
    image.copy_from(grayscale(image, height, width));
    
    //filling matrix for filtration
    gaussian_kernel(gauss, sigma);
    
    image.copy_from(applyFilter(image, height, width, gauss));
    
    //2) Compute Horizontal/Vertical Gradient
    //Gradient is the first-order derivatives of image for each direction. It is rough detection of all pssible edges in the image and the edges look thick. So we need to thinning algorithm to find 1-pixel edge lines, which is Non-Maximal Suppression. The gradient can be computed using central difference:
    //deltaX(x,y) = [(x+1, y) - (x-1, y)] / 2
    //deltaY(x,y) = [(x, y+1) - (x, y-1)] / 2
    
    image.copy_from(gradientComputing(image, height, width));
    
    
    
    //float c = 1;
    //char cc = '1';
    //cout << " ------ " << cc << " " << +(char(c)) << endl;
    image.save_image("/Users/anemone/Desktop/hell1/canny/input_images/img_step_6.bmp");
    return 0;
}
     
void gaussian_kernel(float **gauss, float sigma) {
    float sum = 0.0;
    
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            gauss[x][y] = gaussian_model(x-5/2, y-5/2, sigma);
            sum += gauss[x][y];
        }
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            gauss[i][j] /= sum;
            cout << gauss[i][j] << " ";
        }
        cout << endl;
    }
}

float gaussian_model(float x, float y, float sigma) {
    return (1/ (2*M_PI*sigma*sigma) * exp(-(x*x + y*y) / (2*sigma*sigma)));
}

/*void applyFilter(bitmap_image image, int height, int width, float **gauss) {
    int filterHeight = 5;
    int filterWidth = 5;
    int shift = filterWidth / 2;
    
    for (int y = 0; y < height; ++y)
    {
       for (int x = 0; x < width; ++x)
       {
          rgb_t colour;
           image.get_pixel(x, y, colour);
          //image.set_pixel(x, y, '0', '0', colour.blue);
           float avg;
           avg = 0.3*colour.red + 0.11*colour.blue + 0.59*colour.green;
           //cout << avg << " " << endl;
           image.set_pixel(x, y, avg, avg, avg);
       }
    }
    
    for (int i = 0; i < height-filterHeight+1; i++) {
        for (int j = 0; j < width-filterWidth+1; j++) {
            for (int h = i; h < i+filterHeight; h++) {
                for (int w = j; w < j+filterWidth; w++) {
                    rgb_t colour;
                    //cout << i << " " << j << " " << h << " " << w << endl;
                    image.get_pixel(j, i, colour);
                    float r = (float)colour.red;
                    float g = (float)colour.green;
                    float b = (float)colour.blue;
                    //if (r != 255 && g != 255 && b != 255)
                        //cout << r << " " << g << " " << b << " " << endl;
                    
                    image.set_pixel(j, i,
                                    (100*r*gauss[h-i][w-j]),
                        (100*g*gauss[h-i][w-j]),
                        (100*b*gauss[h-i][w-j]));
                    //cout << "-- r*g= " << r*gauss[h-i][w-j] << "-- gr*g= " << g*gauss[h-i][w-j] << " r= " << r  << " gr= " << g << " g= " << gauss[h-i][w-j] << " " << endl;
                    //image.set_pixel(j, i, (char)r, 0, 0);

                    image.get_pixel(j, i, colour);
                    r = (float)colour.red;
                    g = (float)colour.green;
                    b = (float)colour.blue;
                    //cout << "---- " << r << " " << g << " " << b << " " << endl;
                }
            }
        }
    }
    image.save_image("/Users/anemone/Desktop/hell1/canny/input_images/FINALE.bmp");
    
}*/

bitmap_image grayscale(bitmap_image image, int height, int width) {
    for (int y = 0; y < height; ++y)
    {
       for (int x = 0; x < width; ++x)
       {
          rgb_t colour;
           image.get_pixel(x, y, colour);
           float avg;
           avg = 0.3*colour.red + 0.11*colour.blue + 0.59*colour.green;
           //cout << avg << " " << endl;
           image.set_pixel(x, y, avg, avg, avg);
       }
    }
    image.save_image("/Users/anemone/Desktop/hell1/canny/input_images/img_step_0.bmp");
    
    return image;
}

bitmap_image applyFilter(bitmap_image image, int height, int width, float **gauss) {
    cout << height << " " << width << endl;
    
    for (int x=2; x<width-5; x++) {
        for (int y=2; y<height-5; y++) {
            //cout << " " << y << " " << endl;
            float **distributedColourRed = new float*[5];
            float **distributedColourGreen = new float*[5];
            float **distributedColourBlue = new float*[5];
            
            for (int i = 0; i < 5; i++) {
                distributedColourRed[i] = new float[5];
                distributedColourGreen[i] = new float[5];
                distributedColourBlue[i] = new float[5];
            }
            
            for (int gaussX=0; gaussX<5; gaussX++) {
                for (int gaussY=0; gaussY<5; gaussY++) {
                    
                    int sampleX = x+gaussX;
                    int sampleY = y+gaussY;
                    
                    float currentGauss = gauss[gaussX][gaussY];
                    
                    rgb_t colour;
                    
                    image.get_pixel(sampleX, sampleY, colour);
                    distributedColourRed[gaussX][gaussY] = currentGauss*colour.red;
                    distributedColourGreen[gaussX][gaussY] = currentGauss*colour.green;
                    distributedColourBlue[gaussX][gaussY] = currentGauss*colour.blue;
                }
            }
            image.set_pixel(x, y, getFilteredValue(distributedColourRed), getFilteredValue(distributedColourGreen), getFilteredValue(distributedColourBlue));
        }
    }
    image.save_image("/Users/anemone/Desktop/hell1/canny/input_images/img_step_1.bmp");
    return image;
}

float getFilteredValue(float **filteredColor) {
    float sum = 0;
    
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            sum += filteredColor[i][j];
        }
    }
    return sum;
}

bitmap_image gradientComputing(bitmap_image image, int height, int width) {
    float **gx = new float*[3];
    for (int i = 0; i < 3; i++) {
        gx[i] = new float[3];
    }
    gx[0][0] = 1; gx[0][1] = 0; gx[0][2] = -1;
    gx[1][0] = 2; gx[1][1] = 0; gx[1][2] = -2;
    gx[2][0] = 1; gx[2][1] = 0; gx[2][2] = -1;
    
    float **gy = new float*[3];
    for (int i = 0; i < 3; i++) {
        gy[i] = new float[3];
    }
    gy[0][0] = 1; gy[0][1] = 2; gy[0][2] = 1;
    gy[1][0] = 0; gy[1][1] = 0; gy[1][2] = 0;
    gy[2][0] = -1; gy[2][1] = -2; gy[2][2] = -1;
    
    bitmap_image img_x, img_y;
    img_x = convolve(image, gx);
    img_y = convolve(image, gy);
    
    float magR, magG, magB;
    float maxValR, maxValG, maxValB;
    maxValR=maxValG=maxValB = 0;
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            rgb_t colourx;
            img_x.get_pixel(i, j, colourx);
            //float pix_x = colourx.red + colourx.blue + colourx.green;
            
            rgb_t coloury;
            img_y.get_pixel(i, j, coloury);
            //float pix_y = coloury.red + coloury.blue + coloury.green;
            //mags = sqrt((pix_x*pix_x) + (pix_y*pix_y));
            magR = sqrt((colourx.red*colourx.red) + (coloury.red*coloury.red));
            magG = sqrt((colourx.green*colourx.green) + (coloury.green*coloury.green));
            magB = sqrt((colourx.blue*colourx.blue) + (coloury.blue*coloury.blue));
            if (magR > maxValR) {
                maxValR = magR;
            }
            if (magG > maxValG) {
                maxValG = magG;
            }
            if (magB > maxValB) {
                maxValB = magB;
            }
            image.set_pixel(i, j, magR, magG, magB);
        }
    }
    
    // Make sure all the magnitude values are between 0-255
    for (int i = 2; i < width-2; i++) {
        for (int j = 2; j < height-2; j++) {
            //mag[i][j] = mag[i][j] / maxVal * 255;
            rgb_t colour;
            image.get_pixel(i, j, colour);
            
            image.set_pixel(i, j, colour.red/maxValR *255, colour.green/maxValG *255, colour.blue/maxValB *255);
        }
    }
    image.save_image("/Users/anemone/Desktop/hell1/canny/input_images/img_step_2.bmp");
    return image;
}

bitmap_image convolve(bitmap_image image, float **g) {
    int height = image.height();
    int width = image.width();
    
    for (int i=1; i<width-2; i++) {
        for (int j=1; j<height-2; j++) {
            float sumR = 0;
            float sumG = 0;
            float sumB = 0;
            for (int k=0; k<3; k++) {
                for (int l=0; l<3; l++) {
                    
                    rgb_t colour;
                    image.get_pixel(i+k, j+l, colour);
                    
                    float currentG = g[k][l];
                    sumR += colour.red * currentG;
                    sumG += colour.green * currentG;
                    sumB += colour.blue * currentG;
                }
            }
            sumR = abs(sumR);
            sumG = abs(sumG);
            sumB = abs(sumB);
            image.set_pixel(i, j, sumR, sumG, sumB);
        }
    }
    
    return image;
}
