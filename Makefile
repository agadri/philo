# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:28:55 by adegadri          #+#    #+#              #
#    Updated: 2021/12/14 18:25:05 by adegadri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo

CC =	cc

DEL =	/bin/rm -f

SRCS =  philo.c \
		utils.c \
		time_to.c \
		init.c \
		if_time_to.c \
		check.c \
		print.c

OBJS    = ${SRCS:.c=.o}

CFLAGS    = -Wall -Werror -Wextra -g -fsanitize=thread

CC        = gcc

RM        = rm -f

all:    ${NAME}

$(NAME):	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lpthread 

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS}

fclean:        clean
			${RM} ${NAME}
	
re:	fclean all