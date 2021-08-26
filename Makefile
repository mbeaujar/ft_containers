NAME = ft_containers
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
CC = clang++

PATH_VECTOR= containers/vector
SRCS_VECTOR =  containers/vector/main.cpp containers/vector/std.cpp
OBJS_VECTOR = $(SRCS_VECTOR:.cpp=.o)

PATH_STACK= containers/stack
SRCS_STACK= containers/stack/main.cpp containers/stack/std.cpp
OBJS_STACK = $(SRCS_STACK:.cpp=.o)

%.o : %.cpp
	@$(CC) $(CFLAGS) $< -c -o $@

all: $(NAME)

$(NAME): vector stack

vector: $(OBJS_VECTOR)
	@-$(CC) $(CFLAGS) $(PATH_VECTOR)/main.o -o $(PATH_VECTOR)/main
	@-$(CC) $(CFLAGS) $(PATH_VECTOR)/std.o -o $(PATH_VECTOR)/std
	@-./$(PATH_VECTOR)/main > $(PATH_VECTOR)/output
	@-./$(PATH_VECTOR)/std  > $(PATH_VECTOR)/output_expected
	@-diff $(PATH_VECTOR)/output $(PATH_VECTOR)/output_expected

stack: $(OBJS_STACK)
	@-$(CC) $(CFLAGS) $(PATH_STACK)/main.o -o $(PATH_STACK)/main
	@-$(CC) $(CFLAGS) $(PATH_STACK)/std.o -o $(PATH_STACK)/std
	@-./$(PATH_STACK)/main > $(PATH_STACK)/output
	@-./$(PATH_STACK)/std  > $(PATH_STACK)/output_expected
	@-diff $(PATH_STACK)/output $(PATH_STACK)/output_expected


clean :
	@-$(RM) $(OBJS_VECTOR) $(PATH_VECTOR)/main $(PATH_VECTOR)/std $(PATH_VECTOR)/output $(PATH_VECTOR)/output_expected
	@-$(RM) $(OBJS_STACK) $(PATH_STACK)/main $(PATH_STACK)/std $(PATH_STACK)/output $(PATH_STACK)/output_expected


