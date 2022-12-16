#! /usr/bin/python3
import glob, sys
from os import path

sys.path.append('../../')

from common.test import *

if __name__ == '__main__':
    cleanup()

    try:
        run_tests('cat', 'eivclnhso', list(map(lambda x: path.abspath(x), glob.glob('./cases/*'))))
    except CaseFailedException as ex:
        print(ex)
