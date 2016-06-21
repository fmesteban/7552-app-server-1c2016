#encoding=utf-8
import requests
import unittest
import json
from subprocess import call
import inspect, os

n = 8
my_email = "fede.est" + str(n) + "@domain.com"
other_email = "marga" + str(n) + "@domain.com"
interests = [{"category": "music", "value": "la que no es 25"}, {"category": "sex", "value": "women"}]
interests2 = [{"category": "music", "value": "la que no es 25"}, {"category": "sex", "value": "men"}]

class TestMatches(unittest.TestCase):
	def test_create_users(self):
		data = json.dumps({"name": "UserToMatch", "alias": "fefee33", "password": "test", "email": my_email, "age": "35", "sex": "Male",
			"interests": interests, "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

		data = json.dumps({"name": "UserMatching", "alias": "margarita55", "password": "test", "email": other_email, "age": "35", "sex": "Female",
			"interests": interests2, "location": { "latitude": 45, "longitude": 46 }, "photo_profile": "base64photo" })
		r = requests.post("http://localhost:8000/register", data = data)
		self.assertEquals(r.status_code, 201)

	def test_get_matches(self):
		#Get suggestions
		data = json.dumps({"email": my_email, "count": "3"})
		r = requests.post("http://localhost:8000/getpossiblematches", data = data)
		self.assertEquals(r.status_code, 201)
		suggestions = r.json()[u'possibleMatches']
		print "Suggestions: ",
		print suggestions

		#Like on suggestions
		for candidate in suggestions:
			r_email = candidate[u'user'][u'email']
			data = json.dumps({"emailSrc": my_email, "emailDst": r_email})
			r = requests.post("http://localhost:8000/like", data = data)
			self.assertEquals(r.status_code, 201)

		data = json.dumps({"email": my_email})
		r = requests.post("http://localhost:8000/getmatches", data = data)
		self.assertEquals(r.status_code, 201)
		matches = r.json()[u'matches']
		self.assertEquals(len(matches), 0)

		#Other way like from suggestions
		for candidate in suggestions:
			r_email = candidate[u'user'][u'email']
			data = json.dumps({"emailSrc": r_email, "emailDst": my_email})
			r = requests.post("http://localhost:8000/like", data = data)
			self.assertEquals(r.status_code, 201)


		data = json.dumps({"email": my_email})
		r = requests.post("http://localhost:8000/getmatches", data = data)
		self.assertEquals(r.status_code, 201)
		matches = r.json()[u'matches']
		self.assertNotEqual(len(matches), 0)
		print "Matches: ",
		print matches

	def test_inexistant_user(self):
		pass

	def test_malformed_request(self):
		pass

	def test_incorrect_method(self):
		pass

if __name__ == '__main__':
	unittest.main()

