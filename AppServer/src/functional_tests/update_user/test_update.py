#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestUpdateUser(unittest.TestCase):
	def test_update_profile_valid(self):
		n = 5
		mail = "example_update" + str(n) + "@mail.com"
		interests = [ { "category": "music", "value": "El hacedor de viudas"} ]
		alias = "usuario_update" + str(n)

		# First we register
		data = json.dumps({"name": "TestUpdate", "alias": alias, "password": "test", "email": mail, "age": "32", 
			"sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo", "interests": interests })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		# Then we update.
		data = json.dumps({"name": "TestUpdate", "alias": alias + str(n), "password": "test", "email": mail, "age": "32",
			"sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo", "interests": interests })
		r = requests.put("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 201)

		# Finally we retrieve to check updated data
		data = json.dumps({"email": mail, "password": "test"})
		r = requests.post("http://localhost:8000/login", data = data)
		self.assertEqual(r.status_code, 201)
		# Check name is changed
		response = r.json()[u'user']
		self.assertEqual(response[u'name'], "TestUpdateUpdated")

	def test_update_profile_malformed(self):
		data = json.dumps({"name": "TestUpdateUpdated", "alias": "usuario_update", "password": "test", "email": "example_update1@domain.com", 
			"age": "32", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()