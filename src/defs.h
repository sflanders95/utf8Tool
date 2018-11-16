#define ADDDEFS_HERE

#ifndef DEFS_H
#define DEFS_H
char *Usage( void );
typedef enum {false, true} bool;

// Unsafe str Right macro
#define right(str,n) (strlen(str)>n ? str+n : str)

#define _SHOWDEBUG 0 // use for extra printf's output


#endif