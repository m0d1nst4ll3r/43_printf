/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:58:43 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/27 11:39:45 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FTP_BSIZE	8120
# define FTP_HASH	1
# define FTP_ZERO	2
# define FTP_DASH	4
# define FTP_SPCE	8
# define FTP_PLUS	16
# define FTP_LEN_HH	"hh"
# define FTP_LEN_H	"h"
# define FTP_LEN_L	"l"
# define FTP_LEN_LL	"ll"
# define FTP_LEN_LD	"L"
# define FTP_LEN_J	"j"
# define FTP_LEN_Z	"z"
# define FTP_LEN_T	"t"
// Currently handling [#+- 0]
// Not handling ['] (thousands grouping)
# define FTP_FLAGS	"#+- 0"
// Currently handling [diuboxXcsp%]
// Not handling [eEfFgGaAnm] (all floats, strerror, and printed)
// TBD: n is easy, m is ok, float is hell
// Obj: "diuboxXeEfFgGaAcspnm%"
# define FTP_CONV	"diuboxXcsp%"
# define FTP_HEX	"0123456789abcdef"
# define FTP_DEC	"0123456789"
# define FTP_OCT	"01234567"
# define FTP_BIN	"01"
# define FTP_NULL	"(null)"
# define FTP_NULLEN	6
# define FTP_NIL	"(nil)"
# define FTP_NILLEN	5
# define FTP_EMPTY	""
# define FTP_SPECX	"0x"
# define FTP_SPECB	"0b"
# define FTP_SPECO	"0"
// Arbitrary buffer size for number conversions (optimizing for single pass)
// Enough for theoretical 256 bit integer
# define CONV_BSIZE	100
/*
Old defines, had to remove because of norm
In retrospect without these defines using bitwise is bad
Using one int variable per flag would've been better
# define HAS_HASH(n)	(n & FTP_HASH)
# define HAS_ZERO(n)	(n & FTP_ZERO)
# define HAS_DASH(n)	(n & FTP_DASH)
# define HAS_SPACE(n)	(n & FTP_SPCE)
# define HAS_PLUS(n)	(n & FTP_PLUS)
# define HAS_SIGN(n)	(HAS_PLUS(n) || HAS_SPACE(n))
# define HAS_WIDTH(n)	!(HAS_ZERO(n) || HAS_DASH(n))
# define SIGN(v, n)		(v < 0 || HAS_SIGN(n))
*/

# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>

# include <stdio.h>

/*	Program steps:
*
* 0. Note on buffer management
* 	Throughout execution, we will constantly write to the buffer
* 	Whenever said buffer is full, we flush it (print everything)
* 1. Write into buf until encountering a %
* 2. At %, call flag, width, prec, length and conv-reading func
* 	This fills flags, width, prec, len and conv values of the struct
* 3. Then, use said values to call the correct conversion func
* 	Incompatible flags are ignored (with each other or with conv)
* 	Incompatible len is ignored
* 	Invalid conv is the only event in which we skip conversion
* 	(in that case we simply print the % and continue parsing)
* 4. The conversion func will decide on what to write into buf
* 	It will then advance the index & return to parsing (step 1)
*
*	Struct:
*
*	flags		contains all flags (in bitwise)
*	width		atoi'd field width (or 0 if empty)
*	prec		atoi'd precision (or -1 if empty)
*	len			length modifier in string format
*	conv		conversion specifier in char format
*	conv_i		index during conversion
*	conv_buf	buffer used for conversion
*	conv_sign	sign/special character during conversion
*	arg_len		(converted) arg length for conversion
*
*	s			format string passed to ft_printf
*	ap			arg pointer
*	buf			fixed length array buffer - printed when full
*	buf_i		index of buf
*	str_i		index of arg string
*	tot_i		number of bytes printed total
*/
typedef struct s_printf
{
	int			flags;
	int			width;
	int			prec;
	char		*len;
	char		conv;
	int			conv_i;
	char		conv_buf[CONV_BSIZE];
	char		*conv_sign;
	int			arg_len;

	const char	*s;
	va_list		ap;
	char		buf[FTP_BSIZE];
	int			buf_i;
	int			str_i;
	int			tot_i;
}t_printf;

// utils
// libft - taken from libft
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *s);
void	ft_strrev(char *s);
int		ft_abs(int n);
void	ft_strupper(char *s);
// print - print helpers during conversion
void	print_char(t_printf *d, char c, int n);
void	print_string(t_printf *d, char *buf);
void	print_nstring(t_printf *d, char *buf, int n);
void	print_upper(t_printf *d, char *buf);
void	print_sign(t_printf *d, intmax_t arg);
void	print_width(t_printf *d);
void	print_zero(t_printf *d);
void	print_prec(t_printf *d);
// printf - libft mods for printf
int		printf_atoi(t_printf *d, const char *s);
int		printf_itoa(intmax_t n, char *buf);
int		printf_tobase(uintmax_t n, char *buf, char *base);
void	get_sign(t_printf *d, intmax_t arg);

// buffer
void	flush_buf(t_printf *d);
void	write_buf(t_printf *d, char c);

// flags
void	get_flags(t_printf *d);
void	get_width(t_printf *d);
void	get_prec(t_printf *d);
void	get_len(t_printf *d);

// convert
int		prepare_conv(t_printf *d);
void	process_conv(t_printf *d);

// conversion functions
void	convert_di(t_printf *d);
void	convert_c(t_printf *d);
void	convert_s(t_printf *d);
void	convert_boux(t_printf *d);
void	convert_p(t_printf *d);

int		ft_printf(const char *s, ...);

#endif
