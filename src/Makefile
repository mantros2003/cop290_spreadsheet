CC = cc
CFLAGS = -Wall -Wextra
DEBUG = -g

EXEC_NAME = sheet

SRC_FILES = main.c _parser.c cell.c column.c database.c evaluator.c hashset.c nodes_ll.c print.c utils.c

all: $(EXEC_NAME)

$(EXEC_NAME):
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(SRC_FILES)