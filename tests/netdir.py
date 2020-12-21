"""Tests for the main task."""
import logging
import os
import random
import unittest
import urllib.request

from tests.constants import API_BASE, MOUNTPOINT

logging.basicConfig(
    level=logging.INFO,
    format='[%(asctime)s] %(filename)s:%(lineno)d: %(message)s'
)

TOKEN = os.environ["FS_TOKEN"]


def random_some(values):
    random.shuffle(values)
    size = random.randint(1, len(values))
    return values[:size]


class NetdirTestCases(unittest.TestCase):
    """Tests for the bonus task 7."""
    def test_list(self):
        """Can ls netdir."""
        for _ in range(5):
            expected = random_some([
                "test.txt", "noext", "work.mp4",
                "good.wav", "test_1", "52-5"
            ])

            urllib.request.urlopen(
                "/".join([API_BASE, TOKEN, "list"]),
                data="".join([
                    file + "\n"
                    for file in expected
                ]).encode()
            )
            actual = os.listdir(MOUNTPOINT + "/netdir")

            self.assertEqual(sorted(expected), sorted(actual))
