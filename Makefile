TARGET_EXEC := game

CC=gcc
# CFLAGS=-lSDL2 -O3
CFLAGS=-lSDL2 -g

MY_SOURCES = src/main.c
MY_OBJS = $(patsubst %.c,%.o, $(MY_SOURCES))

all: my

%o: %.c
	$(CC) $(CFLAGS) -c $<

my: $(MY_OBJS)
	$(CC) $(CFLAGS) $^ -o $@
