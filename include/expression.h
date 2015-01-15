#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <stack>
#include <map>
#include <parser.h>
#include <cstdlib>
#include <MathVector.h>


/*using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;**/

namespace Function
{
    double ConvertToDouble(string str)
    {
        stringstream ss;
        ss<<str;
        double result;
        ss>>result;
        return result;
    }

    class FormatException
    {

    };

    double ParseToDouble(string str)
    {
        for(unsigned i=0; i< str.length();i++)
        {
            if(str[i] >'0' && str[i] < '1')
                if(str[i] != ','|| str[i]!='.')
                    throw new FormatException();
        }
        return ConvertToDouble(str);
    }

    class Expression
    {
        //Dictionary<string, double> arguments;
        //Dictionary<string,string> variables;

        std::map<string,double> arguments;
        std::map<string,string> variables;


        std::vector<string> expression;
        public: int variablesNum;
        /// <summary>
        ///
        /// </summary>
        /// <param name="source">Исходная запись в польской нотации</param>
        public: Expression(std::vector<string> source)
        {
            expression = source;
            //arguments;// = new Dictionary<string,double>();
            //variables;// = new Dictionary<string,string>();
            double value=0.0;
            string name="";
            for(unsigned i=0;i<source.size();i++)
            {
                string str = source[i];
                //одна из констант
                if (Parser::Parser::IsConstant(str))
                {
                    if (str == string("Pi"))
                    {
                        name = str;
                        value = acos(-1.0);
                    }
                    else
                    {
                        name = str;
                        value = exp(1.0);
                    }
                }
                //число и не функция
                else if (!Parser::Parser::IsOperator(str) && !Parser::Parser::IsFunction(str))
                {
                    /*try
                    {*/
                        //value = ParseToDouble(str);
                        char* endptr;
                        value = strtod(str.c_str(),&endptr);
                        //cout<<"\n value="<< value;
                        //cout<<"\n endptr"<<endptr;
                        if(endptr==str.c_str())
                        {
                            //throw new FormatException();
                            //cout<<"\nThere must be exception  ";
                            value = 0;
                            name = str;
                            //cout<<name;
                            if(variables.find(str) == variables.end())
                            {
                                variables.insert(pair<string,string>(str,str));
                            }
                        }
                        else
                        {
                            name = str;
                        }
                    //}
                    /*catch( FormatException)
                    {

                        value = 0;
                        name = str;
                        if(variables.find(str) != variables.end())
                        {
                            variables.insert(pair<string,string>(str,str));
                        }
                    }*/
                }
                if(arguments.find(name) == arguments.end())
                    arguments.insert(pair<string,double>(name, value));
            }
            variablesNum = variables.size();
        }
       /* public void SetVariables(List<double> values)
        {
            int i = 0;
            foreach(KeyValuePair<string,string> kvp  in variables)
            {
                arguments[kvp.Key] = values[i];
                i++;
            }
        }*/
        public: double Calculate(std::vector<double> values)
        {
            int i = 0;
            //for(KeyValuePair<string, string> kvp in variables
            for(map<string, string>:: iterator it = variables.begin(); it!=variables.end(); it++)
            {

                arguments[it->first] = values[i];
               // arguments[kvp.Key] = values[i];
                i++;
            }
            stack<double> sstack;
            for (unsigned  j = 0; j < expression.size(); j++)
            {
                //обработка входного символа
                //операнд
                if (!Parser::Parser::IsOperator(expression[j]) && !Parser::Parser::IsFunction(expression[j]))
                {
                    //помещаем операнд в стек
                    sstack.push(arguments[expression[j]]);
                }
                //функция
                else if (Parser::Parser::IsFunction(expression[j]))
                {
                    //левый операнд
                    double d = sstack.top();
                    sstack.pop();
                    if (expression[j] == string("cos"))
                        sstack.push(cos(d));
                    else if (expression[j] == string("sin"))
                        sstack.push(sin(d));
                    else if (expression[j] ==  string("tan"))
                        sstack.push(tan(d));
                    else if (expression[j] == string("atan"))
                        sstack.push(atan(d));
                    else if (expression[j] == string("acos"))
                        sstack.push(acos(d));
                    else if (expression[j] == string("asin"))
                        sstack.push(asin(d));
                    else if (expression[j] == string("log"))
                        sstack.push(log(d));
                    else if (expression[j] == string("log10"))
                        sstack.push(log10(d));
                }
                //знак операции
                else
                {
                    //правый операнд
                    double d1 = sstack.top();
                    sstack.pop();
                    //левый операнд
                    double d2 = sstack.top();
                    sstack.pop();
                    if (expression[j] == string("+"))
                        sstack.push(d2 + d1);
                    else if (expression[j] == string("-"))
                        sstack.push(d2 - d1);
                    else if (expression[j] == string("*"))
                        sstack.push(d2 * d1);
                    else if (expression[j] == string("/"))
                        sstack.push(d2 / d1);
                    else if (expression[j] == string("^"))
                        sstack.push(pow(d2, d1));
                }

            }
            double result = sstack.top();
            sstack.pop();
            return result;
        }

        public: double Calculate(MathVector values)
        {
            int i = 0;
            //for(KeyValuePair<string, string> kvp in variables
            for(map<string, string>:: iterator it = variables.begin(); it!=variables.end(); it++)
            {

                arguments[it->first] = values[i];
               // arguments[kvp.Key] = values[i];
                i++;
            }
            stack<double> sstack;
            for (unsigned  j = 0; j < expression.size(); j++)
            {
                //обработка входного символа
                //операнд
                if (!Parser::Parser::IsOperator(expression[j]) && !Parser::Parser::IsFunction(expression[j]))
                {
                    //помещаем операнд в стек
                    sstack.push(arguments[expression[j]]);
                }
                //функция
                else if (Parser::Parser::IsFunction(expression[j]))
                {
                    //левый операнд
                    double d = sstack.top();
                    sstack.pop();
                    if (expression[j] == string("cos"))
                        sstack.push(cos(d));
                    else if (expression[j] == string("sin"))
                        sstack.push(sin(d));
                    else if (expression[j] ==  string("tan"))
                        sstack.push(tan(d));
                    else if (expression[j] == string("atan"))
                        sstack.push(atan(d));
                    else if (expression[j] == string("acos"))
                        sstack.push(acos(d));
                    else if (expression[j] == string("asin"))
                        sstack.push(asin(d));
                    else if (expression[j] == string("log"))
                        sstack.push(log(d));
                    else if (expression[j] == string("log10"))
                        sstack.push(log10(d));
                }
                //знак операции
                else
                {
                    //правый операнд
                    double d1 = sstack.top();
                    sstack.pop();
                    //левый операнд
                    double d2 = sstack.top();
                    sstack.pop();
                    if (expression[j] == string("+"))
                        sstack.push(d2 + d1);
                    else if (expression[j] == string("-"))
                        sstack.push(d2 - d1);
                    else if (expression[j] == string("*"))
                        sstack.push(d2 * d1);
                    else if (expression[j] == string("/"))
                        sstack.push(d2 / d1);
                    else if (expression[j] == string("^"))
                        sstack.push(pow(d2, d1));
                }

            }
            double result = sstack.top();
            sstack.pop();
            return result;
        }
    };
}


#endif // EXPRESSION_H_INCLUDED
