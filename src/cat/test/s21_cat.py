import glob, sys

sys.path.append('../')
from common.test.lib import *

tFiles = glob.glob('../common/test/cases/*')
tArgs = ['-b', '-e', '-n', '-s', '-t', '-v']

# Common tests
run_tests('cat', tArgs, tFiles)
