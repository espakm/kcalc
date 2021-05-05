#!/bin/sh

# Runs KCalc Client against a KCalc Server.
#
# It assumes that the 'requests' library is installed on the system.
#
# If this is not the case, then:
#
#   - install Miniconda or Anaconda
#   - run the following commands:
#
#      $ conda create --name kcalc python=3
#      $ conda activate kcalc
#      $ pip install requests
#
# Use the following command to activate the `kcalc` environment:
#
#      $ conda activate kcalc
#

export KCALC_SERVER_URI="http://127.0.0.1:8000/calculator"
export KCALC_SYNTAX_FORMAT="infix"

cd kcalc-client

./kcalc_client.py
