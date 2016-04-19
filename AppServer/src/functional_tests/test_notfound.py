import requests
import unittest
import json
from subprocess import call
import inspect, os

class TestNotFound(unittest.TestCase):
  def test_response(self):    
    r = requests.post("http://localhost:8000", params = {})
    self.assertEquals(r.json()["response"], 404)

if __name__ == '__main__':
  unittest.main()
