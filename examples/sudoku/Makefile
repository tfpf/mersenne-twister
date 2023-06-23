CFLAGS = -std=c11 -O3 -Wall -Wextra -I./include
LDLIBS = -lm -lmt19937

Sources = $(wildcard lib/*.c)
Objects = $(Sources:.c=.o)
Executable = sudoku

$(Executable): $(Objects)
	$(LINK.c) -o $@ $^ $(LDLIBS)
