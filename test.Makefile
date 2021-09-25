CASTORNO_PATH	:= test/castorno
CASTORNO		:= test/castorno/libcastorno.a

CC			:= clang++
CPP_FLAGS	:= -g -Wall -Wextra -Werror -I$(CASTORNO_PATH) -I. -DFT_CONTAINER=$(FT_CONTAINER)
LD			:= $(CC)
LD_FLAGS	:= -L$(CASTORNO_PATH) -lcastorno
RM			:= rm -rf

HEADERS		:= vector.hpp map.hpp stack.hpp iterator.hpp
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

$(CASTORNO_PATH):
	git clone https://github.com/aurelien-brabant/castorno $(CASTORNO_PATH)

$(CASTORNO): $(CASTORNO_PATH)
	@make re -C $(CASTORNO_PATH)

%.o: %.cpp $(HEADERS)
	@$(CC) $(CPP_FLAGS) -c $< -o $@
	@printf "CC\t$<\n"
