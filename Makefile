#------------------------------------------PROJECT
NAME		=	ft_containers

FLAGS		=	-Wall -Wextra -Werror -std=c++98
INCLUDES	=	-I ./Sources/

VPATH		=	./Sources/	\
				./Sources/Iterators

#------------------------------------------FILES
SRCS_NAME	=	main.cpp
OBJS_NAME	=	$(SRCS_NAME:.c=.o)

#------------------------------------------RULES

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJS_NAME)
			@c++ $(FLAGS) $(OBJS_NAME) -o $(NAME)

$(OBJS_NAME): $(SRCS_NAME)
			@c++ $(FLAGS) $(INCLUDES) -c $(SRCS_NAME)