#!/usr/bin/env python3

from os import environ
import requests
from requests.exceptions import ConnectionError


server_uri = environ.get('KCALC_SERVER_URI', 'http://127.0.0.1:8000/calculator')
""" The endpoint of the KCalc web service """


syntax_format = environ.get('KCALC_SYNTAX_FORMAT', 'infix')
""" Syntax format of the expressions to evaluate. """


def process(line: str):
    query_args = {'expr': line, 'format': syntax_format}

    try:
        response = requests.get(server_uri, params=query_args)
    except ConnectionError:
        print("Connection refused.")
        return

    if response.status_code != 200:
        print(f"Service responded with status code: {response.status_code}")
        return

    data = response.json()

    if 'result' not in data or 'success' not in data:
        print("Invalid response")
        return

    if data['success'] != True:
        print("Error occurred at evaluating the expression.")
        return

    for r in data['result']:
        print(r)


def repl():
    try:
        line = input('> ')
        while line:
            process(line)
            line = input('> ')
    except EOFError:
        return
    except KeyboardInterrupt:
        return


if __name__ == '__main__':
    repl()
