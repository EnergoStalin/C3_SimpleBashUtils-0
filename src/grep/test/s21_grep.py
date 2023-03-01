import glob, sys

sys.path.append('../')
from common.test.lib import *

tFiles = glob.glob('../common/test/cases/*')
tArgs = ['-i', '-v', '-c', '-l', '-n', '-h', '-s']

def test_with_args(args, **kwargs):
  run_tests('grep', args, tFiles, extra=["--color=never"], **kwargs)

# Common tests
test_with_args(tArgs, rArgs=['f'])
test_with_args(tArgs, rArgs=['-e', 'f'])
test_with_args(tArgs, rArgs=['-f', './test/regex'])


# -s test
print(tArgs.remove('-s'))
run_tests('grep', tArgs, [*tFiles, '12332141'], extra=["--color=never"], rArgs=['-s', 'f'])
