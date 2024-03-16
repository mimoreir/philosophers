# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mimoreir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 09:19:32 by mimoreir          #+#    #+#              #
#    Updated: 2022/12/05 09:19:34 by mimoreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= clang
CFLAGS	= -Wall -Werror -Wextra -fsanitize=thread
RM		= rm -f
AR		= ar rcs

SRCS	= \
	main.c utils.c init.c free.c run.c routine.c run_utils.c

OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(SRCS) -o $(NAME)

debug:
	$(CC) -g -pthread $(SRCS) -o $(NAME)
	gdb -args philo 4 200 200 200

mem:
	valgrind -s --leak-check=full ./philo 2 410 200 200 2

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
