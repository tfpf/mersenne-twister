#! /usr/bin/python3

import random
import sys
import threading
import time

###############################################################################

class SudokuThread(threading.Thread):
    '''\
A subclass to implement what is possibly the worst way to generate a sudoku
puzzle: building the rows by repeatedly permuting the numbers from 1 to 9.

Members:
    table: list of lists (sudoku table)
'''

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.table = [None for _ in range(9)]
        self.stop = threading.Event()

    ###########################################################################

    def show(self):
        '''\
Display the sudoku table. Adacent blocks have different background colours.
This is accomplished using an ANSI colour code.

Args:
    nothing
'''

        for i, row in enumerate(self.table):
            print('    ', end='')
            for j, num in enumerate(row):
                if (i // 3 + j // 3) % 2 == 0:
                    print('\033[100m', end = '')
                print(num, end = '')
                if j % 3 == 2:
                    print('\033[0m', end = '')
                print('  ', end = '')
            print()

    ###########################################################################

    def is_satisfactory(self, i):
        '''\
Check whether the row at position `i' of the sudoku table violates any rules.

Args:
    i: int (row to check for violations)

Returns:
    True (if there are no violations)
    False (if there are violations)
'''

        # Look for repeated numbers in columns. Compare row `i' with rows above
        # it.
        for j in range(i):
            if any(x == y for x, y in zip(self.table[i], self.table[j])):
                return False

        # Look for repeated values in blocks. Traverse each of the three blocks
        # the current row is a part of.
        for j in range(0, 9, 3):
            seen_numbers = set()
            for row in self.table[i - i % 3 : i + 1]:
                for num in row[j : j + 3]:
                    if num in seen_numbers:
                        return False
                    seen_numbers.add(num)

        return True

    ###########################################################################

    def run(self):
        for i in range(9):
            self.table[i] = [*range(1, 10)]

            # Keep generating new rows until we are told to stop.
            while True:
                if self.stop.is_set():
                    self.table = None
                    return

                random.shuffle(self.table[i])
                if self.is_satisfactory(i):
                    break

###############################################################################

def main():
    '''\
Main function.
'''

    # This is the initial number of seconds the main thread will wait for. If
    # the sudoku is not generated in this much time, it will request the other
    # thread to stop and try again.
    timeout = 5

    for i in range(1, 5):
        st = SudokuThread()
        st.start()
        time.sleep(timeout)
        st.stop.set()
        st.join()
        if st.table is not None:
            break

        print(f'Failed to generate a sudoku puzzle in {timeout:2d} seconds. Trying again …')
        timeout += 2 * i

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
                st.table[3 * i + k // 3][3 * j + k % 3] = '-'

    # Delete the remaining numbers.
    deletions -= block_deletions * 9
    while deletions > 0:
        i = random.choice(range(81))
        if st.table[i // 9][i % 9] != '-':
            st.table[i // 9][i % 9] = '-'
            deletions -= 1

    st.show()

###############################################################################

if __name__ == '__main__':
    main()

