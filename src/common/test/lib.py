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

import subprocess, itertools, json, os, re, shutil

def get_integrity_invocation(exe):
  integrity = f'{os.path.abspath("../common/integrity/")}/'
  if(os.path.exists(f'{integrity}{exe}')):
    return f'{integrity}{exe}'
  else:
    return exe


def run(*args, **kwargs):
  return subprocess.run(*args, capture_output=True, timeout=3, **kwargs)

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

def write_report(exe, args, s21, orig):
  try: os.mkdir('report')
  except: pass
  with open(f'./report/s21_{exe}.err', 'wb') as f:
    f.write(s21.stdout)
  with open(f'./report/{exe}.err', 'wb') as f:
    f.write(orig.stdout)

  with open(f'./report/{exe}.ver', 'w') as f:
    invoke = get_integrity_invocation(exe)
    f.write(f'{invoke}\n')
    f.write(run([invoke, '--version']).stdout)

  update_debug_args(exe, args)
    
  raise Exception(f'Stdout mismatch {json.dumps(args)}')

def valgrind_report(exe, args, stderr):
  with open(f'./report/s21_{exe}.valgrind', 'w', encoding='utf-8') as f:
    f.write(f'valgrind:\n\n{stderr}')
  raise Exception(f'Valgrind error {" ".join(args)}')

def valgrind_run(exe, args):
  args = ['valgrind', '--', os.path.abspath(f'./s21_{exe}'), *args]
  valgrind = run(args)
  stderr = valgrind.stderr.decode('utf-8')
  if not('no leaks are possible' in stderr.lower()):
    valgrind_report(exe, args, stderr)

def run_tests(exe, tArgs, tFiles, extra = [], rArgs = []):
  try: shutil.rmtree('./report')
  except: pass

  for i in range(1, len(tArgs)):
    args = []
    for args in itertools.combinations(tArgs, i):
        args = [*rArgs, *args, *tFiles]

        s21 = run([os.path.abspath(f's21_{exe}'), *args])
        orig = run([get_integrity_invocation(exe), *args])

        print(exe, args)

        if (s21.stdout != orig.stdout):
          write_report(exe, args, s21, orig)
    valgrind_run(exe, args)
