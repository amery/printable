CC = gcc
RAGEL = ragel

CFLAGS = -W -Wall
LDFLAGS =
RAGELOPT = -C

CFLAGS += -O3
#CFLAGS += -g -pg
#LDFLAGS += -pg

APP = printable

RL = $(wildcard *.rl)
G_SRCS = $(patsubst %.rl,%.c,$(RL))
SRCS = $(sort $(G_SRCS) $(wildcard *.c))
HDRS = $(wildcard *.h)
OBJS = $(patsubst %.c,%.o,$(SRCS))

.PRECIOUS: $(G_SRCS)
.PHONY: all clean

all: $(APP)

$(APP): $(OBJS)

%.c: %.rl
	$(RAGEL) $(RAGELOPT) -o $@ $^

clean:
	rm -vf $(APP) $(G_SRCS) *.o *~

.gitignore: Makefile
	echo '*.o' > $@~
	echo $(APP) >> $@~
	echo $(G_SRCS) >> $@~
	mv $@~ $@
