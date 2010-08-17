# this file belongs to `printable` http://github.com/amery/printable
#
# Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
# All rights reserved. See COPYING for details.

CC = gcc

CFLAGS = -W -Wall -std=c99
LDFLAGS =

CFLAGS += -O3
#CFLAGS += -g -pg
#LDFLAGS += -pg

APP = printable

SRCS = $(wildcard *.c)
HDRS = $(wildcard *.h)
OBJS = $(patsubst %.c,%.o,$(SRCS))

DESTDIR =
BINDIR  = /usr/local/bin

.PHONY: all clean install

all: $(APP)

$(APP): $(OBJS)

clean:
	rm -vf $(APP) *.o *~

install:
	cp $(APP) $(DESTDIR)$(BINDIR)/
	chmod 0755 $(DESTDIR)$(BINDIR)/$(APP)

.gitignore: Makefile
	for x in '*.o' $(APP) Makefile.deps; do \
	echo "$$x"; \
	done > $@

Makefile.deps: Makefile $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -MM $(SRCS) > $@

include Makefile.deps
