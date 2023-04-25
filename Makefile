SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -flto -std=c11 -Wall -Wextra -I./include
LDLIBS = -lm -l$(Package)
RM     = rm -f
CP     = cp

Package = mt19937
Sources = solve_sudoku.c sudoku_utils.c
Objects = $(Sources:%.c=lib/%.o)
SharedObject = lib/$(Package).so
Header = include/$(Package).h
Executable = solve_sudoku

.PHONY: clean install uninstall

$(Executable): $(Objects)
	$(LINK.c) -o $(Executable) $(Objects) $(LDLIBS)

install: $(SharedObject)
	$(CP) $(Header) /usr/include/$(Package).h
	$(CP) $(SharedObject) /usr/lib/lib$(Package).so

%.so: %.c %_common.c
	$(CC) $(CFLAGS) -shared -o $@ $<

uninstall:
	$(RM) /usr/include/$(Package).h
	$(RM) /usr/lib/lib$(Package).so

clean:
	$(RM) $(Objects) $(SharedObject) $(Executable)
