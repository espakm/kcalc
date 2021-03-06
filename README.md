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


### TLDR;

```
./build-docker.sh
./run-server-docker.sh
./run-client-docker.sh   # in another console window
```

This will start the client in infix mode. For prefix mode, change env var in
launch script.

For local installation, read further.


### KCalc

This is a simple interactive command line application.

Requirements:

 - C++17 compatible compiler
 - CMake 3.13 or later
 - Bash

Build and testing:

```
./build.sh
./test.sh
```

(The test script also builds.)

Running:

The program takes its input from stdin and writes the result to stdout.
The syntax format (prefix or infix) can be specified as an argument. Default is
infix.

```
./run.sh [--prefix|--infix]
```


### KCalc Server

This is a lightweight web service wrapper around KCalc.

Requirements:

 - Python 3.7+
 - Falcon
 - Gunicorn

Testing:

```
./test-server.sh
```

Running:

```
./run-server.sh
```

The default end point of the service can be modified by editing the launch script.


#### REST API

The service accepts GET and POST commands at the "/calculator" route.

The GET command accepts two query arguments:

 - "expr" is the expression to evaluate. It is mandatory and can appear multiple times.
 - "format" can be "prefix" or "infix". It is optional. Default is "infix".

The response is a JSON document with a "result" and "ok" fields. The "result"
field is a list of strings. It holds the results of the evaluated expressions or
an error message for malformed expressions. The "ok" field is True if the
processing was successful, otherwise False.

The POST command accepts a JSON document with an "expr" and "format" fields.
The semantics is the same as for the GET. The response is also the same.


### KCalc Client

It is a simple interactive command line application that evaluates arithmetic
expressions using KCalc Server.

Requirements:

 - Python 3.7+
 - requests (Python library)

Running:

```
./run-client.sh
```

The URI endpoint of the KCalc server and the syntax format (prefix or infix) can
be specified via environment variables in the script. Defaults format is infix.


### Build and run using Docker

Building Docker images for all the three applications:

```
./build-docker.sh
```

Running KCalc:

```
./run-docker.sh [--prefix|--infix]
```

Running KCalc Server:

```
./run-server-docker.sh
```

Running KCalc Client:

```
./run-client-docker.sh
```

Default settings can be modified via environment variables in the launch scripts.
Default expression syntax format is infix.
