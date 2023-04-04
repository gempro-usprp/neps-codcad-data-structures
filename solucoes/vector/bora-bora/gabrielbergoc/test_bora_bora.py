import os
import pytest
import bora_bora
from unittest.mock import patch
from io import StringIO


class Test:
    test_dir = os.path.join(os.getcwd(), 'test')
    in_dir = os.path.join(test_dir, 'in')
    expected_dir = os.path.join(test_dir, 'expected')
    test_cases_count = len(os.listdir(in_dir))

    @staticmethod
    def get_in_file(test_case):
        return os.path.join(Test.in_dir, str(test_case))

    @staticmethod
    def get_expected_file(test_case):
        return os.path.join(Test.expected_dir, str(test_case))

    @pytest.mark.parametrize("test_case", range(1, test_cases_count + 1))
    def test(self, test_case):
        with open(Test.get_in_file(test_case)) as in_file, open(Test.get_expected_file(test_case)) as expected_file:
            in_ = in_file.read().splitlines()
            expected = expected_file.read()

        with patch('builtins.input', side_effect=in_), \
                patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            bora_bora.main()
            output = mock_stdout.getvalue()
            assert output == expected
