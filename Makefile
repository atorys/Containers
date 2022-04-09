#------------------------------------------PROJECT
NAME		=	ft_containers

FLAGS		=	-Wall -Wextra -Werror -std=c++98
INCLUDES	=	-I ./Sources/

VPATH		=	./Sources/			\
				./Sources/Iterator	\
				./Sources/Tree		\
				./Sources/Utils		\
				./Tests/

HEADERS		=	tree.hpp	\
				tree_traits.hpp \
				tree_node.hpp \
				map.hpp \
				set.hpp \
				vector.hpp \
				stack.hpp \
				iterator.hpp \
				iterator_category.hpp \
				iterator_distance.hpp \
				random_access_iterator.hpp \
				reverse_iterator.hpp \
				tree_iterator.hpp \
				copy.hpp \
				enable_if.hpp \
				equal.hpp \
				is_integral.hpp \
				lexicographical_compare.hpp \
				pair.hpp \
				utility.hpp \

#------------------------------------------FILES
SRCS_NAME	=	Tests/test_ft.cpp
SRCS_NAME2	=	Tests/test_std.cpp

OBJS_NAME	=	$(SRCS_NAME:.cpp=.o)
OBJS_NAME2	=	$(SRCS_NAME2:.cpp=.o)

#------------------------------------------RULES

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJS_NAME)
			c++ $(FLAGS) $(OBJS_NAME) -o $@
			@#rm -rf $(OBJS_NAME)



diff:		$(NAME) std_containers
			@sh check_diff.sh
			@rm -rf std

std_containers:		$(OBJS_NAME2)
					c++ $(FLAGS) $(OBJS_NAME2) -o $@
					@rm -rf $(OBJS_NAME2)

$(OBJS_NAME):	$(SRCS_NAME) $(HEADERS)
				@c++ $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_NAME2):	$(SRCS_NAME2) $(HEADERS)
				@c++ $(FLAGS) -c $< -o $@

clean	:
			@rm -rf $(OBJS_NAME)
			@rm -rf $(OBJS2_NAME)

fclean	:	clean
			@rm -f $(NAME)
			@rm -f std_containers
			@rm -f diff_logs

re		:	fclean all