#ifndef VECTOR_H
#define VECTOR_H
#include <exception.h>
#include <string>
//#include "Matrix.h"

class MathVector
{
    public:
        MathVector(const MathVector& source);
        MathVector(int size, bool ones=false);
        virtual ~MathVector();
        const int Getlength() { return length; }
        void Setlength(int val) { length = val; }
        double norma();
        void Normalize();
        double& operator[] (int n)throw (Exception);
        MathVector& operator= (MathVector right);
        std::string ToString();
    protected:
    private:
        double* vec;
        int length;
    friend MathVector operator+(MathVector v);
    friend MathVector operator-(MathVector v);
};

double operator*(MathVector l, MathVector r)throw (Exception);
MathVector operator+(MathVector l,MathVector r)throw (Exception);
MathVector operator-(MathVector l,MathVector r)throw (Exception);
bool operator==(MathVector l, MathVector r)throw (Exception);
bool operator!=(MathVector l, MathVector r)throw (Exception);
bool operator<(MathVector l, MathVector r)throw (Exception);
/*double operator*(Vector l, Vector r)throw (Exception);
Vector operator+(Vector l,Vector r)throw (Exception);
Vector operator-(Vector l,Vector r)throw (Exception);*/
MathVector operator*(double l,MathVector r);
//Vector operator*(double l,Vector r);

#endif // VECTOR_H
