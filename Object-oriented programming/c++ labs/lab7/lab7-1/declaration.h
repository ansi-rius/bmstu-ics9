//
// Created by Anastasia on 20/04/2018.
//

#include <iostream>

#ifndef LAB7_1_DECLARATION_H
#define LAB7_1_DECLARATION_H

#endif //LAB7_1_DECLARATION_H

class Fractions {
public:
    int numerator, denominator;

    Fractions(int n, int d) {
        if(d == 0) {
            std::cout << "net" << std::endl; //check if denom = 0;
        }
        numerator = n;
        denominator = d;

        int thisGcd = gcd(numerator, denominator);

        numerator = numerator/thisGcd;
        denominator = denominator/thisGcd;
    }

public:
    Fractions(int n) {
        numerator = n;
        denominator = 1;
    }

/*public:
    String toString() {
        int thisGcd = gcd(numerator, denominator);

        return (numerator/thisGcd + "/" + denominator/thisGcd);
    }*/
private:
    static int gcd (int n, int d) {
        if (d==0)
            return n;
        return gcd(d,n%d);
    }

public:
    double evaluate() {  // like 'eval'
        double n = numerator;
        double d = denominator;
        return (n / d);
    }

public:
    Fractions add(Fractions fract2) {
        Fractions *res;
        res = new Fractions((numerator * fract2.denominator) + (fract2.numerator * denominator),
                                      (denominator * fract2.denominator));
        return *res;
    }

public:
    Fractions multiplication (Fractions fract2) {
        Fractions *res;
         res = new Fractions((numerator * fract2.numerator),
                                      (fract2.denominator * denominator));
        return *res;
    }
};

class Matrix {
public:
    Fractions **matrix;
    int n, m;
    Fractions **a;

public:
    Matrix(int n, int m);
    //virtual ~Matrix();

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
    //Matrix& operator= (const Matrix &obj1);
    //Matrix(const Matrix &obj1);
    Fractions static multiply(Matrix matrix, int m, int k);
    int static get_num_of_lines(Matrix matrix);
    int static get_num_of_columns(Matrix matrix);
};