SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -flto -std=c11 -Wall -Wextra -I./include
LDLIBS = -lm
RM     = rm -f

Sources = mt19937.c solve_sudoku.c sudoku_utils.c
Objects = $(Sources:%.c=lib/%.o)
SharedObject = lib/mt19937.so
Executable = solve_sudoku

.PHONY: clean install

$(Executable): $(Objects)
	$(LINK.c) -o $(Executable) $(Objects) $(LDLIBS)

# Override the rule for this file, because it includes another file.
lib/mt19937.o: lib/mt19937.c lib/mt19937_common.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.so: %.o
	$(CC) $(CFLAGS) -shared -o $@ $<

install: $(SharedObject)
	cp include/mt19937.h /usr/include/mt19937.h
	cp $(SharedObject) /usr/lib/libmt19937.so

clean:
	$(RM) $(Objects) $(SharedObject) $(Executable)
