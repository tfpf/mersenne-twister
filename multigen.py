#! /usr/bin/python3

import datetime
import os
import os.path
import subprocess
import sys


def main():
    if not os.access('solve_sudoku', os.X_OK):
        raise SystemExit('Compile the C program first.')

    try:
        num_of_puzzles = int(sys.argv[1])
    except (IndexError, ValueError):
        num_of_puzzles = 10

    directory = 'Problems'
    try:
        os.mkdir(directory)
    except FileExistsError as e:
        if not os.path.isdir(directory):
            raise

    today = datetime.date.today()
    for i in range(num_of_puzzles):
        today += datetime.timedelta(days=1)
        fname = today.strftime(f'{directory}/S{i:02d}_%a-%d-%b-%Y.txt')
        with open(fname, 'w') as stdout, open(os.devnull, 'w') as stderr:
            subprocess.Popen(('./solve_sudoku', '11.35'), stdout=stdout, stderr=stderr)


if __name__ == '__main__':
    main()
