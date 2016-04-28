import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestNotFound(unittest.TestCase):
  def test_response(self):    
    r = requests.post("http://localhost:8000", params = {})
    self.assertEquals(r.status_code, 201)
    self.assertEquals(r.json()["response"], "Not Found")

if __name__ == '__main__':
  unittest.main()