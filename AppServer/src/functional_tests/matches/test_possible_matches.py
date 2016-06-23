#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 1
email = "example_real_user" + str(n) + "@mail.com"
interests = [ { "category": "music", "value": "manu chao"} ]
interests2 = [{"category": "music", "value": "la que no es 25"}, {"category": "sex", "value": "women"}]

class TestPossibleMatches(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		data = json.dumps({"name": "TestUser"+str(n), "alias": "usuario_suggestions"+str(n), "password": "test", "email": "example_suggestions" + str(n) + "@mail.com",
		 "age": "25", "interests": interests, "sex": "Male", "location": { "latitude": -34.6975, "longitude": -58.3770 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		data = json.dumps({"name": "TestUser"+str(n), "alias": "usuario_suggestions"+str(n+1), "password": "test", "email": "example_suggestions" + str(n+1) + "@mail.com",
		 "age": "25", "interests": interests, "sex": "Male", "location": { "latitude": -34.6975, "longitude": -58.3770 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		data = json.dumps({"name": "TestUser"+str(n), "alias": "usuario_suggestions"+str(n+2), "password": "test", "email": "example_suggestions" + str(n+2) + "@mail.com",
		 "age": "25", "interests": interests, "sex": "Male", "location": { "latitude": -34.6975, "longitude": -58.3770 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		data = json.dumps({"name": "TestUser"+str(n), "alias": "usuario_suggestions"+str(n+3), "password": "test", "email": "example_suggestions" + str(n+3) + "@mail.com",
		 "age": "25", "interests": interests, "sex": "Male", "location": { "latitude": -34.6975, "longitude": -58.3770 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		data = json.dumps({"name": "TestUser"+str(n), "alias": "usuario_suggestions"+str(n+4), "password": "test", "email": "example_suggestions" + str(n+4) + "@mail.com",
		 "age": "25", "interests": interests, "sex": "Male", "location": { "latitude": -34.6975, "longitude": -58.3770 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

	def test_get_suggestions(self):

		data = json.dumps({"name": "UserToSuggest", "alias": "real_user", "password": "test", "email": email, "age": "35", "sex": "Male",
			"interests": interests2, "location": { "latitude": -34.6975, "longitude": -58.3770 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEqual(r.status_code, 201)

		data = json.dumps({"email": email, "count": "3"})
		r = requests.post("http://localhost:8000/getpossiblematches", data = data)
		self.assertEqual(r.status_code, 201)
		matches = r.json()[u'possibleMatches']
		self.assertNotEqual(len(matches), 0)

	def test_inexistant_user(self):
		data = json.dumps({"email": "invalid@email.com", "count": "3"})
		r = requests.post("http://localhost:8000/getpossiblematches", data = data)
		self.assertEqual(r.status_code, 500)

	def test_incomplete_request(self):
		data = json.dumps({"email": email})
		r = requests.post("http://localhost:8000/getpossiblematches", data = data)
		self.assertEqual(r.status_code, 400)

	def test_incorrect_method(self):
		data = json.dumps({"email": email, "count": "3"})
		r = requests.put("http://localhost:8000/getpossiblematches", data = data)
		self.assertEqual(r.status_code, 400)

if __name__ == '__main__':
	unittest.main()
