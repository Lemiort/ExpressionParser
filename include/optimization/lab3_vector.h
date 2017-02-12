#ifndef LAB3_VECTOR_H_INCLUDED
#define LAB3_VECTOR_H_INCLUDED


#include <iostream>
#include <cmath>
#include "MathVector.h"

using namespace std;


namespace LAB3_VECTOR
{
//double eps;

const double tau = (sqrt(5.0) - 1.0) / 2.0;
const double tau2 = (3 - sqrt(5)) / 2.0;

double g1,g2,alpha, x01, x02, p1,p2, dx1, dx2, x1, x2,eps;
double a, b,l,m;
double z,d,gamma,w;
int k;

MathVector* X0;
MathVector* P;
double (*Y)(MathVector);
double(*dY)(MathVector,MathVector );

void swann1(double (&y)(double))
{
    k = 1;

    alpha = 0.01;
    double x=0.0;

    //устанавливаем направление функции
    if (y(x + alpha) > y(x))
        alpha = -alpha;


    while (k < 30)
    {
        if ( y(x+alpha) > y(x) )
        {
            break;
        }
        else
        {
            x += alpha;
            alpha *= 2.0;
            k++;
        }
    }

    a = x-alpha/2;
    b = x+alpha;

    if (a > b) swap(a, b);
    //cout<<"\nSwann-1 stopped, k="<<k<<"\n ["<<a<<", "<<b<<"]"<<endl;
}


void swann2( double (&dy)(double))//swann4
{
    k=1;
    double x=0, xprev = 0;
    alpha = 0.0001;
    do
    {
        if( dy(x) > 0 )
            alpha = -alpha;
        xprev = x;
        x = x + alpha;
        alpha = 2 * alpha;
        k++;
        if( k>=20 ) break;
    }
    while( dy(x) * dy(xprev) > 0 );
    if( xprev < x )
    {
        a = xprev;
        b = x;
    }
    else
    {
        a = x;
        b = xprev;
    }
    //cout<<"\nSwann-4 stopped, k="<<k<<"\n ["<<a<<", "<<b<<"]"<<endl;
}

double zs2( double (&y)(double))
{
    double len = abs(a - b);
    //cout<<"\na = "<<a<<"; b = "<<b<<endl;
    //cout<<"\n "<<(a+b)/2.0;

    k = 1;
    l = a + tau2 * len;
    m = a + tau * len;
    // cout<<"l = "<<l<<"; m = "<<m<<endl;

    do
    {
        if( y(l) < y(m) )
        {
            //a = a;
            b = m;
            m = l;
            len = abs(a - b);
            l = a + tau2 * len;
        }
        else
        {
            a = l;
            //b = b;
            l = m;
            len = abs(a - b);
            m = a + tau * len;
        }
        k++;
        if( k >= 45 )
        {
            //cout<<"\n\n too looong, exit";
            break;
        }
    }
    while( (b - a) >= eps );

    //cout<<"\nZS2 stopped, k="<<k;
    //cout<<"\nal min = "<<(a+b)/2;
    return (a + b) / 2.0;
}

double  davidon(double (&y)(double), double (&dy)(double))
{
    k= 1;
    do
    {
        z=dy(a)+dy(b) + 3*(y(a)-y(b))/(b-a);
        w = sqrt(z*z - dy(a)*dy(b));
        gamma = (z + w - dy(a))/(dy(b) - dy(a) +2*w);
        d = a+gamma*(b-a);
        //d = gamma*(b);


        if(dy(d)>0)
            b = d;
        if(dy(d)<0)
            a = d;
        k++;
        if(k>=50)
            break;
    }
    while(dy(d) != 0);
    //cout<<"\nDavidon stopped at k="<<k;
    return d;
}

double y(double al)
{
    MathVector X1=(al*(*P));

   /* for(int i=0; i<X1.Getlength(); i++)
    {
        cout<<"\nX1["<<i<<"]=";
        cout<<X1[i];
    }*/

    return Y(*X0 + X1);
}
double dy(double al)
{
    MathVector temp=*X0+(al*(*P));

    /*for(int i=0; i<temp.Getlength(); i++)
    {
        cout<<"\ntemp["<<i<<"]=";
        cout<<temp[i];
    }*/

    return (*dY)(temp ,(*P));
}


double lab3(MathVector _X0, MathVector _P,double (&_Y)(MathVector),double(&_dY)(MathVector,MathVector ), double _eps)
{
    X0=&_X0;
    P=&_P;
    P->Normalize();
    Y=&_Y;
    dY=&_dY;
    eps=_eps;

    swann2(dy);
    double mina =zs2(y);
    //double mina =davidon(y,dy);
    return mina;
}
}

#endif // LAB3_VECTOR_H_INCLUDED
