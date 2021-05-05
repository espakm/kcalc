from kcalc.calculator import SyntaxFormat
from kcalc.calculator import evaluate_expressions
import falcon
import json


class Calculator:

    def on_get(self, req, resp):
        if not req.has_param('expr'):
            resp.text = "Invalid arguments. Expressions missing."
            resp.status = 400
            return

        expressions = req.params['expr']
        if isinstance(expressions, str):
            expressions = [expressions]

        syntax_format = SyntaxFormat.INFIX
        if req.has_param('format'):
            fmt = req.params['format']
            if fmt == 'prefix':
                syntax_format = SyntaxFormat.PREFIX
            elif fmt != 'infix':
                resp.text = "Invalid syntax format specified."
                resp.status = 400
                return

        values, ok = evaluate_expressions(expressions, syntax_format)

        doc = {
            'result': values,
            'success': ok,
        }
        resp.text = json.dumps(doc, ensure_ascii=False)
        resp.status = 200 if ok else 400

    def on_post(self, req, resp):

        request_data = json.loads(req.bounded_stream.read().decode("utf-8"))

        if 'expr' not in request_data:
            return "Invalid data. Expressions missing.", 400

        expressions = request_data['expr']
        if isinstance(expressions, str):
            expressions = [expressions]

        syntax_format = SyntaxFormat.INFIX
        if 'format' in request_data:
            fmt = request_data['format']
            if fmt == 'prefix':
                syntax_format = SyntaxFormat.PREFIX
            elif fmt != 'infix':
                return "Invalid syntax format specified."

        values, ok = evaluate_expressions(expressions, syntax_format)

        doc = {
            'result': values,
            'success': ok,
        }
        resp.text = json.dumps(doc, ensure_ascii=False)
        resp.status = 200 if ok else 400


application = falcon.App()
application.add_route('/calculator', Calculator())
