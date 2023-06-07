# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 16:55:52 by aziyani           #+#    #+#              #
#    Updated: 2023/06/06 16:58:22 by aziyani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

RM = rm -f

SRC = philo.c philo_utiles.c

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	$(RM)
fclean : clean
	$(RM) $(NAME)

re : fclean all