#!/bin/sh

# Runs KCalc Client from a Docker container.

export KCALC_SERVER_URI="http://127.0.0.1:8000/calculator"
export KCALC_SYNTAX_FORMAT="infix"

docker run -it kcalc-client
