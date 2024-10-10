NAME = philo

SRCS = src/aux.c src/init.c src/philosophers.c
OBJS = $(SRCS:src/%.c=obj/%.o)


CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude

all: obj $(NAME)

obj:
	@mkdir -p obj

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "make all correct"

$(OBJS): obj/%.o:src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUSOBJS)
	@ar rcs $(NAME) $^
	@echo "make bonus correct"

$(BONUSOBJS): obj/%.o:bonus/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@echo "make clean correct"

fclean: clean
	@rm -rf libft
	@echo "make fclean correct"

re: fclean all
	@echo "make re correct"

.PHONY: all clean flean re bonus
