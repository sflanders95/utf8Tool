### Setting a bit
Use the bitwise OR operator (|) to set a bit.<br/>
``` number |= 1UL << n; //where n is zero based array index ``` <br/>
That will set the nth bit of number. n should be zero, if you want to set the 1st bit and so on upto  n-1, if you want to set the nth bit.

 <small>*Use 1ULL if number is wider than unsigned long; promotion of 1UL << n doesn't happen until after evaluating 1UL << n where it's undefined behaviour to shift by more than the width of a long. The same applies to all the rest of the examples.*</small>

### Clearing a bit
Use the bitwise AND operator (&) to clear a bit.<br/>
``` number &= ~(1UL << n); ``` <br/>
That will clear the nth bit of number. You must invert the bit string with the bitwise NOT operator (~), then AND it.

### Toggling a bit
The XOR operator (^) can be used to toggle a bit.<br/>
``` number ^= 1UL << n; ``` <br/>
That will toggle the nth bit of number.

### Checking a bit
To check a bit, shift the number n to the right, then bitwise AND it: <br/>
``` bit = (number >> n) & 1U; ``` <br/>
That will put the value of the nth bit of number into the variable bit.

### Changing the nth bit to x
Setting the nth bit to either 1 or 0 can be achieved with the following on a 2's complement C++ implementation: <br/>
``` number ^= (-x ^ number) & (1UL << n); ``` <br/>
Bit n will be set if x is 1, and cleared if x is 0. If x has some other value, you get garbage.  x = !!x will booleanize it to 0 or 1.

[Source Stackoverflow](https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit)

### Plain Shifting:
``` C
// a = 5(00000101), b = 9(00001001) 
unsigned char a = 5, b = 9;  
a = a << 1;  // The result is 00001010  (10)
b = b << 1;  // The result is 00010010  (18)

// macro for 2^x
#define twoToPowerOf(exponent) 1 << exponent
// e.g.: twoToPowerOf(3) returns 8
// e.g.: twoToPowerOf(4) returns 16
```

### More Examples
``` C
unsigned int a = 60;	/* 60 = 0011 1100 */  
unsigned int b = 13;	/* 13 = 0000 1101 */
int c = 0;           
c = a & b;      /* 12  = 0000 1100 */ 
c = a | b;      /* 61  = 0011 1101 */
c = a ^ b;      /* 49  = 0011 0001 */
c = ~a;         /*-61  = 1100 0011 */
c = a << 2;     /* 240 = 1111 0000 */
c = a >> 2;     /* 15  = 0000 1111 */
```

# Links
 - [Hex Calculator]
 - [Hex Dec Oct Bin Converter]
 - [utf-8 Converter]
 - [utf-8 RFC]
 - [Bitwise Operations]


<!-- Link Definitions: -->
[Hex Calculator]: https://www.calculator.net/hex-calculator.html?number1=0800ffff&c2op=%2B&number2=27b0&calctype=op&x=50&y=28
[Hex Dec Oct Bin Converter]: http://calc.50x.eu
[utf-8 Converter]: http://www.ltg.ed.ac.uk/~richard/utf-8.cgi
[utf-8 RFC]: http://www.ietf.org/rfc/rfc3629.txt
[Bitwise Operations]: https://www.programiz.com/c-programming/bitwise-operators