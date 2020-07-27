//
//  main.cpp
//  lab1
//
//  Created by Anastasia on 14.02.2020.
//  Copyright © 2020 Anastasia. All rights reserved.
//

#include <cmath>
#include <iostream>

int main(int argc, const char * argv[]) {
    int n = 0;
    
    std::cout << "Enter size of matrix \n";
    std::cin >> n;
    
    float *diag_a = new float[n];
    float *diag_b = new float[n-1];
    float *diag_c = new float[n-1];
    float *free_d = new float[n];
    
    std::cout << "Enter main diagonal \n";
    for (int i=0; i<n; i++) {
        std::cin >> diag_a[i];
    }
    
    std::cout << "Enter upper diagonal \n";
    for (int i=0; i<n-1; i++) {
        std::cin >> diag_b[i];
    }
    
    std::cout << "Enter lower diagonal \n";
    for (int i=0; i<n-1; i++) {
        std::cin >> diag_c[i];
    }
    
    std::cout << "Enter free numbers d \n";
    for (int i=0; i<n; i++) {
        std::cin >> free_d[i];
    }
    
    float *alpha = new float[n-1];
    float *beta = new float[n-1];
    float *x = new float[n];
    
    //-------------------------------
    for (int i=1; i<n-1; i++) {
        if (std::abs(diag_a[i]) < std::abs(diag_c[i-1] + diag_b[i])) {
            std::cout << "Input is incorrect 1 stat ";
        }
        if (std::abs(diag_b[i])/(std::abs(diag_a[i])) > 1) {
            std::cout << "Input is incorrect 2 stat";
        }
        if (std::abs(diag_c[i-1]) / (std::abs(diag_b[i])) > 1) {
            std::cout << "Input is incorrect 3 stat";
        }
    }
    
    if (diag_a[0] != 0) {
        alpha[0] = - diag_b[0]/diag_a[0];
    } else {
        std::cout << "a[0] = 0 error";
        return 1;
    }
    beta[0] = free_d[0] / diag_a[0];
    
    for (int i=1; i<n-1; i++) {
        alpha[i] = -(diag_b[i])/(alpha[i-1]*diag_c[i-1] + diag_a[i]);
        beta[i] = (free_d[i]-diag_c[i-1]*beta[i-1])/(alpha[i-1]*diag_c[i-1] + diag_a[i]);
        //std::cout << "alpha[" << i <<"]= " << alpha[i];
        //std::cout << "beta[" << i <<"]= " << beta[i];
    }
    beta[n-1] = (free_d[n-1]-diag_c[n-2]*beta[n-2])/(alpha[n-2]*diag_c[n-2] + diag_a[n-1]);
    //std::cout << "beta[" << n-1 <<"]= " << beta[n-1];
    x[n-1] = beta[n-1];
    
    for (int i=n-2; i>=0; i--) {
        x[i] = alpha[i]*x[i+1] + beta[i];
    }

    for (int i=0; i<n; i++) {
        std::cout << "x[" << i << "]= " << x[i] << std::endl;
    }
    
    return 0;
}
