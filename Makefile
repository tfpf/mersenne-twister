SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O3 -flto -std=c11 -Wall -Wextra -I./include
LDLIBS = -lm -l$(Package)
RM     = rm -f
CP     = cp

Prefix = /usr
Package = mt19937
Sources = solve_sudoku.c sudoku_utils.c
Objects = $(Sources:%.c=lib/%.o)
SharedObject = lib/$(Package).so
Header = include/$(Package).h
Executable = solve_sudoku

.PHONY: clean install uninstall

$(Executable): $(Objects)
	$(LINK.c) -o $(Executable) $(Objects) $(LDLIBS)

install: uninstall $(SharedObject)
	$(CP) $(Header) $(Prefix)/include/$(Package).h
	$(CP) $(SharedObject) $(Prefix)/lib/lib$(Package).so

%.so: %.c %_defs.c
	$(CC) $(CFLAGS) -shared -o $@ $<

uninstall:
	$(RM) $(Prefix)/include/$(Package).h
	$(RM) $(Prefix)/lib/lib$(Package).so

clean:
	$(RM) $(Objects) $(SharedObject) $(Executable)
