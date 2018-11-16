#include <unistd.h>
#include <stdio.h>
 
int TestForPipe(void)
{
    if (isatty (STDIN_FILENO))
        return 0; // not a pipe input.
    else
        return 1; // is a pipe input
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
            printf("%c", c);
        }
    } //while
}