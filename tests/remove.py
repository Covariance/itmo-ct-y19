"""Tests for the main task."""
import logging
import os
import unittest

from tests.constants import MOUNTPOINT

logging.basicConfig(
    level=logging.INFO,
    format='[%(asctime)s] %(filename)s:%(lineno)d: %(message)s'
)


class RemoveTestCases(unittest.TestCase):
    """Tests for the bonus task 5."""
    def test_rm1(self):
        """Can rm /dir/file.txt."""
        old_list = os.listdir(MOUNTPOINT)

        os.remove(MOUNTPOINT + "/dir/file.txt")
        self.assertEqual([], os.listdir(MOUNTPOINT + "/dir"))
        self.assertEqual(old_list, os.listdir(MOUNTPOINT))

    def test_rm2(self):
        """Can rm /test.txt."""
        old_list = os.listdir(MOUNTPOINT)

        os.remove(MOUNTPOINT + "/test.txt")

        expected = [item for item in old_list if item != "test.txt"]
        self.assertEqual(expected, os.listdir(MOUNTPOINT))

    def test_rm3(self):
        """Can rm /file.txt."""
        old_list = os.listdir(MOUNTPOINT)

        os.remove(MOUNTPOINT + "/file.txt")

        expected = [item for item in old_list if item != "file.txt"]
        self.assertEqual(expected, os.listdir(MOUNTPOINT))
