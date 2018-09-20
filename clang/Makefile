
#g++ main.c -o mainc -L/usr/local/lib/ -lhiredis

CC=gcc
EXEC=mainc
SRCS=main.c addsub.c myDisplay.c

OBJS=$(SRCS:.c=.o)


start: $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)
	@echo "---------ok--------"


clean:
	rm -rf $(OBJS) && rm -rf *~
