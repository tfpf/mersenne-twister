import datetime
import subprocess
import sys

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
            proc[i] = subprocess.Popen(('./generate_sudoku.py', '12'), stdout=stdout)

    _ = [p.wait() for p in proc]

###############################################################################

if __name__ == '__main__':
    main()

