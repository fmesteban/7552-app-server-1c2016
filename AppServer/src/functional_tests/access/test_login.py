#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestLogin(unittest.TestCase):

	def test_login_existing_user(self):
		data = json.dumps({"name": "TestLogin", "alias": "usuario_login", "password": "test", "email": "example_login7@domain.com", 
			"birthday": "10/10/10", "sex": "Male", "location": json.dumps({ "latitude": 45, "longitude": 46 }), "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/register", data = data)

		data = {"email": "example_login7@domain.com", "password": "test"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 201)
		print(r.json())
		response = r.json()["response"]
		self.assertEqual(response["alias"], "usuario_login")

	def test_login_nonexisting_user(self):
		data = {"email": "example@inexistent.com", "password": "test"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 500)

	def test_login_invalid_arguments(self):
		data = {"email": "example@domain.com"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

	def test_login_invalid_password(self):
		data = json.dumps({"name": "TestWronsPasswd", "alias": "usuario_wpasswd", "password": "test", "email": "example@wrongpasswd.com", 
			"birthday": "10/10/10", "sex": "Male", "location": json.dumps({ "latitude": 45, "longitude": 46 }), "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/register", data = data)

		data = {"email": "example@wrongpasswd.com", "password": "wrong"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
