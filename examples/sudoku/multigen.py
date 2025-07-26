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
        for _ in range(num_of_puzzles):
            print("<h1>", date.strftime("%A %d %B %Y"), "</h1>", file=writer, sep="")
            for idx, difficulty in enumerate(["11", "12"], 1):
                print("<h2>", "✍️" * idx, "</h2><pre>", file=writer, flush=True, sep="")
                subprocess.check_call(["./sudoku", difficulty], stdout=writer)
                print("</pre>", file=writer)
            date += datetime.timedelta(1)
        print("</body></html>", file=writer)

    with open("index.html", "r", encoding="utf8") as reader:
        contents = reader.read()
    with open("index.html", "w", encoding="utf8") as writer:
        print(contents.replace("   ", " ┃ ").replace("\n\n", "\n  ━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"), file=writer)


if __name__ == '__main__':
    main()
