PREFIX=arm-none-eabi-
CC = $(PREFIX)gcc

LDFLAGS = -L/opt/mylibs
LDLIBS = -lm

CFLAGS = -Wall -Werror -g -Og

CFILES  = $(wildcard *.c)

EXE = hello

OBJS = $(patsubst %.c,%.o,$(CFILES)) stubs.o
TARGET_ARCH = -mthumb
VPATH = libs

stubs.o: CFLAGS = -g -O2

all: $(EXE)

$(EXE) : $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(OBJS)
	rm -f $(EXE)

.PHONY: clean
