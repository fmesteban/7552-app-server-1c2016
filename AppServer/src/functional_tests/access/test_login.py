#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 146
mail = "example_login" + str(n) + "@mail.com"

class TestLogin(unittest.TestCase):

	def test_login_existing_user(self):
		data = json.dumps({"name": "TestLogin", "alias": "usuario_login", "password": "test", "email": mail, 
			"birthday": "10/10/10", "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/register", data = data)

		data = {"email": mail, "password": "test"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 201)
		#Assert the alias is the same
		alias = r.json()[u'user'][u'alias']
		print r
		self.assertEqual(alias, "usuario_login")

	def test_login_nonexisting_user(self):
		data = {"email": "example@inexistent.com", "password": "test"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 500)

	def test_login_invalid_arguments(self):
		data = {"email": mail}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

	def test_login_invalid_password(self):
		data = json.dumps({"name": "TestWronsPasswd", "alias": "usuario_wpasswd", "password": "test", "email": mail, 
			"birthday": "10/10/10", "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/register", data = data)

		data = {"email": "example@wrongpasswd.com", "password": "wrong"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 500)

if __name__ == '__main__':
	unittest.main()
