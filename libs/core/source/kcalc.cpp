#include <cstdlib>
#include <iostream>

#include "kcalc.hpp"

namespace kcalc
{

int run(int argc, char* /*argv*/[])
{
  if (argc != 1)
  {
    std::cout <<
        "\n"
        "Invalid command line arguments.\n"
        "\n"
        "This program reads from the standard input and prints its results "
        "to the standard output. No arguments required.\n"
        "\n";
     return EXIT_FAILURE;
  }

  repl();

  return EXIT_SUCCESS;
}


void repl(const std::string& prompt,
          std::istream& inputStream,
          std::ostream& outputStream)
{
    std::string line;
    outputStream << prompt;
    while (std::getline(inputStream, line).good())
    {
        auto value = evalPrefixExpr(line);
        outputStream << value << std::endl << prompt;
    }
}

}
