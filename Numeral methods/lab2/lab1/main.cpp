//
//  main.cpp
//  lab1
//
//  Created by Anastasia on 14.02.2020.
//  Copyright © 2020 Anastasia. All rights reserved.
//

#include <cmath>
#include <iostream>

void inversion(float** A, int N);
float* solve_matrix(float* a, float* b, float* c, float *d);

int n=10;

int main(int argc, const char * argv[]) {
    
    //std::cout << "Enter size of matrix \n";
    //std::cin >> n;
    std::string function = "sin(x)";

    
    float a = 0.0;
    float b = 1.0;
    
    //int n = 5;
    
    float *koef_a = new float[n+1];
    float *koef_b = new float[n+1]; 
    float *koef_c = new float[n+1]; //коэф с
    float *koef_d = new float[n+1]; //коэф д
    float *spline = new float[n+1]; //сам сплайн
    float *delta = new float[n+1]; //погрешность
    
    float h =(float)((b-a)/n);
    
    int j=0;
    float sum = a;
    
    while (sum <= b) {
        koef_a[j] = sum * exp(sum); //koef a
        sum +=h;
        j++;
    }
 
    float *diag_a = new float[n-1];
    float *diag_b = new float[n-2];
    float *diag_c = new float[n-2];
    float *free_d = new float[n-1];

    
    for (int i=0; i<n-1; i++) {
        diag_a[i] = 4.0;
    }
    for (int i=0; i<n-2; i++) {
        diag_b[i] = 1.0;
        diag_c[i] = 1.0;
    }
    
    float* ek = solve_matrix(diag_a, diag_b, diag_c, free_d);
    for (int i = 1; i < n-1 ; i++) {
        koef_c[i] = ek[i];
    }
    koef_c[n-1] = 0;
    koef_c[0] = 0;
    
   
    
    //new c counter
    
    //--------------
    
    for (int i = 0; i < n -1; i++) {
        koef_b[i] = (koef_a[i+1] - koef_a[i]) / h - (h/3) * (koef_c[i+1] + 2*koef_c[i]);
        koef_d[i] = (koef_c[i+1] - koef_c[i]) / (3*h);
    }
    
    for (int i=0; i<n+1; i++) {
        spline[i] = koef_a[i] + koef_b[i]*(h) + koef_c[i]*h*h + koef_d[i]*h*h*h;
    }
    
    for (int i=0; i<n+1; i++) {
        delta[i] = abs(koef_a[i]-spline[i]);
    }
    
    //std::cout << h << std::endl;
    
    std::cout << "  x:  ";
    for (int i=0; i<n+1; i++) {
        printf("%.10f", h*i);
        std::cout << "   ";
    }
    std::cout << std::endl;
    
    std::cout << "  y:  ";
    for (int i=0; i<n+1; i++) {
        printf("%.10f", koef_a[i]);
        std::cout << "   ";
    }
    std::cout << std::endl;
    
    std::cout << " y*:  ";
    for (int i=0; i<n+1; i++) {
        printf("%.10f", spline[i]);
        std::cout << "   ";
    }
    std::cout << std::endl;
    
    std::cout << "del:  ";
    for (int i=0; i<n+1; i++) {
        printf("%.10f", abs(koef_a[i]-spline[i]));
        std::cout << "   ";
    }
    std::cout << std::endl;
    
    for (int i=0; i<n+1; i++) {
        std::cout << "koef_a= " << koef_a[i] << "  ";
    }
    std::cout << std::endl;
    for (int i=0; i<n+1; i++) {
        std::cout << "koef_b= " << koef_b[i] << "  ";
    }
    std::cout << std::endl;
    for (int i=0; i<n+1; i++) {
        std::cout << "koef_c= " << koef_c[i] << "  ";
    }
    std::cout << std::endl;
    for (int i=0; i<n+1; i++) {
        std::cout << "koef_d= " << koef_a[i] << "  ";
    }
    std::cout << std::endl;
    
    free(koef_a);
    free(koef_b);
    free(koef_c);
    free(koef_d);
    

    
    free(spline);
    free(delta);
    

    
    
    return 0;
}

