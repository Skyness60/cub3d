CC = cc

INCLUDES =	get_next_line.h

CFLAGS = -Wall -Wextra -Werror -I${INCLUDES}

NAME = libftgnl.a

FUNCGNL =	get_next_line.c
SRCS = ${FUNCGNL}

OBJS = ${SRCS:.c=.o} 

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		@ar -rsc ${NAME} ${OBJS}

all: 	${NAME}

clean:	
		@rm -f ${OBJS}

fclean:	clean
		@rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re bonus
