CASTORNO_PATH	:= test/castorno
CASTORNO		:= test/castorno/libcastorno.a

CC				:= clang++
FSAN_FLAGS  	:= -fsanitize=address -fno-omit-frame-pointer
CPP_FLAGS		:= -std=c++98 -Wall -Wextra -Werror -I$(CASTORNO_PATH)/include -I./src -DFT_CONTAINER=$(FT_CONTAINER)
LD				:= $(CC)
LD_FLAGS		:= -L$(CASTORNO_PATH) -lcastorno
RM				:= rm -rf

HEADERS			:= $(wildcard src/*.hpp)
SRCS			:= test/tests.cpp $(wildcard test/*/*test.cpp)

OBJ_DIR     	:= .obj/$(FT_CONTAINER)
OBJS			:= $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: prebuild $(FT_CONTAINER)
.PHONY: all

$(FT_CONTAINER): $(OBJ_DIR) $(OBJS) $(CASTORNO)
	@$(LD) -o $(FT_CONTAINER) $(OBJS) $(LD_FLAGS)
	@printf "\033[1;34mLD\033[0m\t$(FT_CONTAINER)\n"

prebuild:
	@printf "\n\033[1;35m*----- Build infos -----*\n\033[0m"
	@printf "Compiler\t\t$(CC)\nCPP flags\t\t$(CPP_FLAGS)\nLD flags\t\t$(LD_FLAGS)\n"
	@printf "\033[1;35m*-----------------------*\n\033[0m\n"
.PHONY: prebuild

clean:
	@$(RM) $(OBJS)
.PHONY: clean

fclean: clean
	@$(RM) $(FT_CONTAINER)
.PHONY: fclean

re: fclean all
.PHONY: re

ifeq ($(FT_CONTAINER), std)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CPP_FLAGS) -c $< -o $@
	printf '\033[1;33mCC\033[0m\t$@\n'
endif

ifeq ($(FT_CONTAINER), ft)
$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CPP_FLAGS) -c -g3 $< -o $@
	printf '\033[1;34mCC\033[0m\t$@\n'
endif

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
