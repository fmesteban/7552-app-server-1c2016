#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestDislikes(unittest.TestCase):

	def test_inexistant_user(self):
		data = json.dumps({"conversation": {"emailSrc": "idont@exist.com", "emailDst": "meneither@lol.com", "messages": [{
			"msg": "lol"}, {"msg": "lol."
			}]}})
		r = requests.post("http://localhost:8000/sendconversation", data = data)
		self.assertEqual(r.status_code, 400)

	def test_incomplete_request(self):
		data = json.dumps({"conversation": {"emailDst": "meneither@lol.com", "messages": [{
			"msg": "lol"}, {"msg": "lol."
			}]}})
		r = requests.post("http://localhost:8000/sendconversation", data = data)
		self.assertEqual(r.status_code, 400)

	def test_incorrect_method(self):
		data = json.dumps({"conversation": {"emailSrc": "idont@exist.com", "emailDst": "meneither@lol.com", "messages": [{
			"msg": "lol"}, {"msg": "lol."
			}]}})
		r = requests.put("http://localhost:8000/sendconversation", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
