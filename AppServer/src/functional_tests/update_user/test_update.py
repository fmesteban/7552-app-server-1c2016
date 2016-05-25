#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestUpdateUser(unittest.TestCase):
	def test_update_profile_valid(self):
		# First we register
		data = json.dumps({"name": "TestUpdate", "alias": "usuario_update", "password": "test", "email": "example_update1@domain.com", 
			"birthday": "10/10/10", "sex": "Male", "location": json.dumps({ "latitude": 45, "longitude": 46 }), "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/register", data = data)

		# Then we update
		data = json.dumps({"name": "TestUpdateUpdated", "alias": "usuario_update", "password": "test", "email": "example_update1@domain.com", 
			"birthday": "10/10/10", "sex": "Female", "location": json.dumps({ "latitude": 45, "longitude": 46 }), "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/updateprofile", data = json.dumps(data))
		self.assertEqual(r.status_code, 200)

		# Finally we retrieve to check updated data
		data = {"email": "example_update1@domain.com", "password": "test"}
		r = requests.post("http://localhost:8000/login", data = json.dumps(data))
		self.assertEqual(r.status_code, 200)
		response = r.json()["response"]
		self.assertEqual(response["name"], "TestUpdateUpdated")
		self.assertEqual(response["sex"], "Female")

	def test_update_profile_malformed(self):
		data = json.dumps({"name": "TestUpdateUpdated", "alias": "usuario_update", "password": "test", "email": "example_update1@domain.com", 
			"birthday": "10/10/10", "sex": "Female", "location": json.dumps({ "latitude": 45, "longitude": 46 }), "photo_profile": "base64photo" })
		requests.post("http://localhost:8000/updateprofile", data = json.dumps(data))
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()