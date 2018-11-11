#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

char* ShowRange(long start, long end)
{
    char *tmpc = calloc(3, sizeof(char*));
    char *tmpd = calloc(8, sizeof(char*)); // number smaller than 7 chars... right?
    char *tmpx = calloc(5, sizeof(char*)); // hex is 5 chars: "\x##\0"
    // char *line =  calloc(30, sizeof(char*));
    // char *buf = calloc(sizeof(line) * (end-start), sizeof(char*)); 
    char *buf = calloc(20 * (end-start), sizeof(char*)); 
    for (int i = start; i <= end; i++)
    {
        unsigned long ul = (unsigned long)(i+4036862976);
        sprintf(tmpc, "%luc-", ul); // CHAR: already has '\0' at end
        sprintf(tmpd, "%lud-", ul);
        sprintf(tmpx, "%lux-", ul); // 65 dec is \x41
        strcat(buf, tmpc);
        strcat(buf, tmpd);
        strcat(buf, tmpx);
        sprintf(tmpx, "%lux\n", ul); // 65 dec is \x41
        strcat(buf, tmpx);
    }
    return buf;
}

/// <summary>
/// https://www.fileformat.info/info/unicode/utf8.htm
/// http://www.ietf.org/rfc/rfc3629.txt
/// </summary>
void DecToUtf8(unsigned long dec)
{

}

char* ShowChar(int dec)
{
    char *buf = calloc(2, sizeof(char*)); 
    sprintf(buf, "%c", dec);
    return buf;
}