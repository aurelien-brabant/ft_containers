CC			:= clang++
CPP_FLAGS	:= -Wall -Wextra -Werror
LD			:= $(CC)
RM			:= rm -rf

HEADERS		:= vector.hpp map.hpp stack.hpp
SRCS		:= main.cpp
TARGET		:= demo

OBJS		:= $(SRCS:%.cpp=%.o)

$(TARGET): $(HEADERS) $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean

%.o: %.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@
