CC=gcc
CFLAGS=

all : getutf8

getutf8 : src/main.o src/getutf8.o src/utf8Util.o src/test.o
	$(CC) $(CFLAGS) -o getutf8 src/main.o src/getutf8.o \
	    src/utf8Util.o src/test.o

main.o : src/main.c src/defs.h
	$(CC) $(CFLAGS) -c src/main.c

getutf8.o : src/getutf8.c src/getutf8.h
	$(CC) $(CFLAGS) -c src/getutf8.c

# /Users/sflanders95/git/getutf8/src/utf8Util.h
utf8Util.o : src/utf8Util.c src/utf8Util.h
	$(CC) $(CFLAGS) -c src/utf8Util.c

test.o : src/test.c src/test.h
	$(CC) $(CFLAGS) -c src/test.c

.PHONY : clean
clean  :
	rm -f getutf8 src/*.o



