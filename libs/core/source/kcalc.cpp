#include <cstdlib>
#include <iostream>

#include "kcalc.hpp"

namespace kcalc
{

void printUsage()
{
    std::cout <<
        "\n"
        "./kcalc [--infix|--prefix]\n"
        "\n"
        "This program reads arithmetic expressions from the standard input and "
        "prints their result to the standard output. The expressions can be "
        "either in prefix or fully parenthesised infix format.\n"
        "\n"
        "The default syntax format is infix.\n"
        "\n";
}

int run(int argc, char* argv[])
{
    auto expressionFormat = ExpressionFormat::INFIX;

    if (argc == 2)
    {
        auto arg2 = std::string{argv[1]};
        if (arg2 == "--prefix")
        {
            expressionFormat = ExpressionFormat::PREFIX;
        }
        else if (arg2 != "--infix")
        {
            std::cout << "Invalid command line argument." << std::endl;
            printUsage();
            return EXIT_FAILURE;
        }
    }
    else if (argc != 1)
    {
        std::cout << "Invalid command line arguments." << std::endl;
        printUsage();
        return EXIT_FAILURE;
    }

    repl(expressionFormat);

    return EXIT_SUCCESS;
}


void repl(ExpressionFormat expressionFormat,
          const std::string& prompt,
          std::istream& inputStream,
          std::ostream& outputStream)
{
    std::string line;
    outputStream << prompt;
    while (std::getline(inputStream, line))
    {
        auto value = evalExpr(expressionFormat, line);
        outputStream << value << std::endl << prompt;
    }
}


float evalExpr(ExpressionFormat expressionFormat,
               const std::string& expression)
{
    return expressionFormat == ExpressionFormat::PREFIX
               ? evalPrefixExpr(expression)
               : evalInfixExpr(expression);
}

}
