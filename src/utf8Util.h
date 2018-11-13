
#ifndef UTF8UTIL_H  /* include collision prevention */
#define UTF8UTIL_H

char *DecToEscUtf8( unsigned long );

unsigned long *Utf8ToDecimal( char * );

char *DecToBinary(unsigned long );

unsigned long BinaryToDecimal(char * );

unsigned long DecToUtf8( unsigned long );

char *Dec2Str( unsigned long );

// Private
unsigned long _DecToUtf8_2byte( unsigned long );
unsigned long _DecToUtf8_3byte( unsigned long );
unsigned long _DecToUtf8_4byte( unsigned long );

#endif