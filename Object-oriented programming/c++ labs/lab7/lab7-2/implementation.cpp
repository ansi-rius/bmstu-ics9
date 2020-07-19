#include <algorithm>
#include "declaration.h"

Fractions::Fractions(long n) {
    this->n = n;
    this->d = 1;
}

Fractions::Fractions(long n, long d) {
    long g = 0;
    g = gcd(n,d);
    this->n = n/g;
    this->d = d/g;
}

Fractions::Fractions() {
    this->n = 0;
    this->d = 0;
}

long Fractions::gcd(long n, long d) {
    return d ? gcd (d, n % d) : n;
}

Fractions Fractions::add(Fractions f){
    return *(new Fractions((this->n * f.d) + (f.n * this->d), (this->d * f.d)));
}

Fractions Fractions::mul(Fractions f){
    return *(new Fractions((this->n * f.n), (f.d * this->d)));
}

Fractions& Matrix::Row::operator[] (int j) {
    return this->matrix->matrix[i][j];
}

Matrix::Matrix(int m, int n) {
    this->n = n;
    this->m = m;
    matrix = new Fractions*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new Fractions[n];
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

Matrix::Row::Row(Matrix *matrix, int i) {
    this->matrix = matrix;
    this->i = i;
}

Matrix::Matrix(const Matrix &obj): n(obj.n)  {
    std::copy(obj.matrix, obj.matrix + n*m, matrix);
}

Matrix& Matrix::operator= (const Matrix &obj) {
    if (this != &obj) {
        Fractions **new_a = new Fractions *[obj.m];
        for (int i=0; i<obj.m; i++)
            new_a = new Fractions *[obj.n];

        std::copy(obj.matrix, obj.matrix + m*n, new_a);
        for (int i = 0; i < m; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        //n = obj.n;
        m = obj.m;

        matrix = new_a;
    }
    return *this;
}

void Matrix::multipl(Matrix matrix, int m, Fractions k) {
    for (int i=0; i < matrix.m; i++) {
        matrix[m][i] = matrix[m][i].mul(k);
    }
}

void Matrix::addi(Matrix matrix, int m1, int m2) {
    for (int i=0; i < matrix.n; i++)
        matrix[m1][i] = matrix[m1][i].add(matrix[m2][i]);

}
int Matrix::get_num_of_columns() {
    return n;
}

int Matrix::get_num_of_lines() {
    return m;
}