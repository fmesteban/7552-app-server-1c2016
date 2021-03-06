#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 5
mail = "example_login" + str(n) + "@mail.com"
new_mail = "example" + str(n) + "@wrongpasswd.com"

class TestLogin(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		#First we register
		data = json.dumps({"name": "TestLogin", "alias": "usuario_login", "password": "test", "email": mail, 
			"age": "21", "sex": "Male", "location": { "latitude": -34.6970, "longitude": -58.3768 }, "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/register", data = data)
		
	def test_login_existing_user(self):
		data = {"email": mail, "password": "test"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 201)
		#Assert the alias is the same
		alias = r.json()[u'user'][u'alias']
		self.assertEqual(alias, "usuario_login")

	def test_login_nonexisting_user(self):
		data = {"email": "example@inexistent.com", "password": "test"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

	def test_login_invalid_arguments(self):
		data = {"email": mail}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

	def test_incorrect_method(self):
		data = json.dumps({"email": mail, "password": "test"})
		r = requests.put("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
