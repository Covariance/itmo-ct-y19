"""Tests for the main task."""
import logging
import os
import unittest
import urllib.request

from tests.constants import API_BASE, MOUNTPOINT

logging.basicConfig(
    level=logging.INFO,
    format='[%(asctime)s] %(filename)s:%(lineno)d: %(message)s'
)

TOKEN = os.environ["FS_TOKEN"]


class NetfileTestCases(unittest.TestCase):
    """Tests for the bonus task 6."""
    def test_truewrite(self):
        """Can write and then read /netfile."""
        new_string = "Hello World!"
        with open(MOUNTPOINT + "/netfile", "w") as test_file:
            test_file.write(new_string)
        with open(MOUNTPOINT + "/netfile") as test_file:
            actual = test_file.read().strip()
        self.assertEqual(new_string, actual)

    def test_bypasswrite(self):
        """Checks /netfile really goes to server."""
        new_string = "Goodbye World!"
        urllib.request.urlopen(
            "/".join([API_BASE, TOKEN, "file"]),
            data=new_string.encode()
        )
        with open(MOUNTPOINT + "/netfile") as test_file:
            actual = test_file.read().strip()
        self.assertEqual(new_string, actual)
