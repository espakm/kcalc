#!/bin/sh

# Runs KCalc Server.
#
# It assumes that falcon and gunicorn are installed on the system.
#
# If this is not the case, then:
#
#   - install Miniconda or Anaconda
#   - run the following commands:
#
#      $ conda create -y --name kcalc python=3.7
#      $ conda activate kcalc
#      $ pip install falcon gunicorn
#
# Use the following command to activate the `kcalc` environment:
#
#      $ conda activate kcalc
#

export KCALC_COMMAND_DIR="${PWD}/build/apps"

cd kcalc-server

KCALC_SERVER_HOST=127.0.0.1
KCALC_SERVER_PORT=8000

gunicorn -b ${KCALC_SERVER_HOST}:${KCALC_SERVER_PORT} kcalc.app
