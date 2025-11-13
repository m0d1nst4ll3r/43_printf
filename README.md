# 43\_printf

## Steps

### 0. Understand va\_arg

### 1. Identify rules

There are 4 optional fields and 1 mandatory field, each in a specific order.
Flags come first (#0- +), then width (a numerical value), then precision (a . followed optionally by a numerical value), then length (hh, h, l, ll, L, j, z, t), then the mandatory conversion specifier.

1. Flags characters
	- Order is irrelevant, the 5 flags can come in any order and are all technically compatible with any conversion. However, the compiler will throw warnings (or errors with -Werror) if you use a conversion specifier with flags that aren´t meant to be used with it ("undefined behavior").
	- In our case, we can tolerate incompatible flags - they just won't have any effect (like compiling with the warnings anyway).
	- The - flag overrides the 0 flag, and if both are used together again a warning is thrown. This case isn't "undefined behavior" and also works if you compile anyway. We can also just tolerate and ignore.
	- The + flag overrides the ' ' flag, same exact as above. We can just tolerate it.
	- The 0 and - flags act on the width value, which is still optional. In case of missing width value, I have no fucking clue what happens, fuck me.
	- #
		- alternate print
		- works with o
			- non-zero result has 0 prepended
		- works with x, X
			- non-zero result has 0x or 0X prepended
		- works with a, A, e, E, f, F, g, G
			- result always has a decimal point even if no digits follow
			- for g and G, trailing zeros are not removed
	- 0
		- causes field width value to add zeroes instead of spaces
			- additionally, those zeroes are added right before the number itself e.g in case of preceding 0x or -
		- default is 1
		- if given precision is 0 and the number is 0, the output is empty
		- works with d, i, o, u, x, X, a, A, e, E, f, F, g, G
		- overridden by - flag
		- if a precision is given with d, i, o, u, x, X, the 0 flag is ignored
	- -
		- causes field width value to add spaces to the right instead of to the left (?)
		- works with everything
		- overrides 0 flag
	- ' '
		- blank before a positive number from a signed conversion
		- works with d, i, a, A, e, E, f, F, g, G (?)
		- also works with s (prints one space instead of an empty string)
		- overriden by + flag
	- +
		- sign (+ or -) before a signed conversion
		- works with d, i, a, A, e, E, f, F, g, G (?)
		- overrides space flag
2. Width
	- This always comes before the length modifier and after the flags
		- 0 and - flags act on the width value, therefore the presence of a 0 flag means you can't add any space padding (- overrides 0)
	- Optional decimal digit string (with nonzero first digit)
	- Adds spaces to the left to pad strings with less bytes than the value
3. Precision
		- default is 6 if no . is present
		- default is 0 if . is present but decimal digit is missing
		- works with d, i, o, u, x, X (min number of digits to appear) (?)
		- works with a, A, e, E, f, F (number of digits to appear after radix character)
		- works with g, G (max number of significant digits) (?)
		- works with s (max number of characters to be printed) (?)
4. Length
	- Order: the length modifier is always right before the conversion specifier
	- hh
		- signed or unsigned char instead of int or unsigned int
		- works with d, i, o, u, x, X, n
	- h
		- short or unsigned short
		- works with d, i, o, u, x, X, n
	- l
		- long or unsigned long
		- works with d, i, o, u, x, X, n
		- works with c (wint_t arg converted to multibyte with wcrtomb, then written)
		- works with s (const wchar_t * same as above)
	- ll
		- long long or unsigned long long
		- works with d, i, o, u, x, X, n
	- L
		- long double (Ld)
		- works with a, A, e, E, f, F, g, G
	- j
		- intmax_t or uintmax_t types (?)
		- works with d, i, o, u, x, X, n
	- z
		- size_t or ssize_t
		- works with d, i, o, u, x, X, n
	- t
		- ptrdiff_t (?)
		- works with d, i, o, u, x, X, n
5. Conversions
	- d, i
		- int, easy
	- o, u, x, X
		- unsigned int converted to a different base
		- o unsigned octal
		- u unsigned decimal (what's the point?)
		- x unsigned hexa with abcdef
		- X unsigned hexa with ABCDEF
	- e, E
		- double (or float, long double, whatever)
		- exponent display, format [-]d.ddde±dd
		- default 6 precision (unless given with . flag)
		- E just makes the exponent letter uppercase (E)
	- f, F
		- double (float, etc...)
		- displayed normally ([-]ddd.ddd)
		- default 6 precision (unless given with . flag)
	- g, G
		- double (float, etc...)
		- does f or e depending on the value (or F or E)
			- e is used if the exponent is less than -4 or >= precision (otherwise, f)
			- trailing zeros are removed (?)
		- default precision is 6
		- a precision of 0 is counted as 1
	- a, A
		- double (float, etc...)
		- converted to hexadecimal style [-]0xh.hhhhp±d (p = exponent separator) (?)
		- A means 0X ABCDEF and P
		- more stuff, but idk, complicated (?)
	- c
		- int
		- converted to unsigned char, resulting character is written
		- with l, does multibyte (?)
	- s
		- const char *
		- prints chars
		- flag . works to limit amount of chars printed
			- in case of . flag, string might not be fully read (absence of null byte can be ok)
		- for l length, does multibyte (?)
	- p
		- void *
		- printed in hexa (as if %#lx) so 0xhhhh
	- n
		- the number of characters written so far is stored in the integer pointed to by the arg
		- supports no flags but can support length (sets the size in bytes of the int)
	- m
		- prints output of strerror(errno)
		- no argument needed
	- %
		- prints %
		- no argument needed

### 2. Design a structure that supports those rules


### 3. Design functions to verify and handle the rules


### 4. Design the main program (and decide on an implementation)


### 5. Design the main conversion function


### 6. Design each different conv function
