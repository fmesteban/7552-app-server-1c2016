#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 5
email = "example_real_user" + str(n) + "@mail.com"
interests = [ { "category": "music", "value": "manu chao"} ]

class TestPossibleMatches(unittest.TestCase):
	def test_get_suggestions(self):
		"""data = json.dumps({"name": "TestUser1", "alias": "usuario_suggestions1", "password": "test", "email": "example_suggestions" + str(n) + "@mail.com",
		 "birthday": "10/10/10", "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

		data = json.dumps({"name": "TestUser2", "alias": "usuario_suggestions2", "password": "test", "email": "example_suggestions" + str(n+1) + "@mail.com",
		 "birthday": "10/10/10", "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

		data = json.dumps({"name": "TestUser3", "alias": "usuario_suggestions3", "password": "test", "email": "example_suggestions" + str(n+2) + "@mail.com",
		 "birthday": "10/10/10", "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

		data = json.dumps({"name": "TestUser4", "alias": "usuario_suggestions4", "password": "test", "email": "example_suggestions" + str(n+3) + "@mail.com",
		 "birthday": "10/10/10", "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

		data = json.dumps({"name": "TestUser5", "alias": "usuario_suggestions4", "password": "test", "email": "example_suggestions" + str(n+4) + "@mail.com",
		 "birthday": "10/10/10", "sex": "Male", "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)
"""
		data = json.dumps({"name": "UserToSuggest", "alias": "real_user", "password": "test", "email": email, "age": "35", "sex": "Female",
			"interests": interests, "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

		data = json.dumps({"email": email, "count": "3"})
		r = requests.get("http://localhost:8000/getpossiblematches", data = data)
		self.assertEquals(r.status_code, 201)
		print r

if __name__ == '__main__':
	unittest.main()
