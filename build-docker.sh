#!/bin/sh

# Builds Docker images for KCalc, KCalc Server and KCalc Client

set -e

docker build -t kcalc .

docker build -t kcalc-server kcalc-server

docker build -t kcalc-client kcalc-client
