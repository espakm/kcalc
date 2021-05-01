#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "kcalc.hpp"


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


TEST_CASE("test kcalc::evalPrefixExpr()")
{
    using namespace std::literals;
    using namespace kcalc;

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
}
