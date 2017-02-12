//#include "expressionEstimator.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <Matrix.h>
#include <MathVector.h>
#include <parser.h>
#include <conio.h>
#include <expression.h>
#include <algorithm>
#include <vector>
#include <lab3_vector.h>
//#include <termios.h>

using namespace std;

//ExpressionEstimator estimator;
//std::auto_ptr<Function::Expression> expression;
Function::Expression* expression;
double eps;
int n;

//function decorator
double y(MathVector X)
{

    return expression->Calculate(X);
    //return estimator.calculate(&X[0],X.Getlength());
}

//gradient
MathVector grad(MathVector X)
{
    double h=eps;
    //h=0.000000001;
    //if(h<1.0) h=h*h;
    MathVector G(X.Getlength());

    for(int i=0; i<G.Getlength(); i++)
    {
        MathVector dX(G.Getlength());
        dX[i] = h;
        //cout<<"\ny(X+dX)"<<y(X+dX);
        G[i]=(y(X+dX)-y(X-dX))/(2.0*h);
    }


    return G;
}

//delta y in  P direction
double dy(MathVector X, MathVector P)
{
    P.Normalize();
    MathVector  G(X.Getlength());
    G = grad(X);
    return G*P;
}

string Example()
{
    cout<<"\n0. Your custom function\
            \n1. 4*x1^2+3*x2^2-4*x1*x2+x1  x*=(-0.125;0)\
            \n2. 8*x1^2+4*x1*x2+5*x2^2  x*=(0;0)\
            \n3. (1.5-x1*(1-x2))^2+(2.25-x1*(1-x2^2))^2+(2.625-x1*(1-x2^3))^2\
            \n x*=(3; 0.5)\
            \n4. 100*(x2-x1^2)^2+(1-x1)^2+90*(x4-x3^2)^2+\n\
                +(1-x3)^3+10.1*((x2-1)^2+(x4-1)^2)+19.8*(x2-1)*(x4-1)\
                \n  x*=(1; 1; 1; 1)\
            \n5. 0.1*(12+x1^2+(1+x2^2)/x1^2+(x1^2*x2^2+100)/(x1^4*x2^4))\
            \n x*=(1.743; 2.036)\
            \n6. x1^2+2*x2^2-2*x1*x2+x1\
            \n x*=(-1,-0.5)\
            \n7. (1-x1)^2+100*(x2-x1^2)^2 (Rosenbrock function)\
            \n x*=(1,1)\
            \nTo select example function type its number\n";
    int selection;
    cin>>selection;
    switch(selection)
    {
    case 1:
        return string("4*x1^2+3*x2^2-4*x1*x2+x1");
        break;
    case 2:
        return string("8*x1^2+4*x1*x2+5*x2^2");
        break;
    case 3:
        return string("(1.5-x1*(1-x2))^2+(2.25-x1*(1-x2^2))^2+(2.625-x1*(1-x2^3))^2");
        break;
    case 4:
        return string("100*(x2-x1^2)^2+(1-x1)^2+90*(x4-x3^2)^2\
                +(1-x3)^3+10.1*((x2-1)^2+(x4-1)^2)+19.8*(x2-1)*(x4-1)");
        break;
    case 5:
        return string("0.1*(12+x1^2+(1+x2^2)/x1^2+(x1^2*x2^2+100)/(x1^4*x2^4))");
        break;
    case 6:
        return string("x1^2+2*x2^2-2*x1*x2+x1");
        break;
    case 7:
        return string("(1-x1)^2+100*(x2-x1^2)^2");
        break;
    default:
        string formula;
        cout<<"\n Write function:\n";
        cin>>formula;
        return formula;
        break;
    }
}


