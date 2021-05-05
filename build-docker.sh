#!/bin/sh

# Builds Docker images for the KCalc command line application and web service.

set -e

docker build -t kcalc .

docker build -t kcalc-ws web-service
