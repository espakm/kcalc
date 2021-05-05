#!/bin/sh

# Builds the KCalc command line application.

set -e

cmake -S . -B build
cmake --build build
