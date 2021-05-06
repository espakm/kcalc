#!/bin/sh

# Runs KCalc Client from a Docker container.

export KCALC_SERVER_URI="http://kcalc-server/calculator"
export KCALC_SYNTAX_FORMAT="infix"

docker run -it --network kcalc-net \
    --env KCALC_SERVER_URI \
    --env KCALC_SERVER_SYNTAX \
    kcalc-client
