CFLAGS = -std=c11 -O3 -Wall -Wextra -I./include -flto -fstrict-aliasing
LDLIBS = -lm -l$(Package)
CP = cp

SolverSources = solve_sudoku.c sudoku_utils.c
SolverObjects = $(SolverSources:%.c=lib/%.o)

Prefix = /usr
Package = mt19937
Header = include/$(Package).h
HeaderDestination = $(Prefix)/include/$(Package).h

ifeq ($(OS), Windows_NT)
Library = lib/$(Package).dll
LibraryDestination = $(Prefix)/lib/$(Package).dll
LibraryDestinationWindows = $(Prefix)/bin/$(Package).dll
SolverExecutable = solve_sudoku.exe
else
Library = lib/$(Package).so
LibraryDestination = $(Prefix)/lib/lib$(Package).so
SolverExecutable = solve_sudoku
endif

.PHONY: clean install uninstall

$(SolverExecutable): $(SolverObjects)
	$(LINK.c) -o $@ $^ $(LDLIBS)

install: uninstall $(Library)
	$(CP) $(Header) $(HeaderDestination)
	$(CP) $(Library) $(LibraryDestination)
	if [ -n "$(LibraryDestinationWindows)" ];  \
	then  \
		$(CP) $(Library) $(LibraryDestinationWindows);  \
	fi

$(Library): lib/$(Package).c lib/$(Package)_defs.c
	$(CC) $(CFLAGS) -shared -o $@ $<

uninstall:
	$(RM) $(HeaderDestination)
	$(RM) $(LibraryDestination)
	$(RM) $(LibraryDestinationWindows)

clean:
	$(RM) $(SolverObjects) $(Library) $(SolverExecutable)
