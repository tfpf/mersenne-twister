CFLAGS = -std=c11 -O3 -Wall -Wextra -I./include -flto -fstrict-aliasing
LDFLAGS = -shared

Prefix = /usr
Package = mt19937
Header = include/$(Package).h
HeaderDestination = $(Prefix)/include/$(Package).h
ifeq ($(OS), Windows_NT)
Library = lib/$(Package).dll
LibraryDestination = $(Prefix)/lib/$(Package).dll
LibraryDestinationWindows = $(Prefix)/bin/$(Package).dll
else
Library = lib/$(Package).so
LibraryDestination = $(Prefix)/lib/lib$(Package).so
endif

.PHONY: install uninstall

install: uninstall $(Library)
	cp $(Header) $(HeaderDestination)
	cp $(Library) $(LibraryDestination)
	if [ -n "$(LibraryDestinationWindows)" ];  \
	then  \
		cp $(Library) $(LibraryDestinationWindows);  \
	fi

$(Library): lib/$(Package).c lib/$(Package)_defs.c
	$(LINK.c) -o $@ $<

uninstall:
	$(RM) $(HeaderDestination) $(LibraryDestination) $(LibraryDestinationWindows)
