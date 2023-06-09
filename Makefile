# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 16:55:52 by aziyani           #+#    #+#              #
#    Updated: 2023/06/09 21:18:06 by aziyani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC = philo.c checks.c routine.c

all : $(NAME)
$(NAME) : $(SRC)
	$(CC)  $(CFLAGS) $(SRC) -o $(NAME)

clean :
	$(RM)
fclean : clean
	$(RM) $(NAME)

re : fclean all