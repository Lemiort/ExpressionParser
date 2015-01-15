#ifndef MATRIX_H
#define MATRIX_H
#include <MathVector.h>
#include <string>

class Matrix
{
    public:
        Matrix(unsigned m, unsigned n, bool e = false);
        Matrix(const Matrix& source);
        Matrix(MathVector v);
        virtual ~Matrix();

        Matrix& transp();
        MathVector ToVector()throw (Exception);
        double* operator[](int m)throw (Exception);

        int collumns;
        int rows;
        void setValue(int m, int n,double value);
        double getValue(int m, int n);

        Matrix Inverse();
        double Determinant();
        Matrix Minor( int, int);
        Matrix Adjugate();
        double Cofactor(int,int);
        std::string ToString();
        //Matrix& operator= (Matrix right);

    protected:
    private:
        //Matrix* operator+(Matrix* right);
        //Matrix* operator-(Matrix* right);
        //Matrix* operator*(Matrix* right);
        //Matrix* operator*(double k);
        double** matr;
};

Matrix& operator+(Matrix l, Matrix r)throw (Exception);
Matrix& operator-(Matrix l, Matrix r)throw (Exception);
Matrix& operator*(Matrix l, Matrix r)throw (Exception);
Matrix& operator*(double l, Matrix r);
Matrix& operator*(Matrix l, double r);
Matrix& operator-(Matrix r);
Matrix& operator/(Matrix l, double r);
//MathVector& operator*(MathVector l, Matrix r)throw (Exception);
#endif // MATRIX_H
