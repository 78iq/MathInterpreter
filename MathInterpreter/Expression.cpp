#include "Expression.h"
#include <regex>
#include <iostream>
#include <vector>
#include <cmath>

Expression::Expression()
{
    result = 0.0;
}

Expression::~Expression()
{
    //dtor
}

Expression::Expression(std::string exp)
{
    newExpression(exp);
}

void Expression::newExpression(std::string exp)
{
    expression = exp;
    reformat();
    if(checkValid())
        result = calculate(expression);
    else
        result = 0.0;
}

double Expression::calculate(std::string exp)
{
    while(exp.rfind('(') != std::string::npos)
    {
        int s = exp.rfind('('), e = exp.find(')', exp.rfind('('));
        std::string x = exp.substr(s + 1, e - s - 1);

        double t = calculate(x);

        exp.replace(s, e - s + 1, std::to_string(t));
        std::cout << exp << std::endl;
    }


    std::vector<double> numbers;
    std::vector<char> operators;

    std::string temp = exp;

    std::regex r(numberRegex);
    std::smatch m;
    while(std::regex_search(temp, m, r))
    {
        numbers.push_back(stod(m[0]));
        temp = m.suffix();
    }

    temp = exp;

    r = operatorsRegex;
    while(std::regex_search(temp, m, r))
    {
        operators.push_back(m.str()[0]);
        temp = m.suffix().str();
    }


    //handle exponents
    for(size_t i = 0; i < operators.size(); i++)
    {
        if(operators[i] == '^')
        {
            operators.erase(operators.begin() + i);
            numbers[i] = pow(numbers[i], numbers[i + 1]);
            numbers.erase(numbers.begin() + i + 1);
            i--;
        }
    }

    //handle multiplication and division arithmetic
    for(size_t i = 0; i < operators.size(); i++)
    {
        if(operators[i] == '*')
        {
            operators.erase(operators.begin() + i);
            numbers[i] *= numbers[i + 1];
            numbers.erase(numbers.begin() + i + 1);
            i--;
        }
        if(operators[i] == '/')
        {
            operators.erase(operators.begin() + i);
            numbers[i] /= numbers[i + 1];
            numbers.erase(numbers.begin() + i + 1);
            i--;
        }
    }


    //handle addition and subtraction arithmetic
    for(size_t i = 0; i < operators.size(); i++)
    {
        if(operators[i] == '+')
        {
            operators.erase(operators.begin() + i);
            numbers[i] += numbers[i + 1];
            numbers.erase(numbers.begin() + i + 1);
            i--;
        }
        if(operators[i] == '-')
        {
            operators.erase(operators.begin() + i);
            numbers[i] -= numbers[i + 1];
            numbers.erase(numbers.begin() + i + 1);
            i--;
        }
    }

    return numbers[0];
}

void Expression::reformat()
{
    for(size_t i = 0; i < expression.length(); i++)
    {
        if(expression[i] == ' ')
        {
            expression.erase(expression.begin() + i);
            i--;
        }
    }
}

bool Expression::checkValid()
{
    //count open and closed brackets against each other
    int counter = 0;
    bool p_counter = false;
    bool iterated = false;

    do
    {
        counter = 0;
        p_counter = false;

        for(size_t i = 0; i < expression.length(); i++)
        {
            if(expression[i] == '(')
                counter++;
            else if(expression[i] == ')')
                counter--;
            if(counter < 0)
            {
                if(!iterated)
                {
                    std::cout << "too many closing parentheses.\n";
                    iterated = true;
                }
                p_counter = true;
                expression = '(' + expression;
                break;
            }
        }

        if(counter != 0)
        {
            if(!iterated)
            {
                std::cout << "too many opening parentheses.\n";
                iterated = true;
            }
            p_counter = true;
            expression += ')';
        }
    }while(p_counter);

    std::regex expressionRegex("\\(*((0|([1-9][0-9]*))(\\.[0-9]*)?)\\)*([\\-\\+\\*\\/\\^]\\(*((0|([1-9][0-9]*))(\\.[0-9]*)?)\\)*)*");
    std::smatch m;
    std::regex_search(expression, m, expressionRegex);

    if(m[0] != expression)
    {
        std::cout << "improper formatting.\n";
        return false;
    }
    return true;
}
