# program name
NAME = philo

# srcs
SRCS = philo.c ft_isdigit.c ft_atoi.c ft_err.c print_msg.c routine.c time_utils.c routine2.c

# objects
OBJS = ${SRCS:.c=.o}

# compilor
CC = gcc -ggdb

# flags for the compilor
CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -rf

${NAME}: 	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

# rules

all :	${NAME} 

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re :	fclean all		


