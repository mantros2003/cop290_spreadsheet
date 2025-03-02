# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm  # Add math library if needed

# Directories
SRC_DIR = src
TEST_DIR = $(SRC_DIR)/test
TARGET_DIR = target
RELEASE_DIR = $(TARGET_DIR)/release
TEST_BUILD_DIR = $(TARGET_DIR)/tests

LATEX_COMP = pdflatex
REPORT_DIR = docs
REPORT_NAME = report

# Ensure necessary directories exist
$(shell mkdir -p $(RELEASE_DIR) $(TEST_BUILD_DIR))

# Program target
TARGET = $(RELEASE_DIR)/spreadsheet

# Source and object files
SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(RELEASE_DIR)/%.o, $(SRC_FILES))

# Test files
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(TEST_BUILD_DIR)/%.o, $(TEST_SRC))
TEST_BIN = $(patsubst $(TEST_DIR)/%.c, $(TEST_BUILD_DIR)/%, $(TEST_SRC))

# Compile the main program
$(TARGET): $(SRC_OBJ) $(RELEASE_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(RELEASE_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

report: $(REPORT_DIR)/$(REPORT_NAME).tex
	$(LATEX_COMP) $(REPORT_DIR)/$(REPORT_NAME).tex
	rm $(REPORT_NAME).aux $(REPORT_NAME).out $(REPORT_NAME).log


# Run the program
run: $(TARGET)
	@$(TARGET) 999 18278

# Compile and link test files
$(TEST_BUILD_DIR)/%: $(TEST_DIR)/%.c $(SRC_OBJ)
	$(CC) $(CFLAGS) $< $(SRC_OBJ) -o $@ $(LDFLAGS)

# Run all tests
test: $(TEST_BIN)
	@echo "Running tests..."
	@for test in $(TEST_BIN); do \
		echo "Executing $$test..."; \
		./$$test; \
		echo ""; \
	done

# Clean build artifacts
clean:
	rm -rf $(TARGET_DIR)
