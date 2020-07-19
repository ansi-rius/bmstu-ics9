#include <iostream>
#include "declaration.h"

std::ostream& operator<< (std::ostream& os, Matrix& matr){
    for (int i=0; i<matr.m; i++)
        for (int j=0; j<matr.n; j++){
            os << matr[i][j].numerator << "/";
            os << matr[i][j].denominator << std::endl;
        }
    return os;
}

int main() {
    int n, m, a, b;

    std::cin >> n >> m;
    Matrix matrix(n, m);

    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++){
            std::cin >> a;
            std::cin >> b;
            matrix[i][j] = *new Fractions(a,b);
        }

    std::cout << matrix;

    //Matrix::get_num_of_lines(matrix);
    //Matrix::get_num_of_columns(matrix);

    return 0;
}