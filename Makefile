SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -flto -std=c11 -Wall -Wextra -I./include
LDLIBS = -lm
RM     = rm -f

Sources    = mt19937.c solve_sudoku.c sudoku_utils.c
Objects    = $(Sources:%.c=lib/%.o)
Executable = solve_sudoku

.PHONY: clean

$(Executable): $(Objects)
	$(LINK.c) -o $(Executable) $(Objects) $(LDLIBS)

# Override the rule for this file, because it includes another file.
lib/mt19937.o: lib/mt19937.c lib/mt19937_common.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(Objects) $(Executable)
