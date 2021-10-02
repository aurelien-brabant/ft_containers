CASTORNO_PATH	:= test/castorno
CASTORNO		:= test/castorno/libcastorno.a

CC			:= clang++
CPP_FLAGS	:= -g -Wall -Wextra -Werror -I$(CASTORNO_PATH)/include -I./src -DFT_CONTAINER=$(FT_CONTAINER) -std=c++98
LD			:= $(CC)
LD_FLAGS	:= -L$(CASTORNO_PATH) -lcastorno
RM			:= rm -rf

HEADERS		:= $(addprefix ./src/, vector.hpp map.hpp stack.hpp iterator.hpp)
SRCS		:= test/tests.cpp $(wildcard test/*/*test.cpp)


OBJ_DIR     := .obj/$(FT_CONTAINER)
OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: $(FT_CONTAINER)

$(FT_CONTAINER): $(OBJ_DIR) $(OBJS) $(CASTORNO)
	@$(LD) -o $(FT_CONTAINER) $(OBJS) $(LD_FLAGS)
	@printf "LD\t$(FT_CONTAINER)\n"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(FT_CONTAINER)

re: fclean all

ifeq ($(FT_CONTAINER), std)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CPP_FLAGS) -c $< -o $@
	@printf "CC\t$(notdir $<)\n"
endif

ifeq ($(FT_CONTAINER), ft)
$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CPP_FLAGS) -c $< -o $@
	@printf "CC\t$(notdir $<)\n"
endif

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
