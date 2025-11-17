# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/11/17 15:57:06 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
AR		= ar rcs
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf.c

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
