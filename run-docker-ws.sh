#!/bin/sh

# Runs the KCalc web service from a Docker container.

HOST_IP=127.0.0.1
HOST_PORT=8000

docker run -it -p ${HOST_IP}:${HOST_PORT}:8000 kcalc-ws
