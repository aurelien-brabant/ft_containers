CC			:= clang++
CPP_FLAGS	:= -g -Wall -Wextra -Werror
LD			:= $(CC)
RM			:= rm -rf

HEADERS		:= vector.hpp map.hpp stack.hpp iterator.hpp
SRCS		:= main.cpp
TARGET		:= demo

OBJS		:= $(SRCS:%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

%.o: %.cpp $(HEADERS)
	$(CC) $(CPP_FLAGS) -c $< -o $@
