import glob, sys

sys.path.append('../')
from common.test.lib import *

tFiles = glob.glob('../common/test/cases/*')
tArgs = ['-i', '-v', '-c', '-l', '-n', '-h', '-s']

def file_list(args, **kwargs):
  grep(args, tFiles, **kwargs)

def grep(*args, **kwargs):
  run_tests('grep', *args, extra=["--color=never"], **kwargs)

# Common tests
file_list(tArgs, rArgs=['f'])
file_list(tArgs, rArgs=['-e', 'f'])
file_list(tArgs, rArgs=['-f', './test/regex'])

print(tArgs.remove('-s'))
run_tests('grep', tArgs, [*tFiles, '12332141'], extra=["--color=never"], rArgs=['-s', 'f'])

# Single file
for file in tFiles:
  grep(tArgs, [file], rArgs=['f'])
  grep(tArgs, [file], rArgs=['-e', 'f'])
  grep(tArgs, [file], rArgs=['-f', './test/regex'])
grep(tArgs, ['dasfagfweew'], rArgs=['-f', './test/regex', '-s'])

# -s test
