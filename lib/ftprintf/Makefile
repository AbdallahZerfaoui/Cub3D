# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 18:07:20 by auplisas          #+#    #+#              #
#    Updated: 2024/11/16 03:20:36 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_printf.c \
					ft_calloc.c \
					ft_print_hex.c \
					ft_print_integer.c \
					ft_print_long_integer.c \
					ft_print_pointer.c \
					ft_putchar.c \
					ft_putstr.c \

OBJS			= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= libftprintf.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus