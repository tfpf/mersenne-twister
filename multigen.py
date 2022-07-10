#! /usr/bin/python3

import datetime
import os
import sys

###############################################################################

def main():
    if not os.access('solve_sudoku', os.X_OK):
        raise SystemExit('Compile the C program first.')

    try:
        num_of_puzzles = int(sys.argv[1])
    except (IndexError, ValueError):
        num_of_puzzles = 10

    today = datetime.date.today()
    for i in range(num_of_puzzles):
        today += datetime.timedelta(days=1)
        fname = today.strftime(f'S{i:02d}_%d_%B_%Y.txt')
        os.system(f'./solve_sudoku 11.35 > {fname} 2> /dev/null &')

###############################################################################

if __name__ == '__main__':
    main()
