
#ifndef UTF8UTIL_H  /* include collision prevention */
#define UTF8UTIL_H

char *DecimalToUtf8( unsigned long );

unsigned long *Utf8ToDecimal( char * );

char *DecimalToBinary(unsigned long );

unsigned long BinaryToDecimal(char * );

#endif