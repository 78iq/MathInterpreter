#include <iostream>
#include <string>
#include "Expression.h"

int main()
{
    std::string expression;
    Expression exp;
    do
    {
        std::cout << "input a math expression:\n";
        getline(std::cin, expression);

        exp.newExpression(expression);
        std::cout << exp.getResult() << std::endl;


        std::cout << std::endl << "keep going? y/n";
        std::cin >> expression;
        std::cin.ignore();

    }while(expression == "y");
    return 0;
}
