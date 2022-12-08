#! /usr/bin/python3

import subprocess, os, itertools

def get_test_files() -> 'list[str]':
    return os.listdir('./cases')

def check_case(original, s21):
    if(original.returncode != s21.returncode):
        raise Exception(f'Return codes not match ({original.returncode} != {s21.returncode})')
    if(original.stderr != s21.stderr):
        raise Exception(f'Sterr output not match ({original.stderr} != {s21.stderr})')
    if(original.stdout != s21.stdout):
        raise Exception(f'Stdout not match ({original.stdout} != {s21.stdout})')

def invoke_case(*args):
    try:
        check_case(
            subprocess.run(['cat', *args], capture_output=True),
            subprocess.run(['./s21_cat', *args], capture_output=True)
        )
        return ' '.join(args) + ' ok'
    except Exception as ex:
        return ' '.join(args) + f'\t\t{{{str(ex)}}}'

def main():
    for file in get_test_files():
        for i in range(1, 8):
            for chars in itertools.combinations('benstvTE', i):
                args = map(lambda x: f'-{x}', chars)
                path = os.path.join('./cases', file)
                print(invoke_case(*[*args, path]))

                args = '-' + ''.join(chars)
                print(invoke_case(*[args, path]))

                print()
                print()

if __name__ == '__main__':
    main()
