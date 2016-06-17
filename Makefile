CC = gcc
LD = gcc

CFLAGS  = -g -Wall -W $(shell pkg-config --cflags gtk+-3.0) -rdynamic
LDFLAGS = $(shell pkg-config --libs gtk+-3.0) -rdynamic

DESTDIR =

.PHONY: all install clean

all: GankIo-Desktop

install:

clean:
	-rm -f *.o
	-rm -f GankIo-Desktop

GankIo-Desktop: GankIo-Desktop.o
	${LD} -o $@ $< ${LDFLAGS}

%.o: %.c
	${CC} -c -o $@ $< ${CFLAGS}
