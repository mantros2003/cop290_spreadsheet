CC = cc
CFLAGS = -Wall -Wextra
DEBUG = -g

EXEC_NAME = sheet

SRC_FILES = src/main.c src/_parser.c src/cell.c src/column.c src/database.c src/evaluator.c src/hashset.c src/nodes_ll.c src/print.c src/utils.c

LATEX_COMP = pdflatex
REPORT_DIR = docs
REPORT_NAME = report

all: $(EXEC_NAME)

$(EXEC_NAME):
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(SRC_FILES)

report: $(REPORT_DIR)/$(REPORT_NAME).tex
	$(LATEX_COMP) $(REPORT_DIR)/$(REPORT_NAME).tex
	rm $(REPORT_NAME).aux $(REPORT_NAME).out $(REPORT_NAME).log

clean:
	rm $(EXEC_NAME)
