#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestUpdateUser(unittest.TestCase):
	def test_update_profile_valid(self):
		n = 45
		mail = "example_update" + str(n) + "@mail.com"
		interests = [ { "category": "music", "value": "manu chao"} ]

		# First we register
		data = json.dumps({"name": "TestUpdate", "alias": "usuario_update", "password": "test", "email": mail, 
			"birthday": "10/10/1990", "sex": "male", "location": "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo", "interests": [ob for ob in interests] })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		# Then we update. Note we are trying to modify the sex, and it is not possible
		data = json.dumps({"name": "TestUpdateUpdated", "alias": "usuario_update", "password": "test", "email": mail, 
			"birthday": "10/10/1990", "sex": "female", "location": "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo", "interests": [ob for ob in interests] })
		r = requests.post("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 201)

		# Finally we retrieve to check updated data
		data = json.dumps({"email": mail, "password": "test"})
		r = requests.post("http://localhost:8000/login", data = data)
		self.assertEqual(r.status_code, 201)
		# Check name is changed
		response = r.json()[u'user']
		self.assertEqual(response[u'name'], "TestUpdateUpdated")
		# Check sex is not changed
		self.assertEqual(response[u'sex'], "male")

	def test_update_profile_malformed(self):
		data = json.dumps({"name": "TestUpdateUpdated", "alias": "usuario_update", "password": "test", "email": "example_update1@domain.com", 
			"birthday": "10/10/10", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()