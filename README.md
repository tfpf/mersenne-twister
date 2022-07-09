# Generate and Solve Sudoku Puzzles
I just wanted to rewrite an old C program of mine using a better style, and
then verify that it worked correctly.

## Generate
```
python3 generate_sudoku.py 12
```
will print a sudoku puzzle of difficulty level 12 to standard output. Copy it
to a file, say, `sudoku.txt`. Alternatively, just redirect the output to
`sudoku.txt`.
```
python3 generate_sudoku.py 12 > sudoku.txt
```
A puzzle of difficulty level 0 (the minimum) is a solved puzzle, while one of
difficulty level 20 (the maximum) is an empty puzzle.

## Solve
```
gcc -O2 -std=c11 -Wall -Wextra -o solve_sudoku solve_sudoku.c
./solve_sudoku sudoku.txt
```
will display the solution. You can also pipe the puzzle directly to the solver:
```
python3 generate_sudoku.py 12 | ./solve_sudoku
```
but that is probably not what you want to do, since it doesn't show the puzzle
first.

The solver is rather primitive. If it cannot fill any cell in the puzzle after
multiple attempts, it makes a random guess. If, as a result of this, the puzzle
becomes unsolvable, it bins everything and starts a fresh attempt.
