//
// Created by Anastasia on 21/04/2018.
//
#include <iostream>

#ifndef LAB7_2_DECLARATION_H
#define LAB7_2_DECLARATION_H

#endif //LAB7_2_DECLARATION_H

class Fractions {
public:
    long n, d;

    Fractions();
    Fractions(long n);
    Fractions(long n, long d);
    long gcd(long n, long d);

    Fractions add (Fractions f);
    Fractions mul (Fractions f);
};

class Matrix {
public:
    Fractions **matrix;
    int n, m;

public:
    Matrix(int n, int m);
    virtual ~Matrix();

    class Row {
    private:
        Matrix *matrix;
        int i;
    public:
        Row(Matrix *matrix, int i);
        Fractions& operator[] (int j);
    };

    Matrix::Row operator[] (int i){
        return Row(this, i);
    }
    Matrix& operator= (const Matrix &obj1);
    Matrix(const Matrix &obj1);
    void static multipl(Matrix matrix, int m, Fractions k);
    void static addi(Matrix matrix, int m1, int m2);
    int  get_num_of_lines();
    int  get_num_of_columns();
};