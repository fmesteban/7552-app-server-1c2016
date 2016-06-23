#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 3
mail = "example_update" + str(n) + "@mail.com"
interests = [ { "category": "music", "value": "El hacedor de viudas"} ]
alias = "usuario_update" + str(n)

class TestUpdateUser(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		# First we register
		data = json.dumps({"name": "TestUpdate", "alias": alias, "password": "test", "email": mail, "age": "32", 
			"sex": "Male", "location": { "latitude": -34.6982, "longitude": -58.3771 }, "photo_profile": "base64photo", "interests": interests })
		r = requests.post("http://localhost:8000/register", data = data)

	def test_update_profile_valid(self):
		data = json.dumps({"name": "TestUpdateUpdated", "alias": alias, "email": mail, "age": "32", "sex": "Male", 
			"location": { "latitude": -34.6982, "longitude": -58.3771 }, "photo_profile": "base64photo", "interests": interests })
		r = requests.post("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 201)

		# We retrieve to check updated data
		data = json.dumps({"email": mail, "password": "test"})
		r = requests.post("http://localhost:8000/login", data = data)
		self.assertEqual(r.status_code, 200)
		# Check name is changed
		response = r.json()[u'user']
		self.assertEqual(response[u'name'], "TestUpdateUpdated")

	def test_update_profile_malformed(self):
		data = json.dumps({"email": mail, "passssword": "test"})
		r = requests.post("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 400)

	def test_incomplete_request(self):
		data = json.dumps({"email": mail})
		r = requests.post("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 400)

	def test_incorrect_method(self):
		data = json.dumps({"email": mail, "password": "test"})
		r = requests.put("http://localhost:8000/updateprofile", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()