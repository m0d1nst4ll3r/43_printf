/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:58:43 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 14:33:24 by rapohlen         ###   ########.fr       */
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
# define FTP_CONV	"diouxXeEfFgGaAcspnm%"

# include <stdarg.h>
# include <unistd.h>

/*	Program steps:
* 
* 0. Note on buffer management
* 	Throughout execution, we will write to the buffer constantly.
* 	Whenever said buffer is full, we flush it (print everything).
*	This is handled by its own function.
* 1. Copy string into buf until encountering a %
* 2. At %, call flag, width, prec, length and conv-reading func
* 	This fills flags, width, prec, len and conv values of the struct
* 3. Then, use said values to call the correct conversion func
* 	Incompatible flags are ignored (with each other or with conv)
* 	Incompatible len is ignored
* 	Invalid conv is the only event in which we skip conversion
* 	(in that case we simply print the % and continue parsing)
* 4. The conversion func will decide on what to print (add to buf)
* 	It will then advance the index & return to the parsing (step 1)
* 
*/


// flags contains all flags (in bitwise)
// width is atoi'd width (or 0 if empty)
// prec is atoi'd precision (or -1 if empty)
// len is the length modifier in string format
// conv is the conversion specifier in char format
// buf is our fixed length array buffer
//	it will be flushed (printed) when full
// buf_i is the index used with buf
// str_i is the index used with the string received in arg
// conv_i is the index used during conversion
// tot_i is the total amount of chars printed thus far
typedef struct s_printf
{
	int			flags;
	int			width;
	int			prec;
	char 		*len;
	char		conv;
	int			conv_i;

	const char	*s;
	va_list		ap;
	char		buf[FTP_BSIZE];
	int			buf_i;
	int			str_i;
	int			tot_i;
}t_printf;

// utils
int		ft_memcmp(const void *, const void *, size_t);
char	*ft_strchr(const char *s, int c);
int		printf_atoi(t_printf *d, const char *s);

// buffer
void	flush_buf(t_printf *d);
void	write_buf(t_printf *d, char c);

// flags
void	get_flags(t_printf *d);
void	get_width(t_printf *d);
void	get_prec(t_printf *d);
void	get_len(t_printf *d);

// conv
int		prepare_conv(t_printf *d);
void	process_conv(t_printf *d);

int	ft_printf(const char *s, ...);

#endif
