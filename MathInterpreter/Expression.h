#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>


class Expression
{
public:
    Expression();
    Expression(std::string);
    virtual ~Expression();

    void newExpression(std::string);

    std::string getExpression(){ return expression; }
    double getResult(){ return result; }

protected:
private:
    double result;
    std::string expression;

    std::string numberRegex = "(0|([1-9][0-9]*))(\\.[0-9]*)?";
    std::string operatorsRegex = "[\\+|[-]|\\^|\\*|\\/]";

    void reformat();
    double calculate(std::string);
    bool checkValid();
};

#endif // EXPRESSION_H
