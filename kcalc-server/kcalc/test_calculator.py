from unittest import TestCase
from kcalc.calculator import SyntaxFormat
from kcalc.calculator import evaluate_expressions


class Test(TestCase):
    def test_evaluate_expressions(self):
        expressions = [
            '(1+3)',
            '((3*4)/10)',
        ]
        fmt = SyntaxFormat.INFIX
        results = evaluate_expressions(expressions, fmt)

        expected_results = (
            ["4", "1.2"],
            True
        )

        self.assertEqual(results, expected_results)
