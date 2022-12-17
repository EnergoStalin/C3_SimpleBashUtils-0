#! /usr/bin/python3
import glob, sys
from os import path

sys.path.append('../../')

from common.test import *

if __name__ == '__main__':
    cleanup()

    run_tests('cat', 'benstvTE', __file__)
