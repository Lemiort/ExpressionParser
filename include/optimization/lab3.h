#ifndef LAB3_H_INCLUDED
#define LAB3_H_INCLUDED

#include <iostream>
#include <cmath>

using namespace std;


namespace LAB3
{
//double eps;

const double tau = (sqrt(5.0) - 1.0) / 2.0;
const double tau2 = (3 - sqrt(5)) / 2.0;

double g1,g2,alpha, x01, x02, p1,p2, dx1, dx2, x1, x2,eps;
double a, b,l,m;
double z,d,gamma,w;
int k;


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
    //cout<<"a = "<<a<<"; b = "<<b<<endl;
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
    //cout<<"\nxmin = "<<x;
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

void norm(double& e1, double& e2)
{
    double temp = sqrt(e1*e1+ e2*e2);
    e1 = e1 / temp;
    e2 = e2 / temp;
}

double f9(double _x1, double _x2)
{
    //return 4*pow(_x1,2.0) + 4*pow(_x2,2.0) - 6*_x1*_x2 + _x1;
    return _x1*_x1 + 3*_x2*_x2 + 2*_x1*_x2;
}

void df9(double _x1, double _x2)
{
    dx1 = 2*_x1 + 2*_x2 ;
    dx2 = 6*_x2 + 2*_x1;
}



void point(double _alpha)
{
    x1 = x01 + _alpha*p1;
    x2 = x02 + _alpha*p2;
}

double y(double _alpha)
{
    point(_alpha);
    return f9(x1,x2);
}

double dy(double _alpha)
{
    point(_alpha);
    df9(x1,x2);
    norm(p1,p2);
    return dx1 * p1 + dx2 * p2;
}

double lab3(double _x01, double _x02, double _p1, double _p2)
{
    p1= _p1;
    p2= _p2;
    norm(p1,p2);
    x01 = _x01;
    x02 = _x02;

    swann2(dy);
    double mina =zs2(y);
    //double mina =davidon(y,dy);
    //point(mina);
    return mina;
}
}
#endif // LAB3_H_INCLUDED
