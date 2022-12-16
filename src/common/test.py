#! /usr/bin/python3

import glob, itertools, os, random, subprocess
from typing import Any

class CaseFailedException(Exception):
    def __init__(self, args, origout, s21out, *postarg) -> None:
        self.args = args
        self.original = origout
        self.s21 = s21out

        super().__init__(*postarg)

    def __str__(self) -> str:
        return super().__str__()

def check_case(original: 'subprocess.CompletedProcess', s21: 'subprocess.CompletedProcess'):
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

def invoke_case(exec: 'str', *args) -> 'str':
    orig = 0
    s21 = 0
    try:
        orig = subprocess.run([exec, *args], capture_output=True)
        s21 = subprocess.run([f'./s21_{exec}', *args], capture_output=True)
        check_case(
            orig,
            s21
        )
    except Exception as ex:
        raise CaseFailedException(args, orig, s21, ex)
    return ' '.join(args) + ' ok'

def single_file_test(exec, args):
    print("Testing single file:")
    random.shuffle(args)
    print(invoke_case(exec, *args))

def multiple_file_test(exec, args):
    print("Testing multiple files:")
    random.shuffle(args)
    print(invoke_case(exec, *args))

def cleanup():
    for _ in glob.glob('./std*'):
        os.remove(_)

def run_tests(name: str, all_args: 'str', all_files: 'list[str]'):
    for file in all_files:
        for i in range(1, len(all_args)):
            for chars in itertools.combinations(all_args, i):
                char_list = list(chars)
                args = [*list(map(lambda x: f'-{x}', char_list))]

                single_file_test(name, [*args, file])
                multiple_file_test(name, [*args, *all_files])

