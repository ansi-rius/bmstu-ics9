#include <iostream>
#include "declaration.h"

std::ostream& operator<< (std::ostream& os, Matrix& matr){
    for (int i=0; i<matr.m; i++)
        for (int j=0; j<matr.n; j++){
            os << matr[i][j].n << "/";
            os << matr[i][j].d << std::endl;
        }
    return os;
}

int main() {
    int n, m, a, b;

    std::cin >> n >> m;
    Matrix matrix(m, n);

    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++){
            std::cin >> a;
            std::cin >> b;
            matrix[i][j] = *new Fractions(a,b);
        }

    std::cout << matrix;
    std::cout<<std::endl;

    std::cout << "lines = " << matrix.get_num_of_lines() << std::endl;
    std::cout << std::endl;
    std::cout << "columns = " << matrix.get_num_of_columns() << std::endl;


    matrix.multipl(matrix, 0, 3);
    std::cout<<matrix;
    std::cout << "ыыы" << std::endl;
    matrix.addi(matrix, 0, 1);
    std::cout << matrix;
    return 0;
}