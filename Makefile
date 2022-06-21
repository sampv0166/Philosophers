NAME = philo

SRCS = philo.c ft_isdigit.c ft_atoi.c ft_err.c print_msg.c routine.c time_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc -ggdb

CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -rf

${NAME}: 	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all :	${NAME} 

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re :	fclean all		


