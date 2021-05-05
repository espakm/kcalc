from falcon import HTTP_200
from falcon.testing import TestCase
from falcon.testing.client import TestClient
from kcalc.app import application
from kcalc.app import Calculator


class TestApp(TestCase, TestClient):

    def setUp(self):
        super(TestCase, self).setUp()
        TestClient.__init__(self, application)


    def test_calculator_get(self):
        query_args = {'expr': 3}
        expected_json = {'result': ['3'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        query_args = {'expr': '(3+4)'}
        expected_json = {'result': ['7'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        query_args = {'expr': '((10-3)/2)'}
        expected_json = {'result': ['3.5'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        query_args = {'expr': '(2 - (5 * 6))'}
        expected_json = {'result': ['-28'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        query_args = {'expr': '(2 - 4)'}
        expected_json = {'result': ['6'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertNotEqual(result.json, expected_json)

        query_args = {'expr': '+ 3 8', 'format': 'prefix'}
        expected_json = {'result': ['11'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        query_args = {'expr': ['+ 3 8', '* 2 4'], 'format': 'prefix'}
        expected_json = {'result': ['11', '8'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        query_args = {'expr': ['(3 + (8 / 16))', '(2 * 3)'], 'format': 'infix'}
        expected_json = {'result': ['3.5', '6'], 'success': True}
        result = self.simulate_get('/calculator', params=query_args)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)


    def test_calculator_post(self):
        data = {'expr': ['3']}
        expected_json = {'result': ['3'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)


        data = {'expr': ['(3+4)']}
        expected_json = {'result': ['7'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        data = {'expr': '((10-3)/2)'}
        expected_json = {'result': ['3.5'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        data = {'expr': '(2 - (5 * 6))'}
        expected_json = {'result': ['-28'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        data = {'expr': '(2 - 4)'}
        expected_json = {'result': ['6'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertNotEqual(result.json, expected_json)

        data = {'expr': '+ 3 8', 'format': 'prefix'}
        expected_json = {'result': ['11'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        data = {'expr': ['+ 3 8', '* 2 4'], 'format': 'prefix'}
        expected_json = {'result': ['11', '8'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)

        data = {'expr': ['(3 + (8 / 16))', '(2 * 3)'], 'format': 'infix'}
        expected_json = {'result': ['3.5', '6'], 'success': True}
        result = self.simulate_post('/calculator', json=data)
        assert result.status == HTTP_200
        self.assertEqual(result.json, expected_json)
