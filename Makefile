CFLAGS = -std=c11 -O3 -Wall -Wextra -I./include -flto -fstrict-aliasing
LDLIBS = -lm -l$(Package)
CP = cp

Prefix = /usr
Package = mt19937
Sources = solve_sudoku.c sudoku_utils.c
Objects = $(Sources:%.c=lib/%.o)
Header = include/$(Package).h
HeaderDestination = $(Prefix)/include/$(Package).h
ifeq ($(OS), Windows_NT)
Library = lib/$(Package).dll
LibraryDestination = $(Prefix)/lib/$(Package).dll
LibraryDestinationWindows = /c/Windows/System32/$(Package).dll
Executable = solve_sudoku.exe
else
Library = lib/$(Package).so
LibraryDestination = $(Prefix)/lib/lib$(Package).so
Executable = solve_sudoku
endif

.PHONY: clean install uninstall

$(Executable): $(Objects)
	$(LINK.c) -o $(Executable) $(Objects) $(LDLIBS)

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
	$(RM) $(Objects) $(Library) $(Executable)
