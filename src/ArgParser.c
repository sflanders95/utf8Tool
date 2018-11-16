#include <unistd.h>  // getopt
#include <stdio.h>   // stderr
#include <ctype.h>   // isprint
#include <string.h>  // strlen
#include <stdlib.h>
#include "ArgParser.h"
#include "defs.h"
#include "utf8Util.h"


struct OptionArgs ParseArguments(int argc, char **argv)
{
    struct OptionArgs op = NewOptionArgs();

    #if _SHOWDEBUG // verbose debug
    printf_s( "\nCommand-line arguments:\n" );  
    for( int count = 0; count < argc; count++ )  
        printf("  argv[%d]   %s\n", count, argv[count]);  
    #endif

    opterr = 0; // mandatory, other apps can interfere with getopt
    char c;
    while ((c = getopt (argc, argv, "d:r:b:h")) != -1)
    {
        switch (c)
        {
        case 'd':
            op.ShowDecimal = true;
            op.DecimalValue = atoll(optarg); // can throw err.
            break;
        case 'r':
            op.ShowRange = true;
            // unsigned long *Range = _ParseRange(optarg, &op); // can throw err.
            // op.RangeStart = Range[0];
            // op.RangeEnd = Range[1];
            _ParseRange(optarg, &op); // can throw err.
            break;
        case 'b':
            op.ShowUtf8 = true;
            op.Utf8Value = DecToUtf8( atoll(optarg)); // can throw err.
            break;
        case 'h':
            op.ShowHeader = true;
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
            return op;
        default:
            abort ();
        }
    }
    return op;
}

// Return array with [start, end] where the input
// is "start..end"
void _ParseRange(char *Range, struct OptionArgs *op)
{
    unsigned long retVal[2] = { 0UL, 0UL };
    char *s = calloc(10, sizeof(char*)); s[0]='0'; s[1]='\0';
    char *e = calloc(10, sizeof(char*)); e[0]='0'; e[1]='\0';
    int len = strlen(Range);
    bool found = false;
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (!found)
        {
            if (Range[i] == '.')
            {
                s[i] = '\0';
                found = true;
                i += 1;
            }
            else
                s[i] = Range[i];
        }
        else
        {
            e[j] = Range[i];
            j += 1;
            if (i == (len -1))
                e[j] = '\0';
        }
    }
    // retVal[0] = (unsigned long)atoll(s); free(s); 
    // retVal[1] = (unsigned long)atoll(e); free(e);
    op ->RangeStart = (unsigned long)atoll(s);  free(s); 
    op ->RangeEnd = (unsigned long)atoll(e); free(e);
}

struct OptionArgs NewOptionArgs () // init object
{ 
    struct OptionArgs op;
    op.ShowDecimal = false;
    op.DecimalValue = 0UL;
    op.ShowUtf8 = false;
    op.Utf8Value = 0UL;
    op.ShowRange = false;
    op.RangeStart = 0UL;
    op.RangeEnd = 0UL;
    op.RangeStart = 0UL;
    op.RangeEnd = 0UL;
    op.ShowHeader = false;
    op.Error = false;
    return op;
};