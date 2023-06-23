#! /usr/bin/env python3

"""
A script to generate multiple sudoku puzzles quickly.
    python3 multigen.py [number of puzzles]
This will create a directory 'Problems' and write the puzzles to files in it. By default, 10 puzzles will be generated.
"""


import datetime
import os
import os.path
import multiprocessing
import subprocess
import sys


def create_puzzle(fname):
    """
Write a sudoku puzzle to a file, supressing standard error. Block until done.

:param fname: File to write to.
    """
    with open(fname, 'w') as stdout, open(os.devnull, 'w') as stderr:
       subprocess.call(('./sudoku', '10.8'), stdout=stdout, stderr=stderr)


def main():
    """Main function."""
    if not os.access('sudoku', os.X_OK):
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

    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    today = datetime.date.today()
    for i in range(num_of_puzzles):
        today += datetime.timedelta(days=1)
        fname = today.strftime(f'{directory}/S{i:02d}_%a-%d-%b-%Y.txt')
        pool.apply_async(create_puzzle, [fname])
    pool.close()
    pool.join()


if __name__ == '__main__':
    main()
