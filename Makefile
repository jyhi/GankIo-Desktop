CC = gcc
LD = gcc

CP = cp
RM = rm
CPFLAGS =
RMFLAGS = -f

CFLAGS  = -g -Wall -W \
          $(shell pkg-config --cflags gtk+-3.0) \
		  $(shell pkg-config --cflags gmodule-export-2.0) #GtkBuilder needs this.

LDFLAGS = $(shell pkg-config --libs gtk+-3.0) \
          $(shell pkg-config --libs gmodule-export-2.0)   #GtkBuilder needs this.

SRCDIR  =
DESTDIR = /usr/local
BINDIR  = $(DESTDIR)/bin


.PHONY: all install clean

all: GankIo-Desktop

install:
	${CP} GankIo-Desktop ${BINDIR}

clean:
	-${RM} ${RMFLAGS} *.o
	-${RM} ${RMFLAGS} GankIo-Desktop

GankIo-Desktop: GankIo-Desktop.o
	${LD} -o $@ $< ${LDFLAGS}

%.o: %.c
	${CC} -c -o $@ $< ${CFLAGS}
