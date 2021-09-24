CC			:= clang++
CPP_FLAGS	:= -g -Wall -Wextra -Werror -Itest/cpptester -I.
LD			:= $(CC)
LD_FLAGS	:= -Ltest/cpptester -lcpptester
RM			:= rm -rf

HEADERS		:= vector.hpp map.hpp stack.hpp iterator.hpp
SRCS		:= test/tester.cpp
TARGET		:= demo

CPPTESTER_PATH	:= test/cpptester
CPPTESTER		:= test/cpptester/libcpptester.a

OBJS		:= $(SRCS:%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

tester: $(CPPTESTER) $(OBJS)
	$(LD) -o tester $(OBJS) $(LD_FLAGS)

$(CPPTESTER):
	make re -C $(CPPTESTER_PATH)

%.o: %.cpp $(HEADERS)
	$(CC) $(CPP_FLAGS) -c $< -o $@
