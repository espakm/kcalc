#ifndef __kcalc_hpp__
#define __kcalc_hpp__

#include <iostream>
#include <sstream>

namespace kcalc
{

/// Main entry point to the `kcalc` application.
int run(int argc, char* argv[]);


/// REPL (read-eval-print loop) for prefix expression evaluation.
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


/// Evaluates an expression coming on a stream in prefix format.
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


/// Evaluates an expression given in infix format.
/// The expression is assumed to be valid. Operands are assumed to be positive
/// integer numbers. Result is returned in the desired type, by default as
/// float. The reading stops after the first complete expression has been read
/// in. Any superfluous content is ignored.
/// @param T the type of the result of the expression
/// @param expression the expression in infix format
/// @return the value of the expression
template<class T = float>
T evalInfixExpr(const std::string& expression);


/// Evaluates an expression coming on a stream in infix format.
/// The expression is assumed to be valid. Operands are assumed to be positive
/// integer numbers. Result is returned in the desired type, by default as
/// float. The reading stops after the first complete expression has been read
/// in. Any following input is not processed, the "cursor" stays at the end of
/// the expression in the stream.
/// @param T the type of the result of the expression
/// @param inputStream the input stream from where the expression is read in
/// @return the value of the expression
template<class T = float>
T evalInfixExpr(std::istream& inputStream);


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
        auto leftOpValue = evalPrefixExpr<T>(inputStream);
        auto rightOpValue = evalPrefixExpr<T>(inputStream);
        switch (nextToken[0])
        {
        case '+':
            return leftOpValue + rightOpValue;
        case '-':
            return leftOpValue - rightOpValue;
        case '*':
            return leftOpValue * rightOpValue;
        //case '/':
        default:
            return leftOpValue / rightOpValue;
        }
    }

    /// According to the specification of the exercise, numbers in input
    /// can be assumed to be positive integers. Hence, no exception handling.
    T value = std::stoi(nextToken);

    return value;
}


template<class T>
T evalInfixExpr(const std::string& expression)
{
    std::stringstream strStream(expression);
    return evalInfixExpr<T>(strStream);
}


template <class T>
T evalInfixExpr(std::istream& inputStream)
{
    std::string nextToken;
    inputStream >> nextToken;

    if (nextToken == "(")
    {
        auto leftOpValue = evalInfixExpr<T>(inputStream);

        inputStream >> nextToken;
        auto operator_ = nextToken;

        auto rightOpValue = evalInfixExpr<T>(inputStream);

        /// Consume and discard the closing parenthesis.
        inputStream >> nextToken;

        switch (operator_[0])
        {
        case '+':
            return leftOpValue + rightOpValue;
        case '-':
            return leftOpValue - rightOpValue;
        case '*':
            return leftOpValue * rightOpValue;
        //case '/':
        default:
            return leftOpValue / rightOpValue;
        }
    }

    /// According to the specification of the exercise, numbers in input
    /// can be assumed to be positive integers. Hence, no exception handling.
    T value = std::stoi(nextToken);

    return value;
}

}

#endif
