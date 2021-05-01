#!/bin/sh

echo
echo "Evaluating some prefix expressions:"
echo

./build/apps/kcalc --prefix < resources/prefix-example-1.txt

echo
echo "Evaluating some infix expressions:"
echo

./build/apps/kcalc --infix < resources/infix-example-1.txt
