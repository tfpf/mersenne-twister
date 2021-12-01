#! /usr/bin/python3

import random
import sys
import threading
import time

###############################################################################

class SudokuThread(threading.Thread):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.table = [None for _ in range(1, 10)]

    def run(self):
https://stackoverflow.com/questions/6893968/how-to-get-the-return-value-from-a-thread-in-python

###############################################################################

def is_satisfactory(table, i):
    '''\
Check whether the row at position `i' of the sudoku table violates any rules.

Args:
    table: list of lists (sudoku table)
    i: int (row to check for violations)

Returns:
    True (if there are no violations)
    False (if there are violations)
'''

    # Look for repeated numbers in columns. Compare row `i' with rows above it.
    for j in range(i):
        if any(x == y for x, y in zip(table[i], table[j])):
            return False

    # Look for repeated values in blocks. Traverse each of the three blocks the
    # current row is a part of.
    for j in range(0, 9, 3):
        seen_numbers = set()
        for row in table[i - i % 3 : i + 1]:
            for num in row[j : j + 3]:
                if num in seen_numbers:
                    return False
                seen_numbers.add(num)

    return True

###############################################################################

def show(table):
    '''\
Display the sudoku table. Adacent blocks have different background colours.
This is accomplished using an ANSI colour code.

Args:
    table: list of lists (sudoku table)
'''

    # The background colour is set at the start of a block and cleared at the
    # end.
    for i, row in enumerate(table):
        print('    ', end='')
        for j, num in enumerate(row):
            if (i // 3 + j // 3) % 2 == 0:
                print('\033[100m', end = '')
            print(num, end = '')
            if j % 3 == 2:
                print('\033[0m', end = '')
            print('  ', end = '')
        print()

###############################################################################

def generate_sudoku():
    '''\
Probably the worst way to generate a sudoku puzzle! Obtain a random permutation
of the numbers from 1 to 9, and check whether this permutation can be used as a
row in the puzzle. Repeat for all rows.

Args:
    nothing

Returns:
    table: list of lists (sudoku table)
'''

    table = [None for _ in range(1, 10)]
    for i in range(9):
        table[i] = list(range(1, 10))
        while True:
            random.shuffle(table[i])
            if is_satisfactory(table, i):
                break

    return table

###############################################################################

def main():
    # table = generate_sudoku()
    thread = threading.Thread(target=generate_sudoku)
    thread.start()
    print('Launched the thread.')
    thread.join()

    try:
        difficulty = int(sys.argv[1])
        assert 0 <= difficulty <= 20
    except (AssertionError, IndexError, ValueError):
        difficulty = 15
    print(f'Difficulty Level: {difficulty:2d}/20')
    deletions = round(difficulty / 20 * 81)

    # Delete some numbers from each block.
    block_deletions = deletions // 9
    for i in range(3):
        for j in range(3):
            for k in random.sample(range(9), block_deletions):
                table[3 * i + k // 3][3 * j + k % 3] = '-'

    # Delete the remaining numbers.
    deletions -= block_deletions * 9
    while deletions > 0:
        i = random.choice(range(81))
        if table[i // 9][i % 9] != '-':
            table[i // 9][i % 9] = '-'
            deletions -= 1

    show(table)

###############################################################################

if __name__ == '__main__':
    main()

