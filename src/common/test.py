#! /usr/bin/python3

from datetime import datetime
import glob, itertools, os, random, subprocess, json, logging

from subprocess import CompletedProcess as Process

class CaseFailedException(Exception):
    def __init__(self, origout: 'Process', s21out: 'Process', valgrind: 'Process', *postarg) -> None:
        self.original = origout
        self.s21 = s21out
        self.valgrind = valgrind

        super().__init__(*postarg)

    def __str__(self) -> str:
        return json.dumps(self.__dict__, default=lambda o: o.stdout.decode('utf-8'))

def write_report(original: 'Process', s21: 'Process'):
    with open('stderr_s21', 'w', encoding='utf-8') as f:
        f.write(s21.stderr.decode('utf-8'))
    with open('stderr_original', 'w', encoding='utf-8') as f:
        f.write(original.stderr.decode('utf-8'))
    with open('stdout_s21', 'w', encoding='utf-8') as f:
        f.write(s21.stdout.decode('utf-8'))
    with open('stdout_original', 'w', encoding='utf-8') as f:
        f.write(original.stdout.decode('utf-8'))

def check_case(original: 'Process', s21: 'Process'):
    if(original.returncode != s21.returncode):
        raise Exception(f'Return codes not match ({original.returncode} != {s21.returncode})')
    if(original.stderr != s21.stderr):
        raise Exception(f'Stdout not match see (./stderr_s21 != ./stderr_original)')
    if(original.stdout != s21.stdout):
        raise Exception(f'Stdout not match see (./stdout_s21 != ./stdout_original)')

def invoke_case(exec: 'str', *args, stdin = None) -> 'str':
    orig = None
    s21 = None
    # valgrind = None
    try:
        orig = subprocess.run([exec, *args], stdin=stdin, capture_output=True)
        if(stdin): stdin.seek(0, 0)
        s21 = subprocess.run([f'./s21_{exec}', *args], stdin=stdin, capture_output=True)
        check_case(orig, s21)

        # valgrind = subprocess.run(['valgrind', '--', f'./s21_{exec}', *args], stdin=stdin, capture_output=True)
        # if(valgrind.returncode != 0 or valgrind.stderr.decode('utf-8').lower().find('no leaks are possible') == -1):
        #     raise Exception('Valgrind check failed')
    except Exception as ex:
        write_report(orig, s21) # type: ignore
        raise CaseFailedException(orig, s21, ex) # type: ignore
    return ' '.join(args) + ' OK'

def single_file_test(exec, args):
    random.shuffle(args)
    logger.info(f'Testing single file: {invoke_case(exec, *args)}')

def stdin_test(exec, args, file):
    random.shuffle(args)
    with open(file, 'r', encoding='utf-8') as f:
        logger.info(f'Testing stdin file: {invoke_case(exec, *args, stdin=f)}')

def multiple_file_test(exec, args):
    random.shuffle(args)
    logger.info(f'Testing multiple files: {invoke_case(exec, *args)}')

def cleanup():
    for _ in glob.glob('./std*'):
        os.remove(_)

def run_tests(name: str, all_args: 'str', file: 'str'):
    global logger
    logger = logging.getLogger(name)
    logger.setLevel(logging.INFO)
    logging.basicConfig(format='%(levelname)s:%(name)s:(%(asctime)s): %(message)s', datefmt='%H:%M:%S')

    start = datetime.now()

    try:
        all_files = glob.glob(os.path.join(os.path.dirname(file), 'cases/*'))
        for file in all_files:
            for i in range(1, len(all_args)):
                for chars in itertools.combinations(all_args, i):
                    char_list = list(chars)
                    args = [*list(map(lambda x: f'-{x}', char_list))]

                    single_file_test(name, [*args, file])
                    stdin_test(name, args, file)
                    multiple_file_test(name, [*args, *all_files])
    finally:
        logger.info(f'Elapsed time: {datetime.now() - start}')

