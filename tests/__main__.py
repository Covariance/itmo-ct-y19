"""Tests runner."""

import unittest

from tests.fs import TestPreparer

from tests.basic import BasicTestCases
from tests.remove import RemoveTestCases
from tests.netfile import NetfileTestCases
from tests.netdir import NetdirTestCases


if __name__ == '__main__':
    preparer = TestPreparer()
    try:
        preparer.prepare()
        unittest.main()
    finally:
        preparer.release()
