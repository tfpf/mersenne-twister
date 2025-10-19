#! /usr/bin/env python3

import datetime
import subprocess
import sys

html_begin = """
<!DOCTYPE html>
<html>
  <head>
    <title>Sudoku</title>
    <script>
        window.addEventListener("load", () => {
            const today = new Date();
            const headerId = today.getFullYear() + "-" + (today.getMonth() + 1) + "-" + today.getDate();
            const headerElement = document.getElementById(headerId);
            headerElement.scrollIntoView({behavior: "smooth", block: "start"});
        });
    </script>
    <style type="text/css">
      td {border: 1px solid; height: 30px; text-align: center; width: 30px;}
      td.even {background-image: linear-gradient(to bottom right, #D0E0E8, #FFFFFF)}
      td.odd {background-image: linear-gradient(to bottom left, #EADB99, #FFFFFF)}
    </style>
  </head>
  <body>
"""

html_end = """
  </body>
</html>
"""


def main():
    try:
        num_of_puzzles = int(sys.argv[1])
    except (IndexError, ValueError):
        num_of_puzzles = 32

    with open("index.html", "w", encoding="utf8") as writer:
        print(html_begin, file=writer)
        date = datetime.date.today()  # noqa: DTZ011
        for _ in range(num_of_puzzles):
            # JavaScript does not have a built-in method to write local dates
            # in the ISO 8601 format, so write the numbers manually.
            print(
                '    <h1 id="',
                date.year,
                "-",
                date.month,
                "-",
                date.day,
                '">',
                date.strftime("%A %d %B %Y"),
                "</h1>",
                file=writer,
                sep="",
            )
            for idx, difficulty in enumerate(["11", "12"], 1):
                print("    <h2>", "✍️" * idx, "</h2>", file=writer, flush=True, sep="")
                subprocess.check_call(["./sudoku", difficulty, "dummy argument to get HTML output"], stdout=writer)
            date += datetime.timedelta(1)
        print(html_end, file=writer)


if __name__ == "__main__":
    main()