MathVector HookeJeeves(MathVector X0)
{
    MathVector X1=X0;
    MathVector X2(X1.Getlength());
    MathVector X3(X1.Getlength());
    MathVector X4(X1.Getlength());
    double betta = 2.0;
    double h = 0.1;
    n = 1;
    int k=1;




    for(int i=0; i<1000; i++)
    {
        do
        {
            //шаг 1 ИП1
            X2=X1;
            for(int i=0; i<X2.Getlength(); i++)
            {
                MathVector E(X2.Getlength());
                E[i] = h;
                if(y(X2+E) < y(X2))
                    X2 = X2 + E;
                else if(y(X2 - E) < y(X2))
                    X2 = X2 - E;
                else
                    X2 = X2;

            }
            //шаг 2, ИП1 неудачен
            if(X2==X1)
            {
                if(h>eps)
                    h = h / betta;
                if(h<=eps)
                {
                    cout<<"\n Hooke-Jeeves k="<<n;
                    return X1;
                }

            }
            //на шаг 3
            else
                break;
        }
        while(true);
        //шаг 3
        X3 = X2 + (X2-X1);

        //проверка в окрестности Х3
        X4 = X3;
        for(int i=0; i<X4.Getlength(); i++)
        {
            MathVector E(X4.Getlength());
            E[i] = 1.0;
            if(y(X4+h*E) < y(X2))
                X4 = X4 + h*E;
            else if(y(X4- h*E) < y(X2))
                X4 = X4 - h*E;
            else
                X4 = X4;
        }
        //шаг 4
        //удача
        if(X4!=X3)
        {
            k++;
            X1 = X2;
            X2 = X4;
        }
        //неудача
        else
        {
            k=1;
            h = h/betta;
            X1 = X2;
        }



        n++;
    }
    cout<<"\n Hooke-Jeeves k="<<n;
    return  MathVector(X0.Getlength());
}

bool predicate(MathVector r, MathVector l)
{
    return y(r)<y(l);
}

MathVector NelderMead(MathVector X00)
{
    double alpha = 1.0;
    double betta = 0.5;
    double gamma = 2.0;
    double h = 0.1;
    int n = X00.Getlength();

    vector<MathVector> X;
    X.push_back(X00);
    for(int i=0; i< n; i++)
    {
        MathVector E(n);
        E[i] = h;
        X.push_back(X00+E);
    }
    //cout<<"\n vector size: ="<<X.size();

    int k=1;
    do
    {

        //шаг 1
        sort(X.begin(), X.end(),predicate);

        //выводим симплекс

        //шаг2
        //cout<<"\nStep 2";
        MathVector X0(n);
        for(int i=0; i<n; i++)
        {
            X0=X0+X.at(i);
        }
        X0 = (1.0/(n))*X0;


        MathVector Xr(n);
        //рефлекторная точка
        Xr=X0+ alpha*(X0-X.at(n));

        //одна из пяти операций
        //cout<<"\n y(Xr)="<<y(Xr);
        //меньше y1
        if( y(Xr) < y(X.at(0)))
        {
            //растяжение
            //cout<<"\nStretching";
            MathVector Xl = X0 + gamma*(X0-X.at(n));
            if(y(Xl) < y(Xr))
            {
                X.at(n) = Xl;
                Xr=Xl;
            }
            else
                X.at(n) = Xr;
        }
        //больше yn+1
        else if( y(Xr) > y(X.at(n)) )
        {
            //сжатие 1
            //cout<<"\n Compression -";
            MathVector Xs = X0 - betta*(X0-X.at(n));



            if( y(Xs) < y(X.at(n)))
            {
                X.at(n) = Xs;
                Xr=Xs;
            }

        }
        //больше y1, но меньше yn
        else if( y(Xr) > y(X.at(0)) && y(Xr) < y(X.at(n-1)) )
        {
            //отражние
            // cout<<"\n Reflection";
            X.at(n) = Xr;
        }
        //между yn и y n+1
        else if( y(Xr)> y(X.at(n-1)) && y(Xr) < y(X.at(n)))
        {
            //сжатие2
            //cout<<"\n Compression +";
            MathVector Xs = X0 + betta*(X0-X.at(n));


            if( y(Xs) < y(Xr))
            {
                X.at(n) = Xs;
                Xr=Xs;
            }

            else
                X.at(n) = Xr;
        }

        double G=0.0;
        MathVector Xm(n);
        for(int i=0; i<=n; i++)
        {
            Xm=Xm+X.at(i);
        }
        Xm= (1.0/(n+1))*Xm;

        for(int i=0; i<n; i++)
        {
            G+=(y(X.at(i)) - y(Xm));
        }
        G = G / (n+1);
        G = sqrt(G);
        //cout<<"\nG="<<G;
        if(G<=eps)
        {
            //cout<<"\nG="<<G;
            cout<<"\nNealder-Mead k="<<k;
            return Xm;
        }

        if(k>=999)
        {
            cout<<"\nNelder-Mead k="<<k;
            return Xm;
        }

        //getch();
        k++;
    }
    while(k<1000);
    return X00;
}

