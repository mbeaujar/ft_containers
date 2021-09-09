NAME_FT = ft
NAME_STD = std
INC = containers
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
CC = clang++


SRCS = main.cpp

OBJS_FT = ft.o 

OBJS_STD = std.o

all : $(NAME_FT) $(NAME_STD)

$(OBJS_FT) : main.cpp
	@$(CC) $(CFLAGS) -I$(INC) -D FT=1 -c $< -o $@

$(NAME_FT) : $(OBJS_FT)
	@$(CC) $(OBJS_FT) -o $@

$(OBJS_STD) : main.cpp
	@$(CC) $(CFLAGS) -I$(INC) -D FT=1 -c $< -o $@

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




