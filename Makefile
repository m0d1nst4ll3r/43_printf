# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/11/18 18:49:16 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
AR		= ar rcs
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf.c \
		  flags.c \
		  convert.c \
		  convert_di.c \
		  utils.c \
		  buffer.c \
		  utils.c \
		  utils_libft.c \
		  conv_utils.c

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
