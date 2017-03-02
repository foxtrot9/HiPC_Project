CC=gcc
CFLAGS=-fopenmp
SOURCE_FILE=hipc.c
OUT_FILE=hipc.o

default: compile

compile: $(SOURCE_FILE)
	$(CC) $(SOURCE_FILE) -o $(OUT_FILE) $(CFLAGS)

clean:
	$(RM) $(OUT_FILE)
