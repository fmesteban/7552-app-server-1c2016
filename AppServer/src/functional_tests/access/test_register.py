import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 2
mail = "example_register" + str(n) + "@mail.com"
interests = [ { "category": "music", "value": "La 25"} ]

class TestRegistration(unittest.TestCase):

	def test_create_valid_user(self):
		data = json.dumps({"name": "TestRegister", "alias": "usuario_register" + str(n), "password": "test", "email": mail, "age": "20",
		"interests": interests, "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		#Create existing user
		data = json.dumps({"name": "TestRegister", "alias": "usuario_register" + str(n), "password": "test", "email": mail, "age": "20",
		"interests": interests, "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 500)

	def test_create_wrong_arguments(self):
		data = {"userName": "usuario1", "passWord": "test", "userSex": "Male"}
		r = requests.post("http://localhost:8000/register", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

	def test_create_incorrect_method(self):
		data = json.dumps({"name": "TestRegister", "alias": "usuario_register" + str(n), "password": "test", "email": mail, "age": "20",
		"interests": interests, "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.put("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