void inversion(float** A, int N)
   {
       double temp;

       float **E = new float*[N];
       for (int i = 0; i < N; i++) {
           E[i] = new float[N];
       }


       for (int i = 0; i < N; i++)
           for (int j = 0; j < N; j++)
           {
               E[i][j] = 0.0;

               if (i == j)
                   E[i][j] = 1.0;
           }

       for (int k = 0; k < N; k++)
       {
           temp = A[k][k];

           for (int j = 0; j < N; j++)
           {
               A[k][j] /= temp;
               E[k][j] /= temp;
           }

           for (int i = k + 1; i < N; i++)
           {
               temp = A[i][k];

               for (int j = 0; j < N; j++)
               {
                   A[i][j] -= A[k][j] * temp;
                   E[i][j] -= E[k][j] * temp;
               }
           }
       }

       for (int k = N - 1; k > 0; k--)
       {
           for (int i = k - 1; i >= 0; i--)
           {
               temp = A[i][k];

               for (int j = 0; j < N; j++)
               {
                   A[i][j] -= A[k][j] * temp;
                   E[i][j] -= E[k][j] * temp;
               }
           }
       }

       for (int i = 0; i < N; i++)
           for (int j = 0; j < N; j++)
               A[i][j] = E[i][j];

   }

float* solve_matrix(float* a, float* b, float* c, float *d) {

    float *diag_a = a;
    float *diag_b = b;
    float *diag_c = c;
    float *free_d = d;

    auto *alpha = new float[n-1];
    auto *beta = new float[n-1];
    auto *x = new float[n];

    //-------------------------------
//    for (int i=1; i<n-1; i++) {
//        if (std::abs(diag_a[i]) <= std::abs(diag_c[i-1] + diag_b[i])) {
//            std::cout << "Input is incorrect 1 stat ";
//        }
//        if (std::abs(diag_b[i])/(std::abs(diag_a[i])) > 1) {
//            std::cout << "Input is incorrect 2 stat";
//        }
//        if (std::abs(diag_c[i-1]) / (std::abs(diag_b[i])) > 1) {
//            std::cout << "Input is incorrect 3 stat";
//        }
//    }

            if (diag_a[0] != 0) {
            alpha[0] = - diag_b[0]/diag_a[0];
            std::cout << "alpha[" << "0" <<"]= " << alpha[0];
        } else {
            std::cout << "a[0] = 0 error";
            //return 1;
        }
        beta[0] = free_d[0] / diag_a[0];
        std::cout << "beta[" << "0" <<"]= " << beta[0];
        
        for (int i=1; i<n-1; i++) {
            alpha[i] = -1* (float)(diag_b[i])/ (float)(alpha[i-1]*diag_c[i-1] + diag_a[i]);
            beta[i] = (free_d[i]-diag_c[i-1]*beta[i-1])/(alpha[i-1]*diag_c[i-1] + diag_a[i]);
            std::cout << "alpha[" << i <<"]= " << (diag_b[i]) << " ";
            std::cout << "beta[" << i <<"]= " << beta[i] << " ";
        }
        beta[n-1] = (free_d[n-1]-diag_c[n-2]*beta[n-2])/(alpha[n-2]*diag_c[n-2] + diag_a[n-1]);
        std::cout << "beta[" << n-1 <<"]= " << beta[n-1] << " ";
        
        alpha[n-1] = -(diag_b[n-1-1])/(alpha[n-1-1]*diag_c[n-1-1] + diag_a[n-1-1]);
        //std::cout << " --- "<< diag_b[n-1] << " " << alpha[n-1-1] << " " << diag_c[n-1-1] << " " << diag_a[n-1] << " --- ";
        std::cout << "alpha[" << n-1 <<"]= " << alpha[n-1] << std::endl;
        x[n-1] = beta[n-1];
        
        for (int i=n-2; i>=0; i--) {
            x[i] = alpha[i]*x[i+1] + beta[i];
            std::cout << "x[" << i << "]= " << x[i] << std::endl;
        }
    
    
    return x;
}
   
