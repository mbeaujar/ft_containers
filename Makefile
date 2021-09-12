NAME_FT = ft
NAME_STD = std
INC = containers
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
CC = clang++

INCLUDE = bidirectional_iterator.hpp \
	binary_search_trees.hpp \
	iterator.hpp \
	map.hpp \
	stack.hpp \
	utils.hpp \
	vector.hpp

HEADER = $(addprefix containers/, $(INCLUDE))

SRCS = main.cpp

OBJS_FT = ft.o 

OBJS_STD = std.o

all : $(NAME_FT) $(NAME_STD)

$(OBJS_FT) : $(SRCS) $(HEADER)
	@$(CC) $(CFLAGS) -I$(INC) -D FT=1 -c $< -o $@

$(NAME_FT) : $(OBJS_FT)
	@$(CC) $(OBJS_FT) -o $@

$(OBJS_STD) : $(SRCS) $(HEADER)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME_STD) : $(OBJS_STD)
	@$(CC) $(OBJS_STD) -o $@

comp : $(NAME_FT) $(NAME_STD)
	@-./ft > output_ft
	@-./std > output_std
	@-diff output_ft output_std

clean :
	@$(RM) $(OBJS_FT) $(OBJS_STD)
	@$(RM) output_ft output_std

fclean : clean
	@$(RM) $(NAME_FT) $(NAME_STD)

re : fclean all




