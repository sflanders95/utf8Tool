#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // getopt
#include <string.h>  // strtok
#include <wchar.h>   //wprintf
#include "defs.h"
#include "getutf8.h"
#include "utf8Util.h"

int main( int argc, char **argv )
{
    bool showD = false;
    bool showR = false;
    bool showB = false;
    char *Dvalue = NULL;
    char *Rvalue = NULL;
    char *Bvalue = NULL;
    int c;
    

    opterr = 0; // mandatory, other apps can interfere with getopt
    while ((c = getopt (argc, argv, "d:r:b:")) != -1)
    {
        switch (c)
        {
        case 'd':
            showD = true;
            Dvalue = optarg;
            break;
        case 'r':
            showR = true;
            Rvalue = optarg;
            break;
        case 'b':
            showB = true;
            Bvalue = optarg;
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
        int d = atoi(Dvalue);
        printf("Showing single value: %d\n", d);
        printf("%s\n", ShowChar(d));
    }
    else if (showR)
    {
        int start, end;
        char *s = calloc(10, sizeof(char*));
        char *e = calloc(10, sizeof(char*));
        int len = strlen( Rvalue );
        bool found = false;
        int j = 0;

        for (int i = 0; i < len; i++)
        {
            if (!found)
            {
                if (Rvalue[i] == '.')
                {
                    s[i] = '\0';
                    found = true;
                    i += 1;
                }
                else
                    s[i] = Rvalue[i];
            }
            else
            {
               e[j] = Rvalue[i];
               j += 1;
               if (i == (len -1))
                  e[j] = '\0';
            }
        }

        start = atoi(s);
        end = atoi(e);
        printf("Showing Range: %d to %d for %s\n", start, end, Rvalue);
        wprintf(L"%s\n", ShowRange(start, end));
        free(s); free(e);
    }
    else if (showB)
    {
        //printf ("Bvalue = ld\n",  atol(Bvalue) );
        unsigned long dec = (unsigned long)atol(Bvalue);
        char *bin = DecimalToBinary( dec );
        printf ("%lu = %s\n", dec, bin);
    }
    else
    {   

	    printf( "%s\n", Usage() );
    }
    return 0;
}

char *Usage()
{
    return \
"Usage:\n\
\tgetutf8 [options]\n\
Where [options] are:\n\
\t-d # - return just the character represented by the decimal value #\n\
\t-r #..# - show the characters represented by the decimal range #..#\n\
\t          in the format of d[tab]char\n";
}