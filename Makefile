# Basic Makefile for static or shared C library

# Compiler and archiver
CC = gcc
AR = ar
ARFLAGS = rcs

# Directories
SRC_DIR = src
OUT_DIR = out
OBJ_DIR=$(OUT_DIR)/obj
ASM_DIR=$(OUT_DIR)/asm
INCLUDE_DIR = include
INSTALLATION_DIR=/usr/local/bin

EXECUTABLE_BASENAME = TicTacToe

SRC_EXTENSIONS=c
OBJ_EXTENSION=o
NASM_EXTENSION=asm
SRCS =$(foreach ext,$(SRC_EXTENSIONS),$(wildcard $(SRC_DIR)/*.$(ext)) )
OBJS=$(SRCS:$(SRC_DIR)/%.$(SRC_EXTENSIONS)=$(OBJ_DIR)/%.$(OBJ_EXTENSION))
ASMS=$(SRCS:$(SRC_DIR)/%.$(SRC_EXTENSIONS)=$(ASM_DIR)/%.$(NASM_EXTENSION))


CFLAGS =-O3 -Wall -Wextra -I$(INCLUDE_DIR)
EXECUTABLE_DESTINATION=$(OUT_DIR)/$(EXECUTABLE_BASENAME)
NASM_FLAGS=-masm=intel -fno-asynchronous-unwind-tables -fno-ident

all: $(EXECUTABLE_DESTINATION)

$(EXECUTABLE_DESTINATION): $(SRCS) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


obj: $(OBJS)

asm: $(ASMS)

$(OBJ_DIR)/%.$(OBJ_EXTENSION) : $(SRC_DIR)/%.$(SRC_EXTENSIONS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM_DIR)/%.$(NASM_EXTENSION) : $(SRC_DIR)/%.$(SRC_EXTENSIONS)  | $(ASM_DIR)
	$(CC) $(CFLAGS) $(NASM_FLAGS) -S $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(ASM_DIR):
	mkdir -p $(ASM_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)


valgrind:
	valgrind $(EXECUTABLE_DESTINATION)

gdb:
	gdb ./$(EXECUTABLE_DESTINATION)

run:
	./$(EXECUTABLE_DESTINATION)

install:
	cp $(EXECUTABLE_DESTINATION) $(INSTALLATION_DIR)

uninstall:
	rm -f $(INSTALLATION_DIR)/$(EXECUTABLE_BASENAME)

# Clean up
clean:
	rm -rf $(OUT_DIR)

# Phony targets
.PHONY: all clean valgrind install uninstall gdb asm obj
