#!/bin/sh

# Runs KCalc Server from a Docker container.

docker container stop kcalc-server
docker container rm kcalc-server

docker network rm kcalc-net
docker network create kcalc-net

docker run -it --name kcalc-server --network kcalc-net kcalc-server
