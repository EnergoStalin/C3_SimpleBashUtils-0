import subprocess, itertools, json, os

def run_tests(exe, tArgs, tFiles, extra = [], rArgs = []):
  eReport = './report'
  if(os.path.exists(eReport)):
    os.remove(eReport)

  for i in range(1, len(tArgs)):
    args = []
    for args in itertools.permutations(tArgs, i):
        args = [*rArgs, *args, *tFiles]
        s21 = subprocess.run([f'./s21_{exe}', *args], capture_output=True, timeout=3)
        orig = subprocess.run([exe, *args, *extra], capture_output=True, timeout=3)

        print(args)

        if (s21.stdout != orig.stdout):
            with open(eReport, 'w') as f:
                f.write(f's21:\n\n{s21.stdout.decode("utf-8")}\n\n\norig:\n\n{orig.stdout.decode("utf-8")}')
            raise Exception(f'Stdout mismatch {json.dumps(args)}')
        
    args = ['valgrind', '--', f'./s21_{exe}', *args]
    valgrind = subprocess.run(args, capture_output=True, timeout=3)
    stderr = valgrind.stderr.decode('utf-8')
    if not('no leaks are possible' in stderr.lower()):
      with open(eReport, 'w') as f:
        f.write(f'valgrind:\n\n{stderr}')
      raise Exception(f'Valgrind error {" ".join(args)}')
