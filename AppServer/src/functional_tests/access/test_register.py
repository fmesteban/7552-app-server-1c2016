import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 45
mail = "example_login" + str(n) + "@mail.com"

class TestRegistration(unittest.TestCase):

	def test_create_valid_user(self):
		data = json.dumps({"name": "TestRegister", "alias": "usuario_register2", "password": "test", "email": mail,
		 "birthday": "10/10/10", "sex": "Male", "location": json.dumps({ "latitude": 45, "longitude": 46 }), "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

	def test_create_existing_user(self):
		data = json.dumps({"name": "TestRegister", "alias": "usuario_register", "password": "test", "email": "example_register1@domain.com",
		 "birthday": "10/10/10", "sex": "Male", "location": json.dumps({ "latitude": 45, "longitude": 46 }), "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 500)

	def test_create_user_wrong_arguments(self):
		data = {"userName": "usuario1", "passWord": "test", "userSex": "Male"}
		r = requests.post("http://localhost:8000/register", data = json.dumps(data))
		self.assertEquals(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
