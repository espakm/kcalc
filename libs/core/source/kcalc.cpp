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

  return EXIT_SUCCESS;
}

}
