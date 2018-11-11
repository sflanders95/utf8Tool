#include <stdio.h>
#include <stdlib.h>
#include "utf8Util.h"


/*
   Binary/Hex/Dec Converter:
   http://calc.50x.eu
   Utf-8 calculator:
   http://www.ltg.ed.ac.uk/~richard/utf-8.cgi?input=383&mode=decimal
   RFC:
   http://www.ietf.org/rfc/rfc3629.txt
   Char. number range  |        UTF-8 octet sequence
      (hexadecimal)    |              (binary)
   --------------------+---------------------------------------------
   0000 0000-0000 007F | 0xxxxxxx                                    0     - 127
   0000 0080-0000 07FF | 110xxxxx 10xxxxxx                           128   - 2047
   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx                  2048  - 65535
   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx         65536 - 1114111
*/
char *DecimalToUtf8( unsigned long decimal )
{
    unsigned long allzeros = 0;
    unsigned long allOnes  = 4294967295; // 32 bit all ones.
    char *retStr;
    if (decimal < 128) // 8 bits
    {
        printf("here %lu\n", decimal);
        retStr = calloc(5, sizeof(char *)); // [ '\\', 'x', 'H', 'H', '\0' ]  "\xAA0"
        sprintf(retStr, "\\x%lux", decimal);
    }
    else if (decimal < 2048) // 16 bits
    {
        retStr = calloc(9, sizeof(char *)); //  "\xHH\xHH0"
        // 110xxxxx 10xxxxxx  bits 16 15 14 are always 110, bits 8 7 are always 10
        // start with num 10000000 with last six bits copied verbatim:
        unsigned long tmp = 128;

    }
    return retStr;
}

unsigned long *Utf8ToDecimal( char *utf8str )
{

    return 0x00;
}

char *DecimalToBinary(unsigned long decimal)
{
    char *retStr = calloc(33, sizeof(char));
    int j = 31;
    for (int i = 0; i < 32; i++) 
    {
        if (((decimal >> i) & 1U) == 1)
            retStr[j] = '1';
        else
            retStr[j] = '0';
        --j;
    }
    retStr[32] = '\0';
    return retStr;
}

