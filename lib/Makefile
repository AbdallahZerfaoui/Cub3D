# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 02:17:11 by macbook           #+#    #+#              #
#    Updated: 2025/02/09 17:27:51 by auplisas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = lib.a

GET_NEXT_LINE_DIR = ./get_next_line
GET_NEXT_LINE_SRCS = get_next_line.c get_next_line_utils.c
GET_NEXT_LINE_OBJS = $(addprefix $(GET_NEXT_LINE_DIR)/, $(GET_NEXT_LINE_SRCS:.c=.o))

LIBFT_DIR = ./libft
LIBFT_SRCS =	ft_putnbr_fd.c \
				ft_putendl_fd.c \
				ft_putstr_fd.c \
				ft_putchar_fd.c \
				ft_striteri.c \
				ft_memcpy.c \
				ft_itoa.c \
				ft_strlen.c \
				ft_strdup.c \
				ft_memcpy.c \
				ft_split.c \
				ft_atoi.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_memmove.c \
				ft_substr.c \
				ft_memset.c \
				ft_calloc.c \
				ft_strchr.c \
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strmapi.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \

LIBFT_OBJS = $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS:.c=.o))

OBJS = $(GET_NEXT_LINE_OBJS) ${LIBFT_OBJS}

OBJDIR = ./objs

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re