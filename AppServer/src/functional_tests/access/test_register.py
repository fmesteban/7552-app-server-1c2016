import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestRegistration(unittest.TestCase):

	def test_create_valid_user(self):
		data = {"name": "TestRegister", "alias": "usuario_register", "password": "test", "email": "example_register4@domain.com", "birthday": "10/10/10", "sex": "Male", "latitude": 32, "longitude": 45, "photo_profile": "base64photo" }
		r = requests.post("http://localhost:8000/register", data = json.dumps(data))
		self.assertEqual(r.status_code, 201)
		self.assertEqual("OK", r.json()["response"])

	def test_create_existing_user(self):
		data = {"name": "TestRegister", "alias": "usuario_register", "password": "test", "email": "example_register1@domain.com", "birthday": "10/10/10", "sex": "Male", "latitude": 32, "longitude": 45, "photo_profile": "base64photo" }
		r = requests.post("http://localhost:8000/register", data = json.dumps(data))
		self.assertEqual(r.status_code, 500)

	def test_create_user_wrong_arguments(self):
		data = {"userName": "usuario1", "passWord": "test", "userSex": "Male"}
		r = requests.post("http://localhost:8000/register", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
