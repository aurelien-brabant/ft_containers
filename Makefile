TARGET_FT	:= ft
TEST_MAKE	:= test.Makefile

all: $(TARGET_FT)

$(TARGET_FT):
	make -f $(TEST_MAKE) FT_CONTAINER=std
	make re -f $(TEST_MAKE) FT_CONTAINER=ft

clean:
	make clean -f $(TEST_MAKE) FT_CONTAINER=std
	make clean -f $(TEST_MAKE) FT_CONTAINER=ft

fclean:
	make fclean -f $(TEST_MAKE) FT_CONTAINER=std
	make fclean -f $(TEST_MAKE) FT_CONTAINER=ft

re: fclean all
