#ifndef __kcalc_hpp__
#define __kcalc_hpp__

#include <iostream>
#include <sstream>

namespace kcalc
{

/// Main entry point to the `kcalc` application.
int run(int argc, char* argv[]);


/// REPL (read-eval-print loop) for expression evaluation.
/// @param prompt Prompt symbol, if any.
/// @param inputStream the stream with the incoming text
/// @param outputStream the stream to print the output to
void repl(const std::string& prompt = "",
          std::istream& inputStream = std::cin,
          std::ostream& outputStream = std::cout);


/// Evaluates an expression given in prefix format.
/// The expression is assumed to be valid. Operands are assumed to be positive
/// integer numbers. Result is returned in the desired type, by default as
/// float. The reading stops after the first complete expression has been read
/// in. Any superfluous content is ignored.
/// @param T the type of the result of the expression
/// @param expression the expression in prefix format
/// @return the value of the expression
template<class T = float>
T evalPrefixExpr(const std::string& expression);


/// Evaluates an expression coming on a stream.
/// The expression is assumed to be valid. Operands are assumed to be positive
/// integer numbers. Result is returned in the desired type, by default as
/// float. The reading stops after the first complete expression has been read
/// in. Any following input is not processed, the "cursor" stays at the end of
/// the expression in the stream.
/// @param T the type of the result of the expression
/// @param inputStream the input stream from where the expression is read in
/// @return the value of the expression
template<class T = float>
T evalPrefixExpr(std::istream& inputStream);


template<class T>
T evalPrefixExpr(const std::string& expression)
{
    std::stringstream strStream(expression);
    return evalPrefixExpr<T>(strStream);
}


template <class T>
T evalPrefixExpr(std::istream& inputStream)
{
    std::string nextToken;
    inputStream >> nextToken;

    if (nextToken == "+"
        || nextToken == "-"
        || nextToken == "*"
        || nextToken == "/")
    {
        T leftOpValue = evalPrefixExpr<T>(inputStream);
        T righttOpValue = evalPrefixExpr<T>(inputStream);
        switch (nextToken[0])
        {
        case '+':
            return leftOpValue + righttOpValue;
        case '-':
            return leftOpValue - righttOpValue;
        case '*':
            return leftOpValue * righttOpValue;
        case '/':
        default:
            return leftOpValue / righttOpValue;
        }
    }

    /// According to the specification of the exercise, numbers in input
    /// can be assumed to be positive integers. Hence, no exception handling.
    T value = std::stoi(nextToken);

    return value;
}

}

#endif
