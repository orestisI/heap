CC = gcc
CFLAGS = -g
TARGET = heap_ex
SOURCES = heap.c heap_ex.c
OBJ = $(patsubst %.c,%.o,$(SOURCES))

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)
	rm *.o

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
