CASTORNO_PATH	:= test/castorno
CASTORNO		:= test/castorno/libcastorno.a

CC			:= clang++
CPP_FLAGS	:= -g -Wall -Wextra -Werror -I$(CASTORNO_PATH) -I. -DTEST_VECTOR="ft::vector"
LD			:= $(CC)
LD_FLAGS	:= -L$(CASTORNO_PATH) -lcastorno
RM			:= rm -rf

HEADERS		:= vector.hpp map.hpp stack.hpp iterator.hpp
SRCS		:= test/tests.cpp $(wildcard test/*/*test.cpp)
TARGET		:= tester

OBJS		:= $(SRCS:%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(CASTORNO) $(OBJS)
	@$(LD) -o $(TARGET) $(OBJS) $(LD_FLAGS)
	@printf "LD\t$(TARGET)\n"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(TARGET)

re: fclean all

$(CASTORNO_PATH):
	git clone https://github.com/aurelien-brabant/castorno $(CASTORNO_PATH)

$(CASTORNO): $(CASTORNO_PATH)
	@make re -C $(CASTORNO_PATH)

%.o: %.cpp $(HEADERS)
	@$(CC) $(CPP_FLAGS) -c $< -o $@
	@printf "CC\t$<\n"
