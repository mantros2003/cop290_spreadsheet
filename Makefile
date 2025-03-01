CC = gcc
CFLAGS = -Wall -Wextra
DEBUG = -g

BUILD_DIR = target/release
EXEC_NAME = spreadsheet

SRC_FILES = src/main.c src/_parser.c src/cell.c src/column.c src/database.c src/evaluator.c src/hashset.c src/nodes_ll.c src/print.c src/utils.c

LATEX_COMP = pdflatex
REPORT_DIR = docs
REPORT_NAME = report

all: $(BUILD_DIR)/$(EXEC_NAME)

$(BUILD_DIR)/$(EXEC_NAME): $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(SRC_FILES) -lm

$(BUILD_DIR):
	mkdir target
	mkdir $(BUILD_DIR)

report: $(REPORT_DIR)/$(REPORT_NAME).tex
	$(LATEX_COMP) $(REPORT_DIR)/$(REPORT_NAME).tex
	rm $(REPORT_NAME).aux $(REPORT_NAME).out $(REPORT_NAME).log

run: $(BUILD_DIR)/$(EXEC_NAME)
	./$(BUILD_DIR)/$(EXEC_NAME) 999 18278

clean:
	rm $(BUILD_DIR)/$(EXEC_NAME)
