//#include "expressionEstimator.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <Matrix.h>
#include <MathVector.h>
#include <parser.h>
#include <conio.h>
#include <expression.h>
//#include <termios.h>

using namespace std;

//ExpressionEstimator estimator;
//std::auto_ptr<Function::Expression> expression;
Function::Expression* expression;
double eps;
int n;

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

int main()
{
    try
    {
        //ExpressionEstimator::Init();
        cout<<"\nType function to calculate\n";

        string formula;
        cin>>formula;

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

        cout<<"\n y(x0)="<<expression->Calculate(X0);

    }
    catch(Exception& e)
    {
        printf("\n%s\n",e.what());
    }
    getch();
    return 0;
}
