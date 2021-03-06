#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "kcalc.hpp"

using namespace std::literals;

namespace kcalc
{

TEST_CASE("test kcalc::run() invalid args")
{
    int argc = 2;
    char args[][256] = {
        "./kcalc",
        "dummy arg"
    };
    char* argv[] = {
        args[0],
        args[1],
        nullptr
    };
    int exit_status = kcalc::run(argc, argv);

    REQUIRE_EQ(exit_status, EXIT_FAILURE);
}


TEST_CASE("test kcalc::evalPrefixExpr(const std::string&)")
{
    REQUIRE_EQ(evalPrefixExpr("3"s), 3.0f);
    REQUIRE_EQ(evalPrefixExpr("+ 1 2"s), 3.0f);
    REQUIRE_EQ(evalPrefixExpr("+ 1 * 2 3"s), 7.0f);
    REQUIRE_EQ(evalPrefixExpr("+ * 1 2 3"s), 5.0f);
    REQUIRE_EQ(evalPrefixExpr("- / 10 + 1 1 * 1 2"s), 3.0f);
    REQUIRE_EQ(evalPrefixExpr("- 0 3"s), -3.0f);
    REQUIRE_EQ(evalPrefixExpr("/ 3 2"s), 1.5f);

    REQUIRE_EQ(evalPrefixExpr<int>("3"s), 3);
    REQUIRE_EQ(evalPrefixExpr<int>("+ 1 2"s), 3);
    REQUIRE_EQ(evalPrefixExpr<int>("+ 1 * 2 3"s), 7);
    REQUIRE_EQ(evalPrefixExpr<int>("+ * 1 2 3"s), 5);
    REQUIRE_EQ(evalPrefixExpr<int>("- / 10 + 1 1 * 1 2"s), 3);
    REQUIRE_EQ(evalPrefixExpr<int>("- 0 3"s), -3);
    REQUIRE_EQ(evalPrefixExpr<int>("/ 3 2"s), 1);

    REQUIRE_EQ(evalPrefixExpr("+1 2"s), 3.0f);
    REQUIRE_EQ(evalPrefixExpr("+1*2 3"s), 7.0f);
    REQUIRE_EQ(evalPrefixExpr("+*1 2 3"s), 5.0f);
    REQUIRE_EQ(evalPrefixExpr("-/10+1 1*1 2"s), 3.0f);
    REQUIRE_EQ(evalPrefixExpr("-0 3"s), -3.0f);
    REQUIRE_EQ(evalPrefixExpr("/3 2"s), 1.5f);

    REQUIRE_EQ(evalPrefixExpr<int>("+1 2"s), 3);
    REQUIRE_EQ(evalPrefixExpr<int>("+1*2 3"s), 7);
    REQUIRE_EQ(evalPrefixExpr<int>("+*1 2 3"s), 5);
    REQUIRE_EQ(evalPrefixExpr<int>("-/10+1 1*1 2"s), 3);
    REQUIRE_EQ(evalPrefixExpr<int>("-0 3"s), -3);
    REQUIRE_EQ(evalPrefixExpr<int>("/3 2"s), 1);

    REQUIRE_THROWS_AS(evalPrefixExpr("wrong"), MalformedExpression);
    REQUIRE_THROWS_AS(evalPrefixExpr("+"), MalformedExpression);
    REQUIRE_THROWS_AS(evalPrefixExpr("+ 1"), MalformedExpression);
    REQUIRE_THROWS_AS(evalPrefixExpr("1 2"), MalformedExpression);
    REQUIRE_THROWS_AS(evalPrefixExpr("+ 1 2 3"), MalformedExpression);
}


TEST_CASE("test kcalc::evalInfixExpr(const std::string&)")
{
    REQUIRE_EQ(evalInfixExpr("3"s), 3.0f);
    REQUIRE_EQ(evalInfixExpr("( 1 + 2 )"s), 3.0f);
    REQUIRE_EQ(evalInfixExpr("( 1 + ( 2 * 3 ) )"s), 7.0f);
    REQUIRE_EQ(evalInfixExpr("( ( 1 * 2 ) + 3 )"s), 5.0f);
    REQUIRE_EQ(evalInfixExpr("( ( ( 1 + 1 ) / 10 ) - ( 1 * 2 ) )"s), -1.8f);
    REQUIRE_EQ(evalInfixExpr("(0 - 3)"s), -3.0f);

    REQUIRE_EQ(evalInfixExpr<int>("3"s), 3);
    REQUIRE_EQ(evalInfixExpr<int>("( 1 + 2 )"s), 3);
    REQUIRE_EQ(evalInfixExpr<int>("( 1 + ( 2 * 3 ) )"s), 7);
    REQUIRE_EQ(evalInfixExpr<int>("( ( 1 * 2 ) + 3 )"s), 5);
    REQUIRE_EQ(evalInfixExpr<int>("( ( ( 1 + 1 ) / 10 ) - ( 1 * 2 ) )"s), -2);
    REQUIRE_EQ(evalInfixExpr<int>("(0 - 3)"s), -3);

    REQUIRE_EQ(evalInfixExpr("(1+2)"s), 3.0f);
    REQUIRE_EQ(evalInfixExpr("(1+(2*3))"s), 7.0f);
    REQUIRE_EQ(evalInfixExpr("((1*2)+3)"s), 5.0f);
    REQUIRE_EQ(evalInfixExpr("(((1+1)/10)-(1*2))"s), -1.8f);
    REQUIRE_EQ(evalInfixExpr("(0-3)"s), -3.0f);

    REQUIRE_EQ(evalInfixExpr<int>("(1+2)"s), 3);
    REQUIRE_EQ(evalInfixExpr<int>("(1+(2*3))"s), 7);
    REQUIRE_EQ(evalInfixExpr<int>("((1*2)+3)"s), 5);
    REQUIRE_EQ(evalInfixExpr<int>("(((1+1)/10)-(1*2))"s), -2);
    REQUIRE_EQ(evalInfixExpr<int>("(0-3)"s), -3);

    REQUIRE_THROWS_AS(evalInfixExpr("wrong"), MalformedExpression);
    REQUIRE_THROWS_AS(evalInfixExpr("+ 1 2"), MalformedExpression);
    REQUIRE_THROWS_AS(evalInfixExpr("1 +"), MalformedExpression);
    REQUIRE_THROWS_AS(evalInfixExpr("1 + 2"), MalformedExpression);
    REQUIRE_THROWS_AS(evalInfixExpr("( 1 + 2"), MalformedExpression);
    REQUIRE_THROWS_AS(evalInfixExpr("(1+2"), MalformedExpression);
}


TEST_CASE("test kcalc::repl()")
{
    SUBCASE("prefix")
    {
        auto inputStream = std::stringstream{
            "3\n"
            "+ 1 2\n"
            "+ 1 * 2 3\n"
            "+ * 1 2 3\n"
            "- / 10 + 1 1 * 1 2\n"
            "- 0 3\n"
            "/ 3 2\n"
            "-/10+1 1*1 2\n"
        };

        auto outputStream = std::stringstream{};

        SUBCASE("without prompt")
        {
            auto expectedOutput =
                "3\n"
                "3\n"
                "7\n"
                "5\n"
                "3\n"
                "-3\n"
                "1.5\n"
                "3\n"s;

            repl(ExpressionFormat::PREFIX, ""s, inputStream, outputStream);

            REQUIRE_EQ(outputStream.str(), expectedOutput);
        }

        SUBCASE("with caret prompt")
        {
            auto expectedOutput =
                "> 3\n"
                "> 3\n"
                "> 7\n"
                "> 5\n"
                "> 3\n"
                "> -3\n"
                "> 1.5\n"
                "> 3\n"
                "> "s;

            repl(ExpressionFormat::PREFIX, "> "s, inputStream, outputStream);

            REQUIRE_EQ(outputStream.str(), expectedOutput);
        }
    }

    SUBCASE("infix")
    {
        auto inputStream = std::stringstream{
            "( 1 + 2 )\n"
            "( 1 + ( 2 * 3 ) )\n"
            "( ( 1 * 2 ) + 3 )\n"
            "( ( ( 1 + 1 ) / 10 ) - ( 1 * 2 ) )\n"
            "(((1+1)/10)-(1*2))\n"
        };

        auto outputStream = std::stringstream{};

        SUBCASE("without prompt")
        {
            auto expectedOutput =
                "3\n"
                "7\n"
                "5\n"
                "-1.8\n"
                "-1.8\n"s;

            repl(ExpressionFormat::INFIX, ""s, inputStream, outputStream);

            REQUIRE_EQ(outputStream.str(), expectedOutput);
        }

        SUBCASE("with caret prompt")
        {
            auto expectedOutput =
                "> 3\n"
                "> 7\n"
                "> 5\n"
                "> -1.8\n"
                "> -1.8\n"
                "> "s;

            repl(ExpressionFormat::INFIX, "> "s, inputStream, outputStream);

            REQUIRE_EQ(outputStream.str(), expectedOutput);
        }
    }
}

}