MathVector Rosenbrock(MathVector X00)
{
    //размерность системы
    int n = X00.Getlength();
    MathVector Alpha(n);
    MathVector prevX = X00;
    MathVector currentX = X00;


    std::vector<MathVector> P;
    for(int i=0; i< n; i++)
    {
        MathVector temp(n);
        temp[i] = 1.0;
        P.push_back(temp);
    }





    int step = 0;
    do
    {
        std::vector<MathVector> A;
        std::vector<MathVector> B;
        std::vector<MathVector> d;
        prevX = currentX;

        //step 1
        //получаем набор направлений минимизации
        for(int k=0; k< n; k++)
        {
            Alpha[k] = LAB3_VECTOR::lab3(prevX, P[k], y, dy, eps);
        }
        MathVector deltaX(n);
        for(int k=0; k< n; k++)
        {
            deltaX = deltaX + Alpha[k]*P[k];
        }

        //получаем новую точку
        currentX = prevX + deltaX;

        //step 2
        if(deltaX.norma() <= eps)
            break;
        //процедура Грамма-Шмидта
        else
        {

            for( int i=0; i< n; i++)
            {
                MathVector currentA(n);
                MathVector currentB(n);

                //step 1
                if( abs(Alpha[i]) <= eps)
                    currentA = P[i];
                else
                {
                    MathVector  tempSum(n);
                    for(int k=i; k<n; k++)
                    {
                        tempSum = tempSum + Alpha[k]*P[k];
                    }
                    currentA = tempSum;
                }

                //step 2
                if(i == 0)
                {
                    currentB = currentA;
                }
                else
                {
                    MathVector  tempSum(n);
                    for( int k=0; k < i-1; k++)
                    {
                        tempSum = tempSum + (A[i]*d[k])*d[k];
                    }
                    currentB = currentA + tempSum;
                }

                //step3
                MathVector currentd(n);
                currentd = currentB;
                currentd.Normalize();

                A.push_back(currentA);
                B.push_back(currentB);
                d.push_back(currentd);
            }
            cout<<"\n";
            //устаналиваем новые поисковые направления
            for(int i=0; i< n; i++)
            {
                P[i] = d[i];
                cout<<d[i].ToString()<<" ";
            }
        }

        cout<<"\nX["<<step<<"]="<<currentX.ToString();
    }
    while(step++ < 100);
    cout<<"\nRosenbrock "<<step;

    return currentX;
    /*do
    {

        for( int i=0; i< n; i++)
        {
            MathVector currentA(n);
            MathVector currentB(n);

            //step 1
            for(int k=0; k< n; k++)
            {
                Alpha[k] = LAB3_VECTOR::lab3(prevX, P[k], y, dy, eps);
            }

            if( abs(Alpha[n] - 0) <= eps)
                currentA = P[i];
            else
            {
                MathVector  tempSum(n);
                for(int k=i; k<n; k++)
                {
                    tempSum = tempSum + Alpha[k]*P[k];
                }
                currentA = tempSum;
            }

            //step 2
            if(i == 0)
            {
                currentB = currentA;
            }
            else
            {
                MathVector  tempSum(n);
                for( int k=0; k < i-1; k++)
                {
                    tempSum = tempSum + (A[i]*d[k])*d[k];
                }
                currentB = currentA + tempSum;
            }

            //step3
            MathVector currentd(n);
            currentd = currentB;
            currentd.Normalize();

            A.push_back(currentA);
            B.push_back(currentB);
            d.push_back(currentd);
        }
    }while( )*/
}

int main()
{
    try
    {
        //ExpressionEstimator::Init();
        string formula = Example();

        expression = new Function::Expression(
            Parser::Parser::TokensToPolskaInvers(
                Parser::Parser::StringToTokens(formula))
        );

        int arguments;
        arguments = expression->variablesNum;
        cout<<"\nVariables num = "<<arguments;

        MathVector X0(arguments);
        for(int i=0; i<arguments; i++)
        {
            cout<<"\nX0["<<i<<"]=";
            cin>>X0[i];
        }

        //cout<<"\n y(x0)="<<expression->Calculate(X0);
        cout<<"\neps = ";
        cin>>eps;

        //MathVector X = Portan2(X0);
        MathVector X = HookeJeeves(X0);
        cout<<"\n X*=";
        for(int i=0; i<X.Getlength(); i++)
            cout<<"\n"<<X[i];

        MathVector X1 = NelderMead(X0);
        cout<<"\n X*=";
        for(int i=0; i<X1.Getlength(); i++)
            cout<<"\n"<<X1[i];

        MathVector X2 = Rosenbrock(X0);
        cout<<"\n X*=";
        for(int i=0; i<X2.Getlength(); i++)
            cout<<"\n"<<X2[i];

    }
    catch(Exception& e)
    {
        printf("\n%s\n",e.what());
    }
    getch();
    return 0;
}
