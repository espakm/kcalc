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

For brevity, the instructions below are only for Linux and Mac. (Windows would
not be much different.)


### Command line application

#### Requirements

 - C++17 compatible compiler
 - CMake 3.13 or later
 - Bash

#### Build and test

The following scripts can be used to build and test the application:

```
./build.sh
./test.sh
```

(The test script also builds.)

#### Run

The application takes its input from stdin and writes the result to stdout.
The syntax format (prefix or infix) can be specified as an argument. Default is
infix.

```
./run.sh [--prefix|--infix]
```

### Web service application

#### Requirements

 - Python 3
 - Falcon
 - Gunicorn

#### Test

The following script can be used to test the web service application:

```
./test-ws.sh
```

#### Run

The application can be run by the following command. It uses port 8000.

```
./run-ws.sh
```

#### REST API

The service accepts GET and POST commands at the "/calculator" route.

The GET command accepts two query arguments:

 - "expr" is the expression to evaluate. It is mandatory and can appear multiple times.
 - "format" can be "prefix" or "infix". It is optional. Default is "infix".

The response is a JSON document with a "result" and "ok" fields. The "result"
field is a list of strings. It holds the results of the evaluated expressions or
an error message for malformed expressions. The "ok" field is True if the
processing was successful, otherwise False.

The POST command accepts a JSON document with an "expr" and  "format" fields.
The semantics is the same as for the GET. The response is also the same.


### Build and run using Docker

Building Docker images for both applications:

```
./build-docker.sh
```

Running the command line application using Docker:

```
./run-docker.sh [--prefix|--infix]
```

Running the web service application using Docker:

```
./run-docker-ws.sh
```

Modify the script if you want to use a different port. (Default is 8000.)
