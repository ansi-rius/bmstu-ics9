//
// Created by Anastasia on 20/04/2018.
//

#include <algorithm>
#include "declaration.h"

Fractions& Matrix::Row::operator[](int j) {
    return this->matrix->matrix[i][j];
}

Matrix::Matrix(int m, int n) {
    this->n = n;
    this->m = m;
    matrix = new Fractions*[m];
    for (int i = 0; i < n; i++) {
        matrix[i] = new Fractions[n];
    }
    ///
    Fractions matrix[m][n] = new Fractions[n][m]


}

/*Matrix::~Matrix() {
    for (int i = 0; i < m; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}*/

Matrix::Row::Row(Matrix *matrix, int i) {
    this->matrix = matrix;
    this->i = i;
}

/*Matrix::Matrix(const Matrix &obj): n(obj.n)  {
    a = new Fractions *[m];
    for (int j=0; j<obj.m; j++)
        a = new Fractions *[obj.n];

    std::copy(obj.a, obj.a + m, a);
}

Matrix& Matrix::operator= (const Matrix &obj) {
    if (this != &obj) {

        Fractions **new_a = new Fractions *[obj.m];
        for (int i=0; i<obj.m; i++)
            new_a = new Fractions *[obj.n];

        std::copy(obj.a, obj.a + obj.m, new_a);
        for (int i = 0; i < m; i++) {
            delete[] a[i];
        }
        delete[] a;
        n = obj.n;
        m = obj.m;

        a = new_a;
    }
    return *this;
}*/

Fractions Matrix::multiply(Matrix matrix, int m, int k) {
    for (int i=0; i<matrix.n; i++) {
        matrix[m][i] = matrix[m][i].multiplication(k);
    }

}

int Matrix::get_num_of_columns(Matrix matrix) {
    return matrix.n;
}

int Matrix::get_num_of_lines(Matrix matrix) {
    return matrix.m;
}