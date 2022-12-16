#! /usr/bin/python3
import subprocess, os, itertools, glob, random, test

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
    try:
        check_case(
            subprocess.run(['cat', *args], capture_output=True),
            subprocess.run(['./s21_cat', *args], capture_output=True)
        )
    except Exception as ex:
        print(ex, args)
        raise ex
    return ' '.join(args) + ' ok'

def single_file_test(args):
    print("Testing single file:")
    random.shuffle(args)
    print(invoke_case(*args))

def multiple_file_test(args):
    print("Testing multiple files:")
    random.shuffle(args)
    print(invoke_case(*args))

def main():
    for _ in glob.glob('./std*'):
        os.remove(_)

    err = None
    all_args = 'benstvTE'
    long_args = [
        '--squeeze-blank',
        '--number-nonblank',
        '--number',
    ]
    all_files = glob.glob('./cases/*')
    for file in all_files:
        for i in range(1, len(all_args)):
            for chars in itertools.combinations(all_args, i):
                char_list = list(chars)
                args = [*list(map(lambda x: f'-{x}', char_list))]

                try:
                    single_file_test([*args, file])
                    multiple_file_test([*args, *all_files])
                except:
                    break
            else:
                continue
            break
        else:
            continue
        break
    if(err):
        exit(1)

if __name__ == '__main__':
    main()
