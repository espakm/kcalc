## KCalc - Prefix & Infix Calculator

     _____________________
    |  _________________  |
    | | JO           0. | |
    | |_________________| |
    |  ___ ___ ___   ___  |
    | | 7 | 8 | 9 | | + | |
    | |___|___|___| |___| |
    | | 4 | 5 | 6 | | - | |
    | |___|___|___| |___| |
    | | 1 | 2 | 3 | | x | |
    | |___|___|___| |___| |
    | | . | 0 | = | | / | |
    | |___|___|___| |___| |
    |_____________________|

The original description of the exercise can be found in the `docs` directory.

### Requirements

 - C++17 compatible compiler
 - CMake 3.13 or later

### Configuring, building and testing the project

The following commands can be used on either Linux, Mac or Windows to configure,
build and test the project:

```
cmake -S . -B build
cd build
cmake --build .
ctest
```

On Linux or Mac, the following script can also be used, for convenience:

```
./test.sh
```

### Running the application

The application takes its input from stdin and writes the result to stdout.

the following command can be used on either Linux, Mac or Windows:

```
./build/apps/kcalc [--prefix|--infix]
```

On Linux or Mac, the following script can also be used, for convenience:

```
./run.sh [--prefix|--infix]
```
