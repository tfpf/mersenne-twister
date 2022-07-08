#! /usr/bin/python3

import random
import sys
import threading

###############################################################################

class SudokuThread(threading.Thread):
    '''\
A subclass to implement what is possibly the worst way to generate a sudoku
puzzle: building the rows by repeatedly permuting the numbers from 1 to 9.

Members:
    table: list of lists (sudoku table)
    stop: threading.Event (flag which tells this thread to stop)
    deletions: int (number of numbers in `self.table' to be removed)
'''

    def __init__(self, deletions, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.table = [None] * 9
        self.stop = threading.Event()
        self.deletions = deletions

    ###########################################################################

    def show(self):
        '''\
Display the sudoku table. Draw adjacent blocks using different background
colours if the output is going to a terminal.

Args:
    nothing
'''

        stdout_is_terminal = sys.stdout.isatty()
        for i, row in enumerate(self.table):
            for j, num in enumerate(row):
                print('  ', end='')
                colour = not (i // 3 + j // 3) % 2 and stdout_is_terminal
                if colour and j % 3 == 0:
                    print('\033[37;100m', end='')
                print(num, end='')
                if colour and j % 3 == 2:
                    print('\033[0m', end='')
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

        # Look for repeated numbers in columns. Compare row `i' with the rows
        # above it.
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

        # Delete some numbers from each block.
        block_deletions = self.deletions // 9
        for i in range(3):
            for j in range(3):
                for k in random.sample(range(9), block_deletions):
                    self.table[3 * i + k // 3][3 * j + k % 3] = '-'

        # Delete some more numbers randomly.
        other_deletions = self.deletions - block_deletions * 9
        while other_deletions:
            i = random.choice(range(81))
            if self.table[i // 9][i % 9] != '-':
                self.table[i // 9][i % 9] = '-'
                other_deletions -= 1

        # Signal to the main thread that we're done.
        self.stop.set()

###############################################################################

def main():
    '''\
Main function.
'''

    try:
        difficulty = float(sys.argv[1])
        assert 0 <= difficulty <= 20
    except (AssertionError, IndexError, ValueError):
        difficulty = 15
    print(f'Difficulty Level: {difficulty}/20')
    deletions = round(difficulty / 20 * 81)

    # Start a thread to generate a sudoku puzzle. If that thread does not
    # terminate in some time, ask it to stop and try again.
    for timeout in range(4, 24, 4):
        st = SudokuThread(deletions)
        st.start()
        st.stop.wait(timeout=timeout)
        st.stop.set()
        st.join()
        if st.table is not None:
            st.show()
            return

        print(f'Failed to generate a sudoku puzzle in {timeout:2d} seconds. Trying again …')

    raise SystemExit(1)

###############################################################################

if __name__ == '__main__':
    main()

