CC=gcc
CFLAGS=-O3 -std=c99 -w
TARGET=kmstats
all: $(TARGET)

$(TARGET): kmstats.c
	$(CC) kmstats.c $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
