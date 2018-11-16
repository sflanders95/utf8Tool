#include <ctype.h> // isprint
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // getopt
#include <string.h>  // strtok
// #include <wchar.h>   //wprintf
//#include "defs.h"
#include "getutf8.h"
#include "utf8Util.h"
#include "StreamHandler.h"
#include "ArgParser.h"

int main( int argc, char **argv )
{

    struct OptionArgs op = ParseArguments( argc,  argv );

    // This can occur with other cli options
    if (op.ShowHeader)
    {
        // print 0xEF,0xBB,0xBF - decimal: 15711167 (EFBBBF).  
        printf("\xEF\xBB\xBF");
    }

    // rest of options are mutually exclusive.
    if (TestForPipe())
    {
        // pipe data as input.
        ProcessStream();
    }
    else if (op.ShowDecimal)
    {
        #if _SHOWDEBUG
            printf("Showing single value: %lu\n", op.DecimalValue);
        #endif
        ShowChar(op.DecimalValue);
        printf("\n");
    }
    else if (op.ShowUtf8)
    {
        ShowChar(op.Utf8Value);
        printf("\n");
    }
    else if (op.ShowRange)
    {
        printf("Showing character Range: %lu to %lu\n", op.RangeStart, op.RangeEnd);
        ShowRange(op.RangeStart, op.RangeEnd);
    }
    else
    {   
	    printf( "%s\n", Usage() );
    }
    return 0;
} // main


char *Usage()
{
    return \
"Usage:\n\
\tgetutf8 [options]\n\
Where [options] are:\n\
\t-d #    - return just the character represented by the\n\
\t          decimal value.\n\
\t-b #    - return just the character represented by the \n\
\t          utf-8 interpreted value.\n\
\t-r #..# - show the utf-8 characters represented by the decimal \n\
\t          range #..# in tab delimited format. output contains\n\
\t          elements of both -d and -b.\n\
\t-h      - print out the utf-8 byte order mark: \\xEF\\xBB\\xBF";
}

/*
Example: 
   Smily UTF-8 Face

$ ./utf8Tool -r 128513..128513
Showing character Range: 128513 to 128513
dec     hex     char    utf-8 dec       utf-8 hex       utf-8 char      utf-8 binary
128513  #1f601  �       4036991105      #f09f9881       😁       11110000100111111001100010000001
$

or
$ ./utf8Tool -b 128513
😁
$
*/