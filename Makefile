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
EXECUTABLE_EXTENSION=out

EXECUTABLE_BASENAME = NatoInvaders

SRC_EXTENSIONS=c
SRCS =$(foreach ext,$(SRC_EXTENSIONS),$(wildcard $(SRC_DIR)/*.$(ext)) )

# PKG_CONFIG_LIBS=sfml-all
CFLAGS = -g -Wall -Wextra -I$(INCLUDE_DIR) #$(shell pkg-config --cflags $(PKG_CONFIG_LIBS))
EXECUTABLE_DESTINATION=$(OUT_DIR)/$(EXECUTABLE_BASENAME).$(EXECUTABLE_EXTENSION)
LDFLAGS = #$(shell pkg-config --libs $(PKG_CONFIG_LIBS))

all: $(EXECUTABLE_DESTINATION)


$(EXECUTABLE_DESTINATION): $(SRCS) 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@






valgrind: 
	valgrind $(EXECUTABLE_DESTINATION)



# Clean up
clean:
	rm  $(BIN_FOLDER)/* $(OBJ_DIR)/*

# Phony targets
.PHONY: all clean valgrind 