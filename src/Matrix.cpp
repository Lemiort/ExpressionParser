#include "Matrix.h"
#include <cmath>
#include <sstream>
#include <iostream>



Matrix::Matrix(unsigned m, unsigned n, bool e)
{
    //ctor
    collumns = n;
    rows = m;
    matr = new double*[rows];
    for(int i=0; i<rows; i++)
    {
        matr[i] = new double[collumns];
        for(int j=0; j<collumns; j++)
        {
            if(e == true && i==j)
            {
                matr[i][j]=1.0;
            }
            else
            {
                matr[i][j]=0.0;
            }
        }

    }
    if(e)
        matr[0][0]=1.0;
}

Matrix::Matrix(MathVector v)
{
    collumns =1;
    rows = v.Getlength();
    matr = new double*[rows];
    for(int i=0;i<rows;i++)
    {
        matr[i] = new double;
        matr[i][0] = v[i];
    }
}

Matrix::~Matrix()
{
    //dtor
    for(int i=0; i<rows; i++)
    {
        //delete[] matr[i];
    }
    delete[] matr;
}

double Matrix::getValue(int m,int n)
{
    return matr[m][n];
}

void Matrix::setValue(int m, int n, double value)
{
    matr[m][n] = value;
}

std::string Matrix::ToString()
{
    std::string result;
    std::stringstream sstr;
    for(int i=0; i<rows;i++)
    {
        result+="\n";
        //std::cout<<"\n";
        for(int j=0; j<collumns;j++)
        {
            sstr<<matr[i][j]<<";  ";
            //std::cout<<matr[i][j]<<"  ";
            std:: string temp;
            sstr>>temp;
            result+=temp;
        }
    }
    return result;
}

double* Matrix::operator[](int m)throw (Exception)
{
    if(m>=rows)
        throw Exception("Out of matrix range exception");
    return matr[m];
}

Matrix& Matrix::transp()
{
    Matrix* temp=new Matrix(collumns,rows);
    for(int i=0; i<rows; i++)
        for(int j=0; j<collumns; j++)
        {
            //double t= matr[i][j];
            temp->matr[j][i]=matr[i][j];
        }
    return *temp;
}

Matrix& operator+(Matrix l, Matrix r)throw (Exception)
{
    if(l.collumns == r.collumns && l.rows == r.rows)
    {
        Matrix* temp = new Matrix(l.rows,r.collumns);
        for(int i=0; i<l.rows; i++)
            for(int j=0; j<l.collumns; j++)
            {
                //double sum=getValue(i,j)+right->getValue(i,j);
                (*temp)[i][j]= l[i][j]+r[i][j];
            }

        return *temp;
    }
    else
    {
        throw Exception("Incompatible matrices");
        return *(new Matrix(0,0));
    }
}

Matrix& operator-(Matrix l, Matrix r)throw (Exception)
{
    if(l.collumns == r.collumns && l.rows == r.rows)
    {
        Matrix* temp = new Matrix(l.rows,r.collumns);
        for(int i=0; i<l.rows; i++)
            for(int j=0; j<l.collumns; j++)
            {
                //double sum=getValue(i,j)+right->getValue(i,j);
                (*temp)[i][j]= l[i][j]-r[i][j];
            }

        return (*temp);
    }
    else
    {
        throw Exception("Incompatible matrices");
        return *(new Matrix(1,1));
    }
}

Matrix& operator*(Matrix l, Matrix r)throw (Exception)
{
    //std::cout<<"\nl.c="<<l.collumns<<"  l.r="<<l.rows<<"  r.r="<<r.rows<<" r.c="<<r.collumns;
    if(l.collumns == r.rows)
    {
        Matrix* temp= new Matrix(l.rows, r.collumns);
        for(int i=0; i<l.rows; i++)
            for(int j=0; j<r.collumns; j++)
                for(int k=0; k<l.collumns; k++)
                {
                    /*double t = temp->getValue(i,j);
                    t+=this->getValue(i,k)*right->getValue(k,j);
                    temp->setValue(i,j,t);*/
                    (*temp)[i][j]+=l[i][k]*r[k][j];
                }
        return *temp;
    }
    else
    {
        throw Exception("Incompatible matrices (operator *)");
        return *(new Matrix(1,1));
    }
}

MathVector& operator*(Matrix& l, MathVector& r)throw (Exception)
{
    if(l.collumns == r.Getlength())
    {
        MathVector* temp = new MathVector(l.collumns);
        for(int j=0; j<l.collumns; j++)
            for(int k=0; k<l.rows; k++)
            {
                (*temp)[j]+=r[k]*l[k][j];
            }
        return *temp;
    }
    else
    {
        throw Exception("Incopatible matrix and vector");
        return *(new MathVector(1));
    }
}

MathVector Matrix::ToVector() throw (Exception)
{
    if(collumns!=1)
    {
        throw Exception("Cant convert matrix to vector");
        return MathVector(0);
    }
    else
    {
        MathVector result(rows);
        for(int i=0; i<rows; i++)
        {
            result[i] = matr[i][0];
        }
        return result;
    }
}

Matrix::Matrix(const Matrix& source)
{
    //MathVector* res=new MathVector(source.Getlength());
    rows = source.rows;
    collumns = source.collumns;

     matr = new double*[rows];
    for(int i=0; i<rows; i++)
    {
        matr[i] = new double[collumns];
        for(int j=0; j<collumns; j++)
        {
            matr[i][j] = source.matr[i][j];
        }

    }
}

Matrix& operator*(double l, Matrix r)
{
    Matrix* result= new Matrix(r.rows, r.collumns);
    for(int i=0; i< r.rows;i++)
        for(int j=0; j<r.collumns;j++)
        {
            (*result)[i][j] = l*r[i][j];
        }
    return *result;
}

Matrix& operator*(Matrix l, double r)
{
    Matrix* result = new Matrix(l.rows, l.collumns);
    for(int i=0; i< l.rows;i++)
        for(int j=0; j<l.collumns;j++)
        {
            (*result)[i][j] = r*l[i][j];
        }
    return *result;
}

Matrix& operator/(Matrix l, double r)
{
    Matrix* result = new Matrix(l.rows, l.collumns);
    for(int i=0; i< l.rows;i++)
        for(int j=0; j<l.collumns;j++)
        {
            (*result)[i][j] = l[i][j]/r;
        }
    return *result;
}



Matrix& operator-(Matrix r)
{
    Matrix* result= new Matrix(r.rows, r.collumns);
    for(int i=0;i<r.rows;i++)
        for(int j=0;j<r.collumns;j++)
            (*result)[i][j] = -r[i][j];
    return *result;
}
