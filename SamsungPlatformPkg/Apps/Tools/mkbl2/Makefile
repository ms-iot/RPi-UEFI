CC=gcc

CFLAGS=-g -Wall

CSRCS =	./mkbl2.c \

OBJS = $(CSRCS:.c=.o)

.SUFFIXES:.c.o

all: mkbl2

testxv: $(OBJS)
	$(CC) $(CFLAGS) -g -o $@ $(OBJS)
	
.c.o:
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm -f mkbl2 $(OBJS) 

