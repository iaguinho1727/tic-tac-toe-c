# Basic Makefile for static or shared C library

# Compiler and archiver
CC = gcc
AR = ar
ARFLAGS = rcs

# Directories
SRC_DIR = src
OUT_DIR = out
INCLUDE_DIR = include
OBJ_DIR=$(OUT_DIR)/obj
INSTALLATION_DIR=/usr/local/bin

EXECUTABLE_BASENAME = TicTacToe

SRC_EXTENSIONS=c
SRCS =$(foreach ext,$(SRC_EXTENSIONS),$(wildcard $(SRC_DIR)/*.$(ext)) )


CFLAGS = -g -Wall -Wextra -I$(INCLUDE_DIR)
EXECUTABLE_DESTINATION=$(OUT_DIR)/$(EXECUTABLE_BASENAME)

all: $(EXECUTABLE_DESTINATION)

$(EXECUTABLE_DESTINATION): $(SRCS) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@



$(OUT_DIR):
	mkdir -p $(OUT_DIR)


valgrind:
	valgrind $(EXECUTABLE_DESTINATION)

run:
	./$(EXECUTABLE_DESTINATION)

install:
	cp $(EXECUTABLE_DESTINATION) $(INSTALLATION_DIR)

uninstall:
	rm -f $(INSTALLATION_DIR)/$(EXECUTABLE_BASENAME)

# Clean up
clean:
	rm  $(EXECUTABLE_DESTINATION)

# Phony targets
.PHONY: all clean valgrind install uninstall
