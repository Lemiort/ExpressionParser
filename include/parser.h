#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

/*using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;*/
#include <string>
#include <vector>
#include <list>
#include <stack>
using namespace std;

namespace Parser
{
    class Parser
    {

       // static Stack<Operator> operators;
       // static Stack<Expression> expression;
       private:
        static int GetOperatorPriority(string str)
        {
            int priority=0;
            if(str==string("+"))
            {
                priority = 1;
            }
            else if( str == string("-"))
            {
                priority = 1;
            }
            else if(str == string("*"))
            {
                priority = 2;
            }
            else if (str == string("/"))
            {
                priority = 2;
            }
            else if (str == string("^"))
            {
                priority = 3;
            }
            return priority;
        }
        public: static bool IsOperator(string str)
        {
            if (str== string("+") || str == string("-") || str == string("*") ||
                    str == string("/") || str ==string("^"))
                return true;
            else
                return false;
        }
        /// <summary>
        /// Унарные функции
        /// </summary>
        /// <param name="str">строка</param>
        /// <returns></returns>
        public: static bool IsFunction(string str)
        {
            if (str == string("log") || str == string("log10") ||
                   str == string("sin") || str == string("cos")
                   || str == string("tan")|| str == string("atan")
                   || str == string("acos") || str == string("asin") )
                return true;
            else
                return false;
        }
        public: static bool IsConstant(string str)
        {
            if (str == string("e") || str == string("Pi"))
                return true;
            else
                return false;
        }
        public: static std::vector<string> StringToTokens(string str)
        {
            std::vector<string> result;
            string temp ="";
            for (unsigned int i = 0; i < str.length(); i++)
            {
                switch(str[i])
                {
                    case '(':
                        result.push_back(temp);
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    case ')':
                        result.push_back(temp);
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    case '+':
                        result.push_back(temp);
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    case '-':
                        result.push_back(temp);
                       /* //если это первый символ - добавляем 0 в начало
                        if (result.Count == 0)
                            result.Add("0");
                        //не первый символ - сохраняем всё
                        else
                            result.Add(temp);
                        //после скобки - добавляем 0
                        if (result.Last().Equals("("))
                            result.Add("0");*/
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    case '/':
                        result.push_back(temp);
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    case '*':
                        result.push_back(temp);
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    case '^':
                        result.push_back(temp);
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    case '\0':
                        result.push_back(temp);
                        temp =  "";
                        temp += str[i];
                        result.push_back(temp);
                        temp = "";
                        break;
                    default:
                        temp += str[i];
                        break;
                }
            }

            //обработка одного символа
            if (result.size()!= 0)
            {
                if (result[result.size()-1] !=string(temp))
                {
                    result.push_back(temp);
                }
            }
            else
                result.push_back(temp);

            std::vector<string> result2;
            string prev="start";
            for(unsigned int i=0; i<result.size();i++)
            {
                if (result[i] != string(""))
                    result2.push_back(result[i]);
                else if (prev == string("(") || prev == string("start"))
                {
                    result2.push_back("0");
                }
                prev = result[i];
            }
            return result2;
        }
        public: static std::vector<string> TokensToPolskaInvers(std::vector<string> source)
        {
            std::stack<string> sstack;
            std::vector<string> result;
            for(unsigned int i=0; i<source.size();i++)
            {
                string str = source[i];
                //символ является открывающей скобкой
                if (str == string("("))
                    //помещаем в стек
                    sstack.push(str);
                //символ является закрывающей скобкой
                else if(str == string(")"))
                {
                    //пока открывающим элементом не станет открывающая скобка
                    while(sstack.top() != string("("))
                    {
                        //выталкиваем элементы из стека в выходную строку.
                        result.push_back(sstack.top());
                        sstack.pop();
                    }
                    //выталкиваем открывающую скобку
                    sstack.pop();
                }
                //символ является функцией
                else if (IsFunction(str))
                {
                    //помещаем в стек
                    sstack.push(str);
                }
                //символ явлется левоассоциативным оператором
                else if (IsOperator(str))
                {

                    //пока приоритет оператора
                    //меньше либо равен приоритету оператора,
                    //находящегося на вершине стека
                    if (sstack.size() != 0)
                        while (GetOperatorPriority(str) <= GetOperatorPriority(sstack.top()))
                        {
                            //выталкиваем верхние элементы стека в выходную строку;
                            result.push_back(sstack.top());
                            sstack.pop();
                            //если пуст, выйти
                            if (sstack.size() == 0)
                                break;
                        }

                    //помещаем оператор в стек
                    sstack.push(str);
                }
                //число
                else
                {
                    result.push_back(str);
                }
            }
            //выталкиваем всё оставлшееся
            while (true)
            {
                if (sstack.size() == 0)
                    break;
                else
                {
                    result.push_back(sstack.top());
                    sstack.pop();
                }
            }
            //result.Add(stack.Peek());
            return result;
        }
    };
}


#endif // PARSER_H_INCLUDED
