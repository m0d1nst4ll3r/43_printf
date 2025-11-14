# 43\_printf

## Steps

### 0. Understand va\_arg

### 1. Identify rules

There are 4 optional fields and 1 mandatory field, each in a specific order.
Flags come first (#0- +), then width (a numerical value), then precision (a . followed optionally by a numerical value), then length (hh, h, l, ll, L, j, z, t), then the mandatory conversion specifier.

1. Flag characters
	- Order is irrelevant, the 5 flags can come in any order and are all technically compatible with any conversion. However, the compiler will throw warnings (or errors with -Werror) if you use a conversion specifier with flags that aren´t meant to be used with it ("undefined behavior").
	- In our case, we can tolerate incompatible flags - they just won't have any effect (like compiling with the warnings anyway).
	- The - flag overrides the 0 flag, and if both are used together again a warning is thrown. This case isn't "undefined behavior" and also works if you compile anyway. We can also just tolerate and ignore.
	- The + flag overrides the ' ' flag, same exact as above. We can just tolerate it.
	- The 0 and - flags act on the width value, which is still optional. In case of missing width value, nothing happens (as if there was no flag).
	- Duplicate flags are allowed and don't throw any warnings or errors - they are just ignored.
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
		- works with d, i, o, u, x, X, a, A, e, E, f, F, g, G
		- overridden by - flag
		- if a precision is given with d, i, o, u, x, X, the 0 flag is ignored
			- it is not just ignored, but set to 0, meaning if a width is present, it is counted as normal width and not modified by 0 (a - flag would still throw a warning if the 0 is also present, even as a leading 0 to the width)
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
	- This always comes before precision and after the flags
		- 0 and - flags act on the width value, therefore the presence of a 0 flag means you can't add any space padding (- overrides 0)
	- Optional decimal digit string (with nonzero first digit, otherwise it could be a 0 flag)
		- Note that a nonzero first digit doesn't throw any warnings or errors. It just counts as a 0 flag if there weren't one already (duplicates don't cause any problems), and any subsequent 0 either counts as a 0 flag too (again, duplicates don't do anything) or are lost in an atoi...
	- Adds spaces to the left to pad strings with less bytes than the value
	- The *total* string length is counted for width (along with any + or - added, or 0x, etc...)
3. Precision
		- default is 6 if no . is present (for float conversions)
		- default is 0 if . is present but decimal digit is missing
		- works with d, i, o, u, x, X (min number of digits to appear)
			- seems to work exactly like the 0 flag, also the 0 flag is always counted as absent in this case
			- this does not work exactly like 0 in the case of #x, since precision does not care about any extra characters - it only care about numerical characters part of the number itself (so the leading 0x is not counted)
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

- Order
	1. Flag characters
	2. Field width
	3. Precision
	4. Length modifier
	5. Conversion specifier
- Duplicate flags are skipped and ignored
- If field width begins with 0's, they are counted as flags
- Precision number is optional (defaults to 0)
- Only one length modifier is accepted
- If a flag is incompatible with conversion, ignore
- If incompatible flags are together, ignore
- If length is incompatible with conversion, also ignore

- How to parse?
	- Option 1: print on the fly, when reaching % parse it, send it to a function, print the result
	- Option 2: write into a buffer, only print the buffer at the very end
	- 

### 3. Design functions to verify and handle the rules


### 4. Design the main program (and decide on an implementation)


### 5. Design the main conversion function


### 6. Design each different conv function
