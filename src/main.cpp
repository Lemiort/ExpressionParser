//#include "expressionEstimator.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <Matrix.h>
#include <VectorMath.h>
#include <Lab3_Vector.h>
#include <MathVector.h>
#include <parser.h>
#include <function.h>
#include <conio.h>
//#include <termios.h>

using namespace std;

//ExpressionEstimator estimator;
//std::auto_ptr<Function::Expression> expression;
Function::Expression* expression;
double eps;
int n;

string Example()
{
    cout<<"\n0. Your custom function\
            \n1. x0^3+x1^2-3*x0-2*x1+2  x*=(1,1)\
            \n2. 8*x0^2+4*x0*x1+5*x1^2  x*=(0,0)\
            \n3. 4*x0^2+3*x1^2-4*x0*x1+x0 \
            \n4.(1.5-x1*(1-x2))^2+(2.25-x1*(1-x2^2))^2+(2.625-x1*(1-x2^3))^2\
            \n x*=(3; 0.5)\
            \n5.100*(x2-x1^2)^2+(1-x1)^2+90*(x4-x3^2)^2+\n\
                +(1-x3)^3+10.1*((x2-1)^2+(x4-1)^2)+19.8*(x2-1)*(x4-1)\
                \n  x*=(1; 1; 1; 1)\
            \n6.0.1*(12+x1^2+(1+x2^2)/x1^2+(x1^2*x2^2+100)/(x1^4*x2^4))\
            \n x*=(1.743; 2.036)\
            \nTo select example function type its number\n";
    int selection;
    cin>>selection;
    switch(selection)
    {
    case 1:
        return string("x0^3+x1^2-3*x0-2*x1+2");
        break;
    case 2:
        return string("8*x0^2+4*x0*x1+5*x1^2");
        break;
    case 3:
        return string("4*x0^2+3*x1^2-4*x0*x1+x0");
        break;
    case 4:
        return string("(1.5-x1*(1-x2))^2+(2.25-x1*(1-x2^2))^2 +(2.625-x1*(1-x2^3))^2");
        break;
    case 5:
        return string("100*(x2-x1^2)^2+(1-x1)^2+90*(x4-x3^2)^2\
                      +(1-x3)^3+10.1*((x2-1)^2+(x4-1)^2)+19.8*(x2-1)*(x4-1)");
        break;
    case 6:
        return string("0.1*(12+x1^2+(1+x2^2)/x1^2+(x1^2*x2^2+100)/(x1^4*x2^4))");
        break;
    default:
        string formula;
        cout<<"\n Write function:\n";
        cin>>formula;
        return formula;
        break;
    }
}

double y(MathVector X)
{

    return expression->Calculate(X);
    //return estimator.calculate(&X[0],X.Getlength());
}

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

     /*for(int i=0; i<G.Getlength(); i++)
     {
         cout<<"\nG["<<i<<"]=";
         cout<<G[i];
     }
     cout<<"\n </grad>\n";*/

    return G;
}

double dy(MathVector X, MathVector P)
{
    P.Normalize();
    /* cout<<"\ndy\n";
     for(int i=0; i<X.Getlength(); i++)
         {
             cout<<"\nX["<<i<<"]=";
             cout<<X[i];
         }*/
    MathVector  G(X.Getlength());
    G = grad(X);
    return G*P;
}

MathVector DFP(MathVector X0)
{
    MathVector X=X0;
    MathVector Xprev = X;
    MathVector P(X0.Getlength());
    double alpha;
    Matrix A(X0.Getlength(), X0.Getlength());
    for(int i=0; i<A.rows; i++)
    {
        for(int j=0; j<A.collumns; j++)
        {
            A[i][j]=0;
        }
    }
    int k=1;
    for(int i=0; i< 30; i++)
    {
        cout<<"\nk="<<k<<endl;
        //Xprev =X;
        //шаг 1 - найти квазиньютоновское направление
        if(k%2==1)
        {
            //A = Matrix(X0.Getlength(), X0.Getlength());
            for(int d=0; d<A.rows; d++)
            {
                for(int j=0; j<A.collumns; j++)
                {
                    A[d][j]=0;
                }
            }

            for(int r=0;r<X0.Getlength();r++)
                A[r][r]=1;
        }

        else
        {
            MathVector dX = X-Xprev;
            //cout<<"dX="<<dX.ToString();
            MathVector Gamma = grad(X) - grad(Xprev);
            //cout<<"\nGamma="<<Gamma.ToString();
            MathVector S = ((A * Matrix(Gamma))).ToVector();
            //cout<<"\ns="<<S.ToString();
            Matrix Numerator1 = Matrix(dX)* (Matrix(dX).transp());
            //cout<<"\n Numerator1="<<Numerator1.ToString();
            Matrix Numarator2 = Matrix(S)* (Matrix(S).transp());
            //cout<<"\n Numerator2="<<Numarator2.ToString();
            double Denominator1= (dX*Gamma);
            //cout<<"\n Denominator1="<<Denominator1;
            double Denominator2= (S*Gamma);
            //cout<<"\n Denominator2="<<Denominator2;
            //cout<<"\n Numerator1*Denominator1 ="<<(Numerator1*Denominator1).ToString();
            //cout<<"\n Numerator2*Denominator2 ="<<(Numarator2*Denominator2).ToString();
            //cout<<"\n A="<<A.ToString();
            //A = A + Numerator1/Denominator1;
            //cout<<"\n A="<<A.ToString();
            //A = A - Numarator2/Denominator2;
            //cout<<"\n A="<<A.ToString();
            A =  A + (Matrix(dX)* (Matrix(dX).transp()))/(dX*Gamma) - (Matrix(S)* (Matrix(S).transp()))/(S*Gamma);
        }


        //шаг 2 - построить направление квазньютоновского поиска
        Matrix G= Matrix(grad(X));
        //G=G.transp();
        //cout<<"\nG"<<G.ToString();
        //cout<<"\nA="<<A.ToString();



        Matrix Pmatr = (-A);
        Pmatr = Pmatr*G;
        P=( Pmatr).ToVector();
        //cout<<"\nP="<<P.ToString();

        //шаг 3 - нати alphak
        alpha=LAB3_VECTOR::lab3(X,P,y,dy,eps*eps);
        //cout<<"\nalpha="<<alpha;

        //шаг 4 найти X
        Xprev = X;
        X =  X+alpha*P;
        k++;
        //шаг 5 -  ќѕ
        if(grad(X).norma()<=eps )
        {
            cout<<"\nDFP k="<<k;
            return X;
        }
        cout<<"\nX="<<X.ToString();
        cout<<"\nk="<<k<<endl;
       // getch();
    }
    return X;
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



        // estimator.compile(formula.c_str());

        int arguments;
        //arguments = estimator.getArguments();
        arguments = expression->variablesNum;
        cout<<"\nVariables num = "<<arguments;

        MathVector X0(arguments);
        for(int i=0; i<arguments; i++)
        {
            cout<<"\nX0["<<i<<"]=";
            cin>>X0[i];
        }

        cout<<"\n y(x0)="<<expression->Calculate(X0);

        cout<<"\neps = ";
        cin>>eps;

        //MathVector X = Portan2(X0);
        MathVector X = DFP(X0);
        for(int i=0; i<X.Getlength(); i++)
            cout<<"\n"<<X[i];
    }
    catch(Exception& e)
    {
        printf("\n%s\n",e.what());
    }
    getch();
    return 0;
}
