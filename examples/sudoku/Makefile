CFLAGS = -std=c11 -O3 -Wall -Wextra -I./include
LDLIBS = -lm -lmt19937

Sources = $(wildcard lib/*.c)
Objects = $(Sources:.c=.o)
ifeq ($(OS), Windows_NT)
Executable = sudoku.exe
else
Executable = sudoku
endif

$(Executable): $(Objects)
	$(LINK.c) -o $@ $^ $(LDLIBS)
