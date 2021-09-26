CASTORNO_PATH	:= test/castorno
CASTORNO		:= test/castorno/libcastorno.a

CC			:= clang++
CPP_FLAGS	:= -Wall -Wextra -Werror -I$(CASTORNO_PATH) -I./src -DFT_CONTAINER=$(FT_CONTAINER) -std=c++98
LD			:= $(CC)
LD_FLAGS	:= -L$(CASTORNO_PATH) -lcastorno
RM			:= rm -rf

HEADERS		:= $(addprefix ./src/, vector.hpp map.hpp stack.hpp iterator.hpp)
SRCS		:= test/tests.cpp $(wildcard test/*/*test.cpp)

OBJS		:= $(SRCS:%.cpp=%.o)

all: $(FT_CONTAINER)

$(FT_CONTAINER): $(CASTORNO) $(OBJS)
	@$(LD) -o $(FT_CONTAINER) $(OBJS) $(LD_FLAGS)
	@printf "LD\t$(FT_CONTAINER)\n"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(FT_CONTAINER)

re: fclean all

%.o: %.cpp $(HEADERS)
	@$(CC) $(CPP_FLAGS) -c $< -o $@
	@printf "CC\t$<\n"
