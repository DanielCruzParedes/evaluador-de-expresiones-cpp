#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../includes/EvaluadorDeExpresiones.h"

// TESTS QUE DEBEN PASAR

TEST_CASE("Postfix evaluation: simple addition", "[evaluatePostfix]")
{
    vector<string> expr = {"3", "5", "+"};
    REQUIRE(evaluatePostfix(expr) == 8);
}

TEST_CASE("Postfix evaluation: simple substraction", "[evaluatePostfix]")
{
    vector<string> expr = {"10", "2", "-"};
    REQUIRE(evaluatePostfix(expr) == 8);
}

TEST_CASE("Postfix evaluation: simple multiplication", "[evaluatePostfix]")
{
    vector<string> expr = {"4", "5", "*"};
    REQUIRE(evaluatePostfix(expr) == 20);
}

TEST_CASE("Postfix evaluation: simple division", "[evaluatePostfix]")
{
    vector<string> expr = {"20", "4", "/"};
    REQUIRE(evaluatePostfix(expr) == 5);
}

TEST_CASE("Postfix evaluation: complex expression", "[evaluatePostfix]")
{
    vector<string> expr = {"2", "3", "+", "4", "*"};
    REQUIRE(evaluatePostfix(expr) == 20);
}

TEST_CASE("Postfix evaluation: exponentiation", "[evaluatePostfix]")
{
    vector<string> expr = {"2", "3", "^"};
    REQUIRE(evaluatePostfix(expr) == 8);
}

TEST_CASE("Postfix evaluation: modulo", "[evaluatePostfix]")
{
    vector<string> expr = {"10", "3", "%"};
    REQUIRE(evaluatePostfix(expr) == 1);
}

TEST_CASE("Postfix evaluation: complex with different operators", "[evaluatePostfix]")
{
    vector<string> expr = {"10", "5", "+", "2", "-"};
    REQUIRE(evaluatePostfix(expr) == 13);
}

TEST_CASE("Postfix evaluation: negative numbers", "[evaluatePostfix]")
{
    vector<string> expr = {"-5", "3", "+"};
    REQUIRE(evaluatePostfix(expr) == -2);
}

TEST_CASE("Postfix evaluation: mixed positive and negative numbers", "[evaluatePostfix]")
{
    vector<string> expr = {"10", "-3", "*"};
    REQUIRE(evaluatePostfix(expr) == -30);
}

// TESTS QUE DEBEN FALLAR

TEST_CASE("Postfix evaluation: division by zero", "[evaluatePostfix]")
{
    vector<string> expr = {"5", "0", "/"};
    REQUIRE(evaluatePostfix(expr) == 5); // Deberia dar error
}

TEST_CASE("Postfix evaluation: modulo with zero", "[evaluatePostfix]")
{
    vector<string> expr = {"10", "0", "%"};
    REQUIRE(evaluatePostfix(expr) == 10); // Debería dar error
}

TEST_CASE("Postfix evaluation: bad calculation", "[evaluatePostfix]")
{
    vector<string> expr = {"3", "2", "+"};
    REQUIRE(evaluatePostfix(expr) == 3); // Deberia dar error
}

TEST_CASE("Postfix evaluation: incorrect exponentiation", "[evaluatePostfix]")
{
    vector<string> expr = {"2", "3", "^"};
    REQUIRE(evaluatePostfix(expr) == 6); // Deberia ser 8
}

TEST_CASE("Postfix evaluation: wrong order of operations", "[evaluatePostfix]")
{
    vector<string> expr = {"3", "5", "-", "2", "*"};
    REQUIRE(evaluatePostfix(expr) == 10); // Debería ser -4
}

TEST_CASE("Postfix evaluation: bad calculation pt2", "[evaluatePostfix]")
{
    vector<string> expr = {"3", "5", "*", "2", "+"};
    REQUIRE(evaluatePostfix(expr) == 8); // Deberia dar error
}

TEST_CASE("Postfix evaluation: bad division", "[evaluatePostfix]")
{
    vector<string> expr = {"10", "2", "/"};
    REQUIRE(evaluatePostfix(expr) == 4); // Deberia dar error
}

TEST_CASE("Postfix evaluation: bad modular", "[evaluatePostfix]")
{
    vector<string> expr = {"5", "10", "%"};
    REQUIRE(evaluatePostfix(expr) == 8); // Deberia dar error
}

TEST_CASE("Postfix evaluation: extra operand", "[evaluatePostfix]")
{
    vector<string> expr = {"3", "5", "+", "7"};
    REQUIRE(evaluatePostfix(expr) == 8); // Hay un número extra sin operar
}

TEST_CASE("Postfix evaluation: only one operand", "[evaluatePostfix]")
{
    vector<string> expr = {"42"};
    REQUIRE(evaluatePostfix(expr) == 0); // Un solo número no puede evaluarse
}
