"""Tests for the main task."""
import logging
import os
import unittest

from tests.constants import MOUNTPOINT

logging.basicConfig(
    level=logging.INFO,
    format='[%(asctime)s] %(filename)s:%(lineno)d: %(message)s'
)


class BasicTestCases(unittest.TestCase):
    """Tests for the main task."""
    def test_list1(self):
        """Can ls in mountpoint."""
        actual = os.listdir(MOUNTPOINT)

        required = ["dir", "file.txt", "test.txt"]
        allowed = required + ["netdir", "netfile"]

        for item in actual:
            self.assertIn(item, required + allowed)

        for item in required:
            self.assertIn(item, actual)

    def test_list2(self):
        """Can ls in /dir."""
        actual = os.listdir(MOUNTPOINT + "/dir")

        self.assertEqual(["file.txt"], actual)

    def test_cat_file1(self):
        """Can cat /file.txt."""
        with open(MOUNTPOINT + "/file.txt") as test_file:
            actual = test_file.read().strip()
        self.assertEqual("Merry Christmas!", actual)

    def test_cat_file2(self):
        """Can cat /dir/file.txt."""
        with open(MOUNTPOINT + "/dir/file.txt") as test_file:
            actual = test_file.read().strip()
        self.assertEqual("Merry Christmas!", actual)

    def test_cat_test(self):
        """Can cat /test.txt."""
        with open(MOUNTPOINT + "/test.txt") as test_file:
            actual = test_file.read().strip()
        self.assertEqual("test", actual)

    def test_write_file1(self):
        """Can write /file.txt."""
        new_string = "Hello World!"
        with open(MOUNTPOINT + "/file.txt", "w") as test_file:
            test_file.write(new_string)
        with open(MOUNTPOINT + "/file.txt") as test_file:
            actual = test_file.read().strip()
        self.assertEqual(new_string, actual)

    def test_write_file2(self):
        """Can write /dir/file.txt."""
        new_string = "abracadabra"
        with open(MOUNTPOINT + "/dir/file.txt", "w") as test_file:
            test_file.write(new_string)
        with open(MOUNTPOINT + "/dir/file.txt") as test_file:
            actual = test_file.read().strip()
        self.assertEqual(new_string, actual)

    def test_write_file_independent(self):
        """Files /file.txt and /dir/file.txt are independent."""
        first_string = "This is root file."
        with open(MOUNTPOINT + "/file.txt", "w") as test_file:
            test_file.write(first_string)

        second_string = "This is dir file."
        with open(MOUNTPOINT + "/dir/file.txt", "w") as test_file:
            test_file.write(second_string)

        with open(MOUNTPOINT + "/file.txt") as test_file:
            actual = test_file.read().strip()
        self.assertEqual(first_string, actual)
