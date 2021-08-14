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

re : fclean all