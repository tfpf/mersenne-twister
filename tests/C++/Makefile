SHELL  = /bin/sh
CC     = g++
CFLAGS = -O2 -std=c++11 -Wall -Wextra
LDLIBS = -lmt19937
RM     = rm -f

Sources    = tests.cc
Executable = tests

.PHONY: clean

$(Executable): $(Sources)
	$(CC) $(CFLAGS) -o $(Executable) $(Sources) $(LDLIBS)

clean:
	$(RM) $(Executable)
