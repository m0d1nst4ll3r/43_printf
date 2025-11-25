# 43\_printf

## Progress

Floats will take too much time, turning in without them and will work on them separately.

Remaining:

- Add c (easy)
- Add s (easy)
- Add % (easy)
- Conv functions for diuxX (and p) done
- Just finish sub-funcs for printing width etc...
	- Width spaces (same for before/after, just condition the call)
	- Sign | DONE
	- Zero (either width or prec)
	- Then finish funcs for diuxX
- Conv function for o TBD
	- Add o after, reuses work for diuxX

## Steps

### 0. Understand va\_arg

Apparently you're ok using va\_arg anywhere in your code as long as you're passing its address around, which we will since we'll be using a structure. Therefore, there's nothing much to understand beyond calling va\_start, va\_end, and then using va\_arg as needed.

Note: don't call va\_arg with types such as char or short, int is the smallest type you can recover with it.

### 1. Identify rules

There are 4 optional fields and 1 mandatory field, each in a specific order.

Flags come first (#0- +), then width (a numerical value), then precision (a . followed optionally by a numerical value), then length (hh, h, l, ll, L, j, z, t), then the mandatory conversion specifier.

Note: there are more flags than just those 5, this is a bonus for later.

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
		- u unsigned decimal
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
		- accepts flags, width works with this
		- # flag makes this print errno instead of strerror(errno)
			- errno's macro value is printed as string (like ENOENT) unless it is 0 (0 is printed)
	- %
		- prints %
		- no argument needed
		- flags are completely ignored (no warnings or errors, unlike all other conversions)

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
	- Option 1: Naive approach, write one by one without malloc (no buffer, no malloc)
		- This is a bad approach as calling write so much is slow and inefficient
		- Also not thread safe (not everything is printed at once) meaning if two threads call ft_printf at the same time, characters can be commingled
	- Option 2: Full buffer approach, malloc, write in malloc, print malloc'd string
		- In this approach you need to know well in advance how many chars will be in your entire string
		- After doing this, you still need to write your actual string, so you need to calculate twice
		- This requires parsing through arguments with va_arg twice, and doing conversions twice
		- I think this is annoying for no reason
		- At least, it's super thread safe
	- Option 3: Buffer approach with malloc but in chunks
		- Same as before but you write in chunks of BUFFER_SIZE size e.g 1000, all linked through a chained list
		- No need to know in advance, you will malloc by default a first chunk of 1000 and should you fill it, you malloc another
		- Only needs to calculate once but even for a super short string, you will always malloc 1000
		- One more malloc call for every 1000 bytes
		- Has to write each chunk separately, which is not thread safe, unless you concatenate all your strings into one big one
			- If you do that, that's a whole lot of copying for big strings = useless instructions, inefficient
	- Option 4: Buffer approach but without malloc, flushing the buffer if it's full
		- Statically allocated buffer (buf[BUFFER_SIZE]) with no mallocs whatsoever, when it's filled, it's written
		- No mallocs, which makes it way simpler, but not thread safe at all (even less than option 3)
	- Option 5: Static buffer followed by mallocs
		- Static buffer by default (up to BUFFER_SIZE bytes) which then switches to a malloc if BUFFER_SIZE is too small
		- Same problem as above, if we use a chained list we are not thread safe, if we concatenate everything into one big string we need to spend a lot of instructions on copying (very bad)
	- No matter which option we choose, there are upsides and downsides and there will be "extra" instructions
	- Writing one by one should always be avoided, but whether to write *everything* at once or not depends on which sacrifice you want to make
	- Writing everything at once means you have to either copy a lot (chained list approach), or calculate in advance and re-calculate after (double parse approach)
		- If you go for the copy approach, you can set a reasonably big buffer (e.g 1k) so that you should only copy in extremely rare cases where you have to print a humongous line
		- If you go for the double parse approach, you also waste processing power, but at least you don't have to copy anything (I think copying is one of the slowest instructions)
	- Writing in chunks is the simplest approach but might cause problems with multi-threading
		- The simplest implementation for this approach is to have a fixed size buffer and just write when it's full
		- Another possible implementation is to have a chained list and write each chunk in a chain at the end
		- The difference will be that the 2nd one needs much less time between each write while the 1st one has to do some processing between each write
		- But the 2nd one requires mallocs, which is annoying
- The best options to me seem to be
	1. Double parse approach (malloc one big buffer, then write into it)
		- Advantages
			- Writes once, not a very hard approach
		- Disadvantages
			- Gotta parse and process twice (using the same code)
			- Uses malloc, but only once, which is ok
	2. Chained list approach (one malloc every BUFFER\_SIZE bytes)
		- Advantages
			- Can also write once, but there will be copying involved
			- Only has to parse once
		- Disadvantages
			- Uses multiple mallocs, annoying
			- Copying feels really bad
	3. Single static buffer approach (no mallocs at all)
		- Advantages
			- No mallocs at all
			- Extremely simple concept
		- Disadvantages
			- Does multiple writes (one every BUFFER_SIZE)

- How to convert?
	- Converting is sorta annoying because due to field width, you need information obtained from converting values before you can print them
	- You either need to process the conversion twice (once to know how many bytes in advance, once to write the result)
	- Or you need to store the results of your first conversion somewhere
		- This involves using malloc
		- OR... using a fixed size array
			- The only conversion that has a potentially infinite print is s
			- All other conversions have to have a max size, or a size given by flags (like . for float)
			- For s conversions, strlen is needed (double parse), for all the rest, we can use a static array
			- e.g for d, the static array's max size is 12 (INT_MIN)
			- for x, the max size is 8 + 1 (for sign) + 2 (for 0x)
			- for ld it will be more, etc...
	- For every conversion, the way to do the width can be different
		- This means it might be smarter to simply handle the logic in the conversion function itself rather than do it before

- How to handle length?
	- One approach is to store any value in the biggest container possible e.g hhd, hd, d, ld, lld will all be contained in a long anyway (ps: what's ll if long long isn't a thing?)
		- You will still need to call va_arg with a different type and/or cast that type (since va_arg's smallest type is int anyway)
	- Another approach is to have entirely different functions for different lengths (e.g 5 functions (or 4?) for d: hhd hd d ld lld)
	- Best approach seems to be #1

### 3. Design functions to verify and handle the rules

Done

### 4. Design the main program (and decide on an implementation)

Done

Implementation is a fixed length buffer flushed when it's full (1k-8k size). This works much like printf.

### 5. Design the main conversion function

Done

### 6. Design each different conv function

Conv functions have steps:

1. Acquire the arg depending on length (static func)

2. Figure out how long the arg is for width and/or precision
	- Again there's 2 ways to do this, you have to convert but
		1. You can write the conversion somewhere. If you don't want to malloc you need a fixed length array, which won't work for s (though that's fine), and for floats (because of potentially infinite precision).
			- For floats, since you know the precision in advance, you can figure out the length, but you also need to know how many digits there are BEFORE the decimal point so you do need to convert.
		2. You can also not write the conversion anywhere and just do it a second time.
			- This works for floats with prec but is a bit wasteful.

### 7. On how to do floats

A float on 4 bytes works like this

seee eeee emmm mmmm mmmm mmmm mmmm mmmm

s is the sign (0 positive 1 negative)

e is the exponent (power of 2) going from -126 to 127 (take it as a unsigned char and substract 127)

m is the mantissa

a float is basically s * (2^e * (1 + m))

m is calculated this way: the first bit is 2^(-1) the second bit is 2^(-2) etc... up to 2^(-23)

E.g if the mantissa is 101 0000 0000 0000 0000 0101

m is equal to 2^(-1) + 2^(-3) + 2^(-21) + 2^(-23)

All of that is added to 1 then multiplied with 2^e (e between -126 and 127), then the sign is added

Note: turning in without floats for now, will add later.
