#------------------------------------------PROJECT
NAME		=	test

FLAGS		=	-Wall -Wextra -Werror -std=c++98
INCLUDES	=	-I ./Sources/

VPATH		=	./Sources/			\
				./Sources/Iterator	\
				./Sources/Tree		\
				./Sources/Utils		\
				./Tests/

#------------------------------------------FILES
SRCS_NAME	=	Tests/test_vector.cpp
#SRCS_NAME	=	main.cpp
#				test_map.cpp
OBJS_NAME	=	$(SRCS_NAME:.cpp=.o)

#------------------------------------------RULES

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJS_NAME)
			c++ $(FLAGS) $(OBJS_NAME) -o $@
			@rm -rf $(OBJS_NAME)

$(OBJS_NAME): $(SRCS_NAME)
			@c++ $(FLAGS) $(INCLUDES) -c $< -o $@

clean	:
			@rm -rf $(OBJS_NAME)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all