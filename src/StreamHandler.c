#include <unistd.h>
#include <stdio.h>
#include "StreamHandler.h"
#include "utf8Util.h"
#include "getutf8.h"
 
bool TestForPipe(void)
{
    if (isatty (STDIN_FILENO))
        return false; // not a pipe input.
    else
        return true; // is a pipe input
} // TestForPipe

void ProcessStream(void)
{
    char c;
    char KeepReading = 1;
    while (KeepReading) 
    {
        c = getchar(); // Read a character

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF) // || c == '\n') 
        {
            printf("\n");
            KeepReading = 0;
        } else {
            // unsigned long cul = DecToUtf8((unsigned long)c);
            ShowChar(DecToUtf8((unsigned long)c));
            //printf("%c", c);
        }
    } //while
}