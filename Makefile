NAME = ft_containers
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
CC = clang++

PATH_VECTOR= containers/vector
SRCS_VECTOR =  containers/vector/main.cpp containers/vector/std.cpp
OBJS_VECTOR = $(SRCS_VECTOR:.cpp=.o)

%.o : %.cpp
	@$(CC) $(CFLAGS) $< -c -o $@

all: $(NAME)

$(NAME): vector

vector: $(OBJS_VECTOR)
	@$(CC) $(CFLAGS) $(PATH_VECTOR)/main.o -o $(PATH_VECTOR)/main
	@$(CC) $(CFLAGS) $(PATH_VECTOR)/std.o -o $(PATH_VECTOR)/std
	@./$(PATH_VECTOR)/main > $(PATH_VECTOR)/output
	@./$(PATH_VECTOR)/std  > $(PATH_VECTOR)/output_expected
	@diff $(PATH_VECTOR)/output $(PATH_VECTOR)/output_expected


clean :
	$(RM) $(OBJS_VECTOR) $(PATH_VECTOR)/main $(PATH_VECTOR)/std $(PATH_VECTOR)/output $(PATH_VECTOR)/output_expected


