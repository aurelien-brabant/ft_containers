CASTORNO_PATH	:= test/castorno
CASTORNO		:= test/castorno/libcastorno.a
TARGET_FT	:= ft
TEST_MAKE	:= test.Makefile

all: castorno-check-update
	@make -s -C $(CASTORNO_PATH)
	@make -s -f $(TEST_MAKE) FT_CONTAINER=std
	@make -s -f $(TEST_MAKE) FT_CONTAINER=ft

clean:
	@make clean -s -f $(TEST_MAKE) FT_CONTAINER=std
	@make clean -s -f $(TEST_MAKE) FT_CONTAINER=ft

fclean:
	@make fclean -s -f $(TEST_MAKE) FT_CONTAINER=std
	@make fclean -s -f $(TEST_MAKE) FT_CONTAINER=ft
	@make fclean -s -C $(CASTORNO_PATH)

re: fclean all

.PHONY: all clean fclean re castorno-check-update

$(CASTORNO_PATH):
	@git clone https://github.com/aurelien-brabant/castorno $(CASTORNO_PATH)

$(CASTORNO): $(CASTORNO_PATH)
	@make re -C $(CASTORNO_PATH)

castorno-check-update: $(CASTORNO_PATH)
	@printf "Castorno: checking for updates...\n"
	@cd $(CASTORNO_PATH) && git pull origin HEAD
