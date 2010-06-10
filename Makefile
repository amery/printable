# this file belongs to `printable` http://github.com/amery/printable
#
# Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
# All rights reserved. See COPYING for details.
#
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

.PHONY: all clean

all: $(APP)

$(APP): $(OBJS)

clean:
	rm -vf $(APP) *.o *~

.gitignore: Makefile
	echo '*.o' > $@~
	echo $(APP) >> $@~
	mv $@~ $@
