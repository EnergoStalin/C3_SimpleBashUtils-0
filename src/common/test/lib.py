# Launch with Python 3.10.6

# Integrity tested on
# grep --version
# grep (GNU grep) 3.7
# Copyright (C) 2021 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
# This is free software: you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.

# Written by Mike Haertel and others; see
# <https://git.sv.gnu.org/cgit/grep.git/tree/AUTHORS>.

import subprocess, itertools, json, os, re

def update_debug_args(exe, args):
  try:
    with open('../../.vscode/launch.json', 'r+', encoding='utf-8') as f:
      launch = json.loads(re.sub('\\/\\/.*', '', f.read()))
      f.seek(0)
      i = [t['name'] for t in launch['configurations']].index(f's21_{exe} (gdb) Launch')
      launch['configurations'][i]['args'] = args
      f.truncate(0)
      json.dump(launch, f, indent=2)
  except:
    pass

def run_tests(exe, tArgs, tFiles, extra = [], rArgs = []):
  for f in ['valgrind', 's21', 'orig']:
      if(os.path.exists(f)):
        os.remove(f)

  for i in range(1, len(tArgs)):
    args = []
    for args in itertools.permutations(tArgs, i):
        args = [*rArgs, *args, *tFiles]
        s21 = subprocess.run([f'./s21_{exe}', *args], capture_output=True, timeout=3)
        orig = subprocess.run([exe, *args, *extra], capture_output=True, timeout=3)

        print(args)

        if (s21.stdout != orig.stdout):
            with open('./s21', 'wb') as f:
              f.write(s21.stdout)
            with open('./orig', 'wb') as f:
              f.write(orig.stdout)

            update_debug_args(exe, args)
              
            raise Exception(f'Stdout mismatch {json.dumps(args)}')
        
    args = ['valgrind', '--', f'./s21_{exe}', *args]
    valgrind = subprocess.run(args, capture_output=True, timeout=3)
    stderr = valgrind.stderr.decode('utf-8')
    if not('no leaks are possible' in stderr.lower()):
      with open('./valgrind', 'w', encoding='utf-8') as f:
        f.write(f'valgrind:\n\n{stderr}')
      raise Exception(f'Valgrind error {" ".join(args)}')
