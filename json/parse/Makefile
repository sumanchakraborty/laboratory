
CC=gcc 
CFLAGS=-g -c -Wall
LDFLAGS=
SOURCES=parse test
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=json

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

