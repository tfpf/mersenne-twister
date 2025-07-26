#! /usr/bin/env python3

import datetime
import subprocess
import sys

def main():
    try:
        num_of_puzzles = int(sys.argv[1])
    except (IndexError, ValueError):
        num_of_puzzles = 31

    with open("index.html", "w", encoding="utf8") as writer:
        print("<!DOCTYPE html><html><head><title>Sudoku</title></head><body>", file=writer)
        date = datetime.date.today()
        for _ in range(31):
            print("<h1>", date.strftime("%A %d %B %Y"), "</h1>", file=writer, sep="")
            for icon, difficulty in zip(["✍️", "✍️✍️"], ["11", "12"]):
                print("<h2>", icon, "</h2><pre>", file=writer, flush=True, sep="")
                subprocess.check_call(["./sudoku", difficulty], stdout=writer)
                print("</pre>", file=writer)
            date += datetime.timedelta(1)
        print("</body></html>", file=writer)


if __name__ == '__main__':
    main()
