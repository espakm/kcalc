#!/bin/sh

# Runs the KCalc web service.
#
# It assumes that falcon and gunicorn are installed on the system.
#
# If this is not the case, then:
#
#   - install Miniconda or Anaconda
#   - run the following commands:
#
#      $ conda create --name kcalc python=3
#      $ conda activate kcalc
#      $ pip install falcon gunicorn
#
# Use the following command to activate the `kcalc` environment:
#
#      $ conda activate kcalc
#

export KCALC_COMMAND_DIR="${PWD}/build/apps"

cd web-service

# For debugging:
# gunicorn -b 127.0.0.1:5000 kcalc.app --reload

# By default the web service is bound to 0.0.0.0:8000
gunicorn kcalc.app