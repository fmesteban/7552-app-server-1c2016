import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestRegistration(unittest.TestCase):

    def test_create_valid_user(self):
      data = {"userName": "usuario1", "passWord": "test", "userRealName": "Federico", "userMail": "example@domain.com", "userBirthday": "10/10/10", "userSex": "Male"}
      r = requests.post("http://localhost:8000/register", data = data)
      self.assertEqual(r.status_code, 201)
      self.assertEqual("hello " + data["userName"], r.json()["response"])

    def test_create_existing_user(self):
      pass

    def test_create_user_wrong_arguments(self):
      pass

if __name__ == '__main__':
  unittest.main()
