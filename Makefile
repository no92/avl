SRC		:= $(shell find src -name '*.c' -type f)
OBJ		:= $(SRC:.c=.o)
DEP		:= $(SRC:.c=.d)

all: avl

%.o: %.c
	@gcc -o $@ $< -c -MD -ggdb3 -D_GNU_SOURCE

avl: $(OBJ)
	@gcc -o $@ $^
	-@./avl

test:
	@valgrind --leak-check=yes ./avl

clean:
	@$(RM) $(OBJ) avl

-include $(DEP)
