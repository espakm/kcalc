#!/bin/sh

# Runs unit tests for the KCalc web service.
#
# Make sure that the right Python environment is selected, e.g.:
#
#    $ conda activate kcalc
#

set -e

cd web-service
python -m unittest discover
