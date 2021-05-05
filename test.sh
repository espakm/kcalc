#!/bin/sh

# Runs unit and system tests for the KCalc command line application.

set -e

cmake -S . -B build
cmake --build build

cd build
ctest
