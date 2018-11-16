#ifndef ARGPARSER_H  /* include collision prevention */
#define ARGPARSER_H
#include "defs.h" // for bool

// typedef struct Options OptionArgs;
struct OptionArgs {
   // Given a decimal number as input, print only its literal
   // character value.
   bool ShowDecimal;  // -d
   unsigned long DecimalValue; // -d Value
   // Given a decimal number as input, translate that number
   // to utf-8 and then display the character.
   bool ShowUtf8;  // -b
   unsigned long Utf8Value; // -b Value - note stored as translated utf-8 number.
   // Similar to Show Decimal and ShowUtf8 except accepts a range of decimal
   // numbers as input. Output is a table of utf-8 transated
   // representations.
   bool ShowRange; // -r
   unsigned long RangeStart; // -r X
   unsigned long RangeEnd; // -r x..Y
   // Output only the utf-8 file header characters 0xEF,0xBB,0xBF and exit
   bool ShowHeader; // -h
   bool Error;
}; 

struct OptionArgs NewOptionArgs(void);

struct OptionArgs ParseArguments( int, char**);

void _ParseRange(char *, struct OptionArgs *);

#endif