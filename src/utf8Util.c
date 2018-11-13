#include <stdio.h>
#include <stdlib.h>
// #include <math.h> // powl(x, y) // x^y
#include "utf8Util.h"
#include <string.h>


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
   Bitwise modifications:
   https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
   https://stackoverflow.com/questions/26004263/set-the-i-th-bit-to-zero
   https://www.geeksforgeeks.org/left-shift-right-shift-operators-c-cpp/
*/

// Escapes the given bytes described in parameter dec and 
// creates a character string.  
// Important!! Caller must free() the string.
// Status: Testing.
char *Dec2Str( unsigned long dec )
{
    unsigned long mask = 255;
    char tmp[20] = {'\0'};
    int skip = 0;
    for (int i = sizeof(dec) - 1; i >= 0; i--)
    {
        int byte = (dec >> (i*8)) & mask; // hide all but last 8 bits
        if ((byte != 0) || (strlen(tmp) > 0))
        {
            tmp[skip] = byte;
            tmp[++skip] = '\0';
        }
    }
    char *str = malloc((sizeof(char)*strlen(tmp)) + 1);
    sprintf(str, "%s", tmp);
    return str;
}

// transpose the decimal to utf-8 and then output it in escape codes.
// To view the codes in a utf-8 enabled terminal, you can use the output
// of this function with note single quotes:
//     echo -e '\xF0\x9F\x98\x81'
// !!Important!! Caller must invoke free() on the string returned.
// Status: incomplete.  need to finish thranslating \xHH from /"[HH]?"/
char *DecToEscUtf8( unsigned long dec )
{
    char *retStr;

    if ((0 <= dec) & (dec < 128))
    {
        retStr = calloc(2, sizeof(char *));
        retStr[0] = (char)dec;
        retStr[1] = '\0';
    }
    else if ((128 <= dec) && (dec < 1114112))
    {
        char tmp[33];
        sprintf(tmp, "%lx", DecToUtf8(dec));
        retStr = calloc(strlen(tmp) + 1, sizeof(char *));
        strcpy(retStr, tmp);
    }
    else
    {
        // ERROR: Invalid utf-8 character - Number is outside of [0..1114111]
        retStr = calloc(2, sizeof(char *));
        retStr[0] = '?';
        retStr[1] = '\0';
    }

    return retStr;
}

unsigned long *Utf8ToDecimal( char *utf8str )
{

    return 0x00;
}

// Create a char[32] string of all of the bits.
// Status: Complete.
char *DecToBinary(unsigned long decimal)
{
    int size = (int)(sizeof (unsigned long) * 8LU);
    char *retStr = calloc(size+1, sizeof(char));
    int j = size - 1;
    for (int i = 0; i < size; i++) 
    {
        if (((decimal >> i) & 1U) == 1)
            retStr[j] = '1';
        else
            retStr[j] = '0';
        --j;
    }
    retStr[size] = '\0';
    return retStr;
}

// Return the utf-8 interpreted value of a decimal.
// Status: Complete.
unsigned long DecToUtf8(unsigned long num)
{
    if ((0 <= num) & (num < 128))
    {
        return num;  // utf-8 1 byte compatible.
    }
    else if ((128 <= num) && (num < 2048))
    {
        return _DecToUtf8_2byte(num);
    }
    else if ((2048 <= num) && (num < 65536))
    {
        return _DecToUtf8_3byte(num);
    }
    else if ((65536 <= num) && (num < 1114112))
    {
        return _DecToUtf8_4byte(num);
    }
    else
    {
        // ERROR: Invalid utf-8 character - Number is outside of [0..1114111]
        return num;
    }
}

// Handles utf-8 2 byte representations of a decimal within [128..2047]
// Status: Complete.
unsigned long _DecToUtf8_2byte(unsigned long num)
{
    //             xxxyy yy  << shift 2      
    // Pattern: 110xxxxx 10xxxxxx
    unsigned long pattern = (1UL<<15) + (1UL<<14) + (1UL<<7); 
    unsigned long lastBits = 63UL & num;  // 00xxxxxx
    // middle 5 bits are 789AB are then sifted 2 bits left.
    // 00000xxx xx000000 becomes: 000xxxxx 00000000
    unsigned long midBits = ((31UL<<6) & num) <<2;
    // Now Put all three together:
    return pattern | lastBits | midBits;
}

// Handles utf-8 2 byte representations of a decimal between [2048..65535]
// Status: Complete.
unsigned long _DecToUtf8_3byte(unsigned long num)
{
    // Pattern: 1110xxxx 10xxxxxx 10xxxxxx
    unsigned long pattern = (1UL<<23) + (1UL<<22) + (1UL<<21) + (1UL<<15) + (1UL<<7);
    unsigned long lastBits = 63UL & num; // 00xxxxxx
    // middle (now) 6 bits are then shifted 2 bits left.
    // 0000xxxx xx000000 becomes: 00xxxxxx 00000000
    unsigned long midBits = ((63UL<<6) & num) <<2;
    // first 4 Bits shifted 4 left:  
    // xxxx0000 00000000 becomes: 0000xxxx 00000000 00000000
    unsigned long firstBits = ((15UL<<12) & num) <<4;
    // Now Put all three together:
    return pattern | lastBits | midBits | firstBits;
}

// Handles utf-8 2 byte representations of a decimal between [65536..1114111]
// Status: Complete.
unsigned long _DecToUtf8_4byte(unsigned long num)
{
    // Pattern: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    unsigned long pattern = (1UL<<31) + (1UL<<30) + (1UL<<29) + (1UL<<28) + (1UL<<23) + (1UL<<15) + (1UL<<7);
    unsigned long lastBits = 63UL & num; // 00xxxxxx
    // middle (now) 6 bits are then shifted 2 bits left.
    // 00000000 0000xxxx xx000000 becomes: 00000000 00xxxxxx 00000000
    unsigned long midBits1 = ((63UL<<6) & num) <<2;
    // next 6 Bits shifted 4 left: 
    // 000000xx xxxx0000 00000000 becomes: 00xxxxxx 00000000 00000000
    unsigned long midBits2 = ((63UL<<12) & num) <<4;
    // first 3 Bits shifted 6 left:  
    // 00000000 000xxx00 00000000 00000000 becomes: 00000xxx 00000000 00000000 00000000
    unsigned long firstBits = ((7UL<<18) & num) <<6;
    // Now Put all three together:
    return pattern | lastBits | midBits1 | midBits2 | firstBits;
}