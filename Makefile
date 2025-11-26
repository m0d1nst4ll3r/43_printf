# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/11/26 15:13:32 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
AR		= ar rcs
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf.c buffer.c flags.c \
		  convert.c convert_c.c convert_s.c convert_di.c convert_boux.c convert_p.c \
		  utils.c utils_print.c utils_libft.c utils_libft2.c

OBJS	= $(SRCS:.c=.o)

NAME	= libftprintf.a

all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $@ $^

bonus:		$(OBJS)
			$(AR) $(NAME) $^

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: clean fclean all
