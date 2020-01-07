OBJ := board.o interface.o move.o main.o
CC := gcc
CFLAGS := -lcurses

all: $(OBJ)
	$(CC) $(OBJ) -o 2048 $(CFLAGS)

$(OBJ): 2048.h

rebuild: clean $(OBJ) all

clean:
	rm $(OBJ)
