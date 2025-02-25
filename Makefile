CC = cc
CFLAGS = -Wall -Wextra
DEBUG = -g

EXEC_NAME = sheet

SRC_FILES = main.c _parser.c cell.c column.c database.c evaluator.c hashset.c nodes_ll.c print.c utils.c

LATEX_COMP = pdflatex
REPORT_NAME = report

all: $(EXEC_NAME)

$(EXEC_NAME):
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(SRC_FILES)

report: $(REPORT_NAME).tex
	$(LATEX_COMP) $(REPORT_NAME).tex
	rm $(REPORT_NAME).aux $(REPORT_NAME).out $(REPORT_NAME).log

clean:
	rm $(EXEC_NAME)
