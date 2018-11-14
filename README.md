
# utf8Tool

This is a command line utility that encodes decimals as utf-8 encoded text.

# Sample:
Example: 
>> Smily UTF-8 Face
``` block
$ ./utf8Tool -r 128513..128513
Showing character Range: 128513 to 128513
dec     hex     char    utf-8 dec       utf-8 hex       utf-8 char      utf-8 binary
128513  #1f601  �       4036991105      #f09f9881       😁       11110000100111111001100010000001
$
$ ./utf8Tool -b 128513
😁
$
$ ./utf8Tool
Usage:
  	getutf8 [options]
Where [options] are:
	-d #    - return just the character represented by the
	          decimal value.
	-b #    - return just the character represented by the 
	          utf-8 interpreted value.
	-r #..# - show the utf-8 characters represented by the decimal 
	          range #..# in tab delimited format.
	-h      - print out the utf-8 byte order mark: \xEF\xBB\xBF
```

# Building
Sample Session:
``` block
$ make -ver
GNU Make 3.81
Copyright (C) 2006  Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

This program built for i386-apple-darwin11.3.0
$ gcc --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/usr/include/c++/4.2.1
Apple LLVM version 10.0.0 (clang-1000.11.45.2)
Target: x86_64-apple-darwin17.7.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
$ make clean
rm -f utf8Tool src/*.o
$ make
gcc    -c -o src/main.o src/main.c
gcc    -c -o src/getutf8.o src/getutf8.c
gcc    -c -o src/utf8Util.o src/utf8Util.c
gcc  -o utf8Tool src/main.o src/getutf8.o \
	    src/utf8Util.o
$
```

<img width="80%" height="1px"/>[/sflanders95/utf8Tool]


[/sflanders95/utf8Tool]: https://github.com/sflanders95/utf8Tool