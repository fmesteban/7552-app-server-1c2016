#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestUpdateUser(unittest.TestCase):

	def setUp(self):
		pass
	#	data = {"name": "TestUpdate", "alias": "usuario1", "password": "test", "email": "example_update@domain.com", "birthday": "10/10/10", "sex": "Male",
	#			"interests": [], "location": { "latitude": 121, "longitude": 46.51119 }, "photo_profile": "base64photo" }
	#	requests.post("http://localhost:8000/register", data = json.dumps(data))

	def test_update_profile_valid(self):
		pass
	#	data = {"name": "TestUpdate", "alias": "juanmonigote", "password": "test", "email": "example_update@domain.com", "birthday": "10/10/10", "sex": "Male",
	#			"interests": [], "location": { "latitude": 121.45356, "longitude": 46.51119 }, "photo_profile": "base64photo" }
	#	requests.post("http://localhost:8000/updateprofile", data = json.dumps(data))
	#	self.assertEqual(r.status_code, 200)

	def test_update_profile_malformed(self):
		pass
	#	data = {"password": "test", "email": "example_update@domain.com", "birthday": "10/10/10", "sex": "Male",
	#			"interests": [], "location": { "latitude": 121.45356, "longitude": 46.51119 }, "photo_profile": "base64photo" }
	#	requests.post("http://localhost:8000/updateprofile", data = json.dumps(data))
	#	self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()