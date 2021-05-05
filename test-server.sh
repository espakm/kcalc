#!/bin/sh

# Runs unit tests for KCalc Server.
#
# Make sure that the right Python environment is selected, e.g.:
#
#    $ conda activate kcalc
#

set -e

export KCALC_COMMAND_DIR="${PWD}/build/apps"

cd kcalc-server
python -m unittest discover
