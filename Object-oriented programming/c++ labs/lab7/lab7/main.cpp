#include <iostream>
#include "declaration.h"

std::ostream& operator<< (std::ostream& os, Matrix& matr) {
    for (int i = 0; i < matr.m; i++) {
        for (int j = 0; j < matr.n; j++) {
            os << matr[i][j] << ' ';
        }
        os << std::endl;
    }
    return os;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    int matrix[n][m];

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            std::cin >> matrix[i][j];
        }
    }
    return 0;
}