CASTORNO_PATH	:= test/castorno
CASTORNO		:= test/castorno/libcastorno.a
TARGET_FT	:= ft
TEST_MAKE	:= test.Makefile

all: $(TARGET_FT)

$(TARGET_FT): $(CASTORNO)
	@printf "\033[1mSTD VERSION\033[0m\n"
	@make -s -f $(TEST_MAKE) FT_CONTAINER=std
	@printf "\033[1mFT VERSION\033[0m\n"
	@make re -s -f $(TEST_MAKE) FT_CONTAINER=ft

clean:
	@make clean -s -f $(TEST_MAKE) FT_CONTAINER=std
	@make clean -s -f $(TEST_MAKE) FT_CONTAINER=ft

fclean:
	@make fclean -s -f $(TEST_MAKE) FT_CONTAINER=std
	@make fclean -s -f $(TEST_MAKE) FT_CONTAINER=ft
	@make fclean -s -C $(CASTORNO_PATH)

re: fclean all
	@make re -s -C $(CASTORNO_PATH)

.PHONY: all clean fclean re

$(CASTORNO_PATH):
	git clone https://github.com/aurelien-brabant/castorno $(CASTORNO_PATH)

$(CASTORNO): $(CASTORNO_PATH)
	@make re -C $(CASTORNO_PATH)
