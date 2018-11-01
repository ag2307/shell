# Shell Makefile

CC = gcc
CFLAGS  = -Wall -g
OBJ = shell.c

all: shell

shell: $(OBJ)
	$(CC) $(CFLAGS) -o shell $(OBJ) 
