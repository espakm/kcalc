#!/bin/sh

# Runs KCalc Server from a Docker container.

HOST_IP=127.0.0.1
HOST_PORT=8000

docker run -it -p ${HOST_IP}:${HOST_PORT}:8000 kcalc-server
