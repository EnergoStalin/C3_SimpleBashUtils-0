#! /usr/bin/python3

import subprocess, os, itertools, glob

def check_case(original, s21):
    if(original.returncode != s21.returncode):
        raise Exception(f'Return codes not match ({original.returncode} != {s21.returncode})')
    if(original.stderr != s21.stderr):
        with open('stderr_s21', 'w', encoding='utf-8') as f:
            f.write(s21.stderr.decode('utf-8'))
        with open('stderr_original', 'w', encoding='utf-8') as f:
            f.write(original.stderr.decode('utf-8'))
        raise Exception(f'Stdout not match see (./stderr_s21 != ./stderr_original)')
    if(original.stdout != s21.stdout):
        with open('stdout_s21', 'w', encoding='utf-8') as f:
            f.write(s21.stdout.decode('utf-8'))
        with open('stdout_original', 'w', encoding='utf-8') as f:
            f.write(original.stdout.decode('utf-8'))
        raise Exception(f'Stdout not match see (./stdout_s21 != ./stdout_original)')

def invoke_case(*args):
    check_case(
        subprocess.run(['cat', *args], capture_output=True),
        subprocess.run(['./s21_cat', *args], capture_output=True)
    )
    return ' '.join(args) + ' ok'

def main():
    err = None
    all_args = 'benstvTE'
    all_files = glob.glob('./cases/*')
    for file in all_files:
        for i in range(1, len(all_args)):
            for chars in itertools.combinations(all_args, i):
                print("Testing single file argument variants:")
                args = map(lambda x: f'-{x}', chars)
                try:
                    print(invoke_case(*[*args, file]))
                except Exception as ex:
                    if(not err): err = ex
                    print(ex, chars)

                args = '-' + ''.join(chars)
                try:
                    print(invoke_case(*[args, file]))
                except Exception as ex:
                    if(not err): err = ex
                    print(ex, args)

                print("Testing multiple files")
                args = [args, *all_files]
                try:
                    print(invoke_case(*args))
                except Exception as ex:
                    if(not err): err = ex
                    print(ex, args)
                print()

    if(err):
        exit(1)

if __name__ == '__main__':
    main()
