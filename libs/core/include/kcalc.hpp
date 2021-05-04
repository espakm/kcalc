#ifndef __kcalc_hpp__
#define __kcalc_hpp__

#include <iostream>
#include <iterator>
#include <regex>

namespace kcalc
{

/// Main entry point to the `kcalc` application.
int run(int argc, char* argv[]);


/// Exception type for expression syntax errors.
class MalformedExpression : public std::runtime_error
{
public:
    MalformedExpression(const std::string& message = std::string())
        : std::runtime_error(message)
    {
    }
};


/// Denotes the syntax format of an expression. Either prefix or infix.
enum class ExpressionFormat : uint8_t
{
    PREFIX,
    INFIX,
};


/// REPL (read-eval-print loop) for prefix/infix expression evaluation.
/// Results are calculated as real numbers (float).
/// @param expressionFormat the syntax format of the expressions
/// @param prompt Prompt symbol, if any.
/// @param inputStream the stream with the incoming text
/// @param outputStream the stream to print the output to
void repl(ExpressionFormat expressionFormat = ExpressionFormat::INFIX,
          const std::string& prompt = "",
          std::istream& inputStream = std::cin,
          std::ostream& outputStream = std::cout);


/// Evaluates an expression in a given syntax format to a real number.
/// The expression is assumed to be valid. Operands are assumed to be positive
/// integer numbers. Result is returned as a float number. (Any sub-expressions
/// are float.) The reading stops after the first complete expression has been
/// read in. Any superfluous content is ignored.
/// @param expression the expression in prefix format
/// @return the value of the expression
float evalExpr(ExpressionFormat expressionFormat,
               const std::string& expression);


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


/// Evaluates an expression in prefix format.
/// The tokens of the expression are provided by the iterator argument.
/// The expression is assumed to be valid. Operands are assumed to be positive
/// integer numbers. Result is returned in the desired type, by default as
/// float. The reading stops after the first complete expression has been read
/// in. Further tokens are not processed, even if the iterator is not at the
/// end.
/// @param T the type of the result of the expression
/// @param tokenIt the iterator that delivers the tokens of the expression
/// @return the value of the expression
template<class T = float>
T evalPrefixExpr(std::sregex_iterator& tokenIt);


/// Evaluates an expression in infix format.
/// The tokens of the expression are provided by the iterator argument.
/// The expression is assumed to be valid. Operands are assumed to be positive
/// integer numbers. Result is returned in the desired type, by default as
/// float. The reading stops after the first complete expression has been read
/// in. Further tokens are not processed, even if the iterator is not at the
/// end.
/// @param T the type of the result of the expression
/// @param tokenIt the iterator that delivers the tokens of the expression
/// @return the value of the expression
template <class T>
T evalInfixExpr(std::sregex_iterator& tokenIt);


template<class T>
T evalPrefixExpr(const std::string& expression)
{
    auto tokenRegex = std::regex{"\\d+|[\\+\\-\\*\\/]"};
    auto tokenIt = std::sregex_iterator{
        expression.begin(),
        expression.end(),
        tokenRegex};

    auto value = evalPrefixExpr<T>(tokenIt);

    if (tokenIt != std::sregex_iterator())
        throw MalformedExpression("Unexpected token after expression.");

    return value;
}


template<class T>
T evalInfixExpr(const std::string& expression)
{
    auto tokenRegex = std::regex{"\\d+|[\\+\\-\\*\\/\\(\\)]"};
    auto tokenIt = std::sregex_iterator{
        expression.begin(),
        expression.end(),
        tokenRegex};

    auto value = evalInfixExpr<T>(tokenIt);

    if (tokenIt != std::sregex_iterator())
        throw MalformedExpression("Unexpected token after expression.");

    return value;
}


template <class T>
T evalPrefixExpr(std::sregex_iterator& tokenIt)
{
    if (tokenIt == std::sregex_iterator())
        throw MalformedExpression("Unexpected end of expression.");

    auto nextToken = tokenIt++->str();

    if (nextToken == "+"
        || nextToken == "-"
        || nextToken == "*"
        || nextToken == "/")
    {
        auto operator_ = nextToken;

        auto leftOpValue = evalPrefixExpr<T>(tokenIt);
        auto rightOpValue = evalPrefixExpr<T>(tokenIt);
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

    try
    {
        return std::stoi(nextToken);
    }
    catch (const std::invalid_argument&)
    {
        throw MalformedExpression("Number expected.");
    }
}


template <class T>
T evalInfixExpr(std::sregex_iterator& tokenIt)
{
    if (tokenIt == std::sregex_iterator())
        throw MalformedExpression("Unexpected end of expression.");

    auto nextToken = tokenIt++->str();

    if (nextToken == "(")
    {
        auto leftOpValue = evalInfixExpr<T>(tokenIt);

        if (tokenIt == std::sregex_iterator())
            throw MalformedExpression("Unexpected end of expression.");

        auto operator_ = tokenIt++->str();

        auto rightOpValue = evalInfixExpr<T>(tokenIt);

        /// Consume and discard the closing parenthesis.

        if (tokenIt == std::sregex_iterator())
            throw MalformedExpression("Unexpected end of expression.");

        nextToken = tokenIt++->str();

        if (nextToken != ")")
            throw MalformedExpression("Closing paranthesis expected.");

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

    try
    {
        return std::stoi(nextToken);
    }
    catch (const std::invalid_argument&)
    {
        throw MalformedExpression("Number expected.");
    }
}

}

#endif
