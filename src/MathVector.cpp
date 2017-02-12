#include "MathVector.h"
#include <cmath>
#include <iostream>
#include <sstream>

MathVector::MathVector(int size, bool ones)
{
    //ctor
    length = size;
    vec = new double[length];

    for(int i=0; i< length;i++)
    {
        if(!ones)
            vec[i] = 0.0;
        else
            vec[i] = 1.0;
    }
}

MathVector::~MathVector()
{
    //dtor
    delete[] vec;
}

double& MathVector::operator[](int n) throw (Exception)
{
    if(n>=length)
        throw Exception("Out of vector  range exception");
    return (vec[n]);
}

double MathVector::norma()
{
    double n=0;
    for(int i=0;i < length;i++)
        n=n+pow(vec[i],2.0);
    return pow(n,0.5);
}

MathVector operator+(MathVector l,MathVector r) throw (Exception)
{
    if(l.Getlength()!=r.Getlength())
        return 0;
    else
    {
        MathVector temp(l.Getlength());
        for(int i=0;i<temp.Getlength();i++)
            temp[i]= l[i]+r[i];
        return temp;
    }
}

MathVector operator-(MathVector l,MathVector r) throw (Exception)
{
    if(l.Getlength()!=r.Getlength())
    {
        throw Exception("Different vector lenghts");
        return 0;
    }
    else
    {
        MathVector temp(l.Getlength());
        for(int i=0;i<temp.Getlength();i++)
            temp[i]= l[i]-r[i];
        return temp;
    }
}

MathVector operator*(double l,MathVector r)
{
        MathVector temp(r.Getlength());
        for(int i=0;i<temp.Getlength();i++)
            temp[i]= l*r[i];
        return temp;
}

void MathVector::Normalize()
{
    double n= norma();
    /*if(n==0.0)
        return;
        //std::cout<<"\n norma ="<<n;*/
    for(int i=0;i<length;i++)
        vec[i]=vec[i]/n;
}

MathVector operator+(MathVector v)
{
    return v;
}
MathVector operator-(MathVector v)
{
    MathVector t(v.Getlength());
    for(int i=0;i<t.Getlength();i++)
        t[i]=-v[i];
    return t;
}

MathVector& MathVector::operator=(MathVector right)
{
    length = right.length;
    for(int i=0;i<length;i++)
    {
        vec[i]=right.vec[i];
    }

    return *this;
}

MathVector::MathVector(const MathVector& source)
{
    //MathVector* res=new MathVector(source.Getlength());
    length = source.length;
    vec = new double[length];
    for(int i=0;i<length;i++)
    {
        vec[i]=source.vec[i];
    }
}

double operator*(MathVector l, MathVector r)throw (Exception)
{
    if(l.Getlength()!=r.Getlength())
    {
        throw Exception("Different vector lenghts");
        return 0;
    }
    else
    {
        double res=0;
        for(int i=0;i<l.Getlength();i++)
        {
            //std::cout<<"\nres="<<res<<"  l="<<l[i]<<"  r="<<r[i] <<std::endl;
            res+= l[i]*r[i];
        }
        //std::cout<<"\nres="<<res<<std::endl;
        return res;
    }
}

bool operator==(MathVector l, MathVector r)throw (Exception)
{
    if(l.Getlength()!=r.Getlength())
    {
        throw Exception("Different vector lenghts");
        return 0;
    }
    else
    {
        bool res=true;
        for(int i=0;i<l.Getlength();i++)
        {
            if(l[i]!=r[i])
                return false;
        }
        //std::cout<<"\nres="<<res<<std::endl;
        return res;
    }
}

bool operator!=(MathVector l, MathVector r)throw (Exception)
{
    if(l.Getlength()!=r.Getlength())
    {
        throw Exception("Different vector lenghts");
        return 0;
    }
    else
    {
        bool res=false;
        for(int i=0;i<l.Getlength();i++)
        {
            if(l[i]!=r[i])
                return true;
        }
        //std::cout<<"\nres="<<res<<std::endl;
        return res;
    }
}


std::string MathVector::ToString()
{
    std::string result;
    std::stringstream sstr;
    result+="\n";
    for(int i=0; i<length;i++)
    {

            sstr<<vec[i]<<";  ";
            std:: string temp;
            sstr>>temp;
            result+=temp;
    }
    return result;
}
