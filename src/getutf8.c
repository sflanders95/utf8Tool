#include <string.h>  // strlen()
#include <stdio.h>   // printf()
#include <stdlib.h>  // mem free()
#include "defs.h"    // right()
#include "utf8Util.h" 

void ShowRange(unsigned long start, unsigned long end)
{
    unsigned long utf8Dec = 0;
    // Format:
    //  "{dec}\t{hex}\t{dec char}\t{utf-8 dec}\t{utf-8 hex}\t{utf-8 char}\t{bin}\n"
    printf("dec\thex\tchar\tutf-8 dec\tutf-8 hex\tutf-8 char\tutf-8 binary\n");

    for (unsigned long dec = start; dec <= end; dec++)
    {
        char *decStr, *utf8Str, *utf8Bin;
        decStr = Dec2Str( dec );
        utf8Dec = DecToUtf8( dec );
        utf8Str = Dec2Str( utf8Dec );
        utf8Bin = DecToBinary( utf8Dec );
        // "{dec}\t{hex}\t{dec char}\t{utf-8 dec}\t{utf-8 hex}\t{utf-8 char}\t{bin}\n"
        printf("%lu\t#%lx\t%s\t%lu\t#%lx\t%s\t%s\n",
                dec,
                dec,
                decStr,
                utf8Dec,
                utf8Dec,
                utf8Str,
                right(utf8Bin,32));
        free(decStr);
        free(utf8Str);
        free(utf8Bin);
    }
}

/// <summary>
/// Displays character based on decimal value to stdout.
/// https://www.fileformat.info/info/unicode/utf8.htm
/// http://www.ietf.org/rfc/rfc3629.txt
/// </summary>
void ShowChar(int dec)
{
    char *str = Dec2Str(dec);
    printf("%s", str);
    free( str );
}