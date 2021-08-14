NAME = a.out
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
CC = clang++

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp	
	$(CC) $(CFLAGS) $< -c -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

push :
	git push git@github.com:mbeaujar/ft_containers.git

copy : 
	@cat main.cpp | sed 's/ft/std/g' > std.cpp

test : copy
	@clang++ main.cpp -o test1 && ./test1 > a
	@clang++ std.cpp -o test2 && ./test2 > b
	@-rm -rf test1 test2
	@-diff a b 
	@-rm -rf a b

re : fclean all