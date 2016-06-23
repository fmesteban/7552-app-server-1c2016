#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestDislikes(unittest.TestCase):

	def test_inexistant_user(self):
		data = json.dumps({"emailSrc": "invalid@email.com", "emailDst": "another_invalid@email.com"})
		r = requests.post("http://localhost:8000/getconversation", data = data)
		self.assertEqual(r.status_code, 400)

	def test_incomplete_request(self):
		data = json.dumps({"emailSrc": "invalid@email.com"})
		r = requests.post("http://localhost:8000/getconversation", data = data)
		self.assertEqual(r.status_code, 400)

	def test_incorrect_method(self):
		data = json.dumps({"emailSrc": "invalid@email.com", "emailDst": "another_invalid@email.com"})
		r = requests.put("http://localhost:8000/getconversation", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
