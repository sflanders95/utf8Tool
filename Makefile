CC=gcc
CFLAGS=

all : utf8Tool

utf8Tool : src/main.o src/getutf8.o src/utf8Util.o \
           src/ArgParser.o src/StreamHandler.o
	$(CC) $(CFLAGS) -o utf8Tool src/main.o src/getutf8.o \
	    src/utf8Util.o src/ArgParser.o src/StreamHandler.o

main.o : src/main.c 
	$(CC) $(CFLAGS) -c src/main.c

getutf8.o : src/getutf8.c src/getutf8.h
	$(CC) $(CFLAGS) -c src/getutf8.c

ArgParser.o : src/ArgParser.c src/ArgParser.h
	$(CC) $(CFLAGS) -c src/ArgParser.c

StreamHandler.o : src/StreamHandler.c src/StreamHandler.h src/defs.h src/utf8Util.h
	$(CC) $(CFLAGS) -c src/StreamHandler.c

utf8Util.o : src/utf8Util.c src/utf8Util.h
	$(CC) $(CFLAGS) -c src/utf8Util.c

.PHONY : clean
clean  :
	rm -f utf8Tool src/*.o



