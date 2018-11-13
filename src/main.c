#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // getopt
#include <string.h>  // strtok
// #include <wchar.h>   //wprintf
#include "defs.h"
#include "getutf8.h"
#include "utf8Util.h"

int main( int argc, char **argv )
{
    bool showD = false;
    bool showR = false;
    bool showB = false;
    bool showBOM = false;
    char *argValue = NULL;
    int c; // getopt iterator

    opterr = 0; // mandatory, other apps can interfere with getopt
    while ((c = getopt (argc, argv, "d:r:b:h")) != -1)
    {
        switch (c)
        {
        case 'd':
            showD = true;
            argValue = optarg;
            break;
        case 'r':
            showR = true;
            argValue = optarg;
            break;
        case 'b':
            showB = true;
            argValue = optarg;
            break;
        case 'h':
            showBOM = true;
            break;
        case '?':
            if (optopt == 'd')
            fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
            fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
            return 1;
        default:
            abort ();
        }
    }
    
    if (showD)
    {
        unsigned long d = (unsigned long)atoll(argValue); // Dvalue);
        printf("Showing single value: %lu\n", d);
        ShowChar(d);
        printf("\n");
    }
    else if (showB)
    {
        // unsigned long dec = (unsigned long) atoll(Bvalue);
        unsigned long dec = (unsigned long) atoll(argValue);
        char *str;
        dec = DecToUtf8( dec );
        str = Dec2Str( dec );
        printf("%s\n", str);
        free(str);
    }
    else if (showR)
    {
        unsigned long start, end;
        char *s = calloc(10, sizeof(char*));
        char *e = calloc(10, sizeof(char*));
        int len = strlen(argValue); // Rvalue );
        bool found = false;
        int j = 0;

        for (int i = 0; i < len; i++)
        {
            if (!found)
            {
                // if (Rvalue[i] == '.')
                if (argValue[i] == '.')
                {
                    s[i] = '\0';
                    found = true;
                    i += 1;
                }
                else
                    s[i] = argValue[i];
                    // s[i] = Rvalue[i];
            }
            else
            {
               // e[j] = Rvalue[i];
               e[j] = argValue[i];
               j += 1;
               if (i == (len -1))
                  e[j] = '\0';
            }
        }

        start = (unsigned long)atoll(s); free(s); 
        end   = (unsigned long)atoll(e); free(e);
        printf("Showing character Range: %lu to %lu\n", start, end);
        ShowRange(start, end);
    }
    else if (showBOM)
    {
        // showing decimal: 15711167 doesn't cut it.  It prepends a byte
        // of zeros.  Instead print 0xEF,0xBB,0xBF and exit.
        printf("\xEF\xBB\xBF");
    }
    else
    {   
	    printf( "%s\n", Usage() );
    }
    return 0;
} // main

void ProcessArguments( int argc, char **argv )
{

}

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
\t          range #..# in tab delimited format.\n\
\t-h      - print out the utf-8 byte order mark: \\xEF\\xBB\\xBF";
}

/*
Example: 
   Smily UTF-8 Face

$ ./getutf8 -r 128513..128513
Showing character Range: 128513 to 128513
dec     hex     char    utf-8 dec       utf-8 hex       utf-8 char      utf-8 binary
128513  #1f601  �       4036991105      #f09f9881       😁       11110000100111111001100010000001
$

or
$ ./getutf8 -b 128513
😁
$
*/