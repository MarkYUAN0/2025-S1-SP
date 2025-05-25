CC      = gcc
CFLAGS  = -std=c99 -Wall


OBJS_COMMON = splitline.o execute.o fatal.o


part1: smsh2
smsh2: smsh2.o $(OBJS_COMMON)
	$(CC) $(CFLAGS) -o smsh2 smsh2.o $(OBJS_COMMON)


part2: smsh3
smsh3: smsh3.o $(OBJS_COMMON)
	$(CC) $(CFLAGS) -o smsh3 smsh3.o $(OBJS_COMMON)


part3: smsh4
smsh4: smsh4.o $(OBJS_COMMON)
	$(CC) $(CFLAGS) -o smsh4 smsh4.o $(OBJS_COMMON)


%.o: %.c smsh.h
	$(CC) $(CFLAGS) -c $<


splitline.o: splitline.c smsh.h
	$(CC) $(CFLAGS) -c splitline.c

execute.o: execute.c smsh.h
	$(CC) $(CFLAGS) -c execute.c

fatal.o: fatal.c smsh.h
	$(CC) $(CFLAGS) -c fatal.c

clean:
	rm -f *.o smsh2 smsh3 smsh4
