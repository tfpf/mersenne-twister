#! /usr/bin/python3

import datetime
import multiprocessing
import sys

import generate_sudoku

###############################################################################

def wrapper(stdout):
    sys.stdout = stdout
    sys.argv[1] = 12
    generate_sudoku.main()

###############################################################################

def main():
    try:
        NUM_OF_PROC = int(sys.argv[1])
    except (IndexError, ValueError):
        NUM_OF_PROC = 10

    today = datetime.date.today()
    proc = [None] * NUM_OF_PROC

    for i in range(NUM_OF_PROC):
        today += datetime.timedelta(days=1)
        fname = today.strftime(f'0x{i:02x}_%d_%B_%Y.txt')
        with open(fname, 'w') as stdout:
            multiprocessing.Process(target=wrapper, args=(stdout,)).start()

###############################################################################

if __name__ == '__main__':
    main()

