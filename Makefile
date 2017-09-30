# Shell Makefile

CC = gcc
CFLAGS  = -Wall -g
OBJ = shell.o

all: shell

shell: $(OBJ)
	$(CC) $(CFLAGS) -o shell $(OBJ) 

%.o: %.c
	$(CC) $(CFLAGS) -c $<
