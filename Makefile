CC=gcc
CFLAGS=

all : utf8Tool

utf8Tool : src/main.o src/getutf8.o src/utf8Util.o
	$(CC) $(CFLAGS) -o utf8Tool src/main.o src/getutf8.o \
	    src/utf8Util.o

main.o : src/main.c src/defs.h
	$(CC) $(CFLAGS) -c src/main.c

getutf8.o : src/getutf8.c src/getutf8.h
	$(CC) $(CFLAGS) -c src/getutf8.c

utf8Util.o : src/utf8Util.c src/utf8Util.h
	$(CC) $(CFLAGS) -c src/utf8Util.c

.PHONY : clean
clean  :
	rm -f utf8Tool src/*.o



