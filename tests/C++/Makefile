SHELL    = /bin/sh
CXX      = g++
CPPFLAGS = -O2 -std=c++11 -Wall -Wextra
LDLIBS   = -lmt19937
RM       = rm -f

Sources    = tests.cc
Executable = tests

.PHONY: clean

$(Executable): $(Sources)

clean:
	$(RM) $(Executable)
