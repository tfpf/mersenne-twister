SHELL    = /bin/sh
CXX      = g++
CPPFLAGS = -O3 -std=c++11 -Wall -Wextra
LDLIBS   = -lmt19937
RM       = rm -f

Source = $(wildcard *.cc)
Executable = $(Source:.cc=)

.PHONY: clean

$(Executable): $(Source)

clean:
	$(RM) $(Executable)
