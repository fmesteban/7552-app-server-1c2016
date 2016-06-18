import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 1
mail = "example_login" + str(n) + "@mail.com"
interests = [ { "category": "music", "value": "La 25"} ]

class TestRegistration(unittest.TestCase):

	def test_create_valid_user(self):
		data = json.dumps({"name": "TestRegister", "alias": "usuario_register" + str(n), "password": "test", "email": mail, "age": "20",
		"interests": interests, "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

	def test_create_existing_user(self):
		data = json.dumps({"name": "TestRegister", "alias": "usuario_register", "password": "test", "email": "example_register1@domain.com", "age": "20",
		"interests": interests, "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 500)

	def test_create_user_wrong_arguments(self):
		data = {"userName": "usuario1", "passWord": "test", "userSex": "Male"}
		r = requests.post("http://localhost:8000/register", data = json.dumps(data))
		self.assertEquals(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
