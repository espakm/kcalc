from enum import Enum
from subprocess import run as run_command
from subprocess import TimeoutExpired
from os import environ


KCALC_COMMAND_TIMEOUT = float(environ.get('KCALC_COMMAND_TIMEOUT', '30.0'))
""" Timeout for evaluating expressions, in seconds. """


KCALC_COMMAND_DIR: str = environ.get('KCALC_COMMAND_DIR', '/usr/bin')
"""Absolut path of the directory that contains the 'kcalc' command."""


class SyntaxFormat(Enum):
    PREFIX = 0,
    INFIX = 1,


def evaluate_expressions(expressions: [str], fmt: SyntaxFormat) -> ([str], bool):
    """
    Evaluates the given expressions and returns their value or a parsing error.
    Returns the following two values:
      - the output of the evaluation that is the value of the expressions
        or error message if the expression could not be parsed;
      - True if the command has returned successfully, otherwise False
    :param expressions the list of expressions to evaluate
    :param fmt the syntax format of the expressions, i.e. prefix of infix
        The same format is applied to each expression.
    :return the output of the expression evaluations and whether command ran
        successfully
    """

    syntax_format_arg = '--prefix' if fmt == SyntaxFormat.PREFIX else '--infix'

    command = f'{KCALC_COMMAND_DIR}/kcalc'

    input_text = '\n'.join(expressions) + "\n"

    try:
        proc = run_command(
            [command, syntax_format_arg],
            input=input_text,
            capture_output=True,
            text=True,
            timeout=KCALC_COMMAND_TIMEOUT)

        output = proc.stdout.split('\n')
        del output[-1]
        success = proc.returncode == 0

        return output, success
    except TimeoutExpired:
        return "Timeout. Expression could not be evaluated.", False
