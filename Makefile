NAME = philo

SRCS = philo.c ft_isdigit.c ft_atoi.c free_and_exit.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -rf



${NAME}: 	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all :	${NAME} 

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(TARGET)

re :	fclean all		


