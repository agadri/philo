# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:28:55 by adegadri          #+#    #+#              #
#    Updated: 2021/12/06 15:49:54 by adegadri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo

CC =	cc

DEL =	/bin/rm -f

SRCS =  philo.c \
		utils.c \
		time_to.c

OBJS    = ${SRCS:.c=.o}

CFLAGS    = -Wall -Werror -Wextra -g

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