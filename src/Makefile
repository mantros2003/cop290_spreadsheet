CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJ = cell.o column.o utils.o nodes_ll.o database.o _parser.o hashset.o evaluator.o print.o
SRC = $(OBJ:.o=.c)
INPUT ?= main.c
INPUT_OUT = $(INPUT:.c=.o)
TARGET = run


all: $(TARGET) final

$(TARGET): $(OBJ) $(INPUT_OUT)
	@$(CC) $(CFLAGS) $(INPUT_OUT) $(OBJ) -o $(TARGET)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
final:
	@./$(TARGET)
clean:
	@rm -f *.o TESTINGCODES/*.o $(INPUT_OUT) $(TARGET)
