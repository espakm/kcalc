#!/bin/sh

# Builds Docker images for the KCalc command line application, the web service
# and the web client.

set -e

docker build -t kcalc .

docker build -t kcalc-ws web-service

docker build -t kcalc-client web-client
