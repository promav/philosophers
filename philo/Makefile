NAME = philo

SRCS = src/aux.c src/init.c src/philosophers.c src/actions.c src/printmessage.c
OBJS = $(SRCS:src/%.c=obj/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude

all: obj $(NAME)

obj:
	@mkdir -p obj

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $@  # Use the compiler to link the object files into an executable
	@echo "make all correct"

$(OBJS): obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUSOBJS)
	@$(CC) $(BONUSOBJS) -o $(NAME)
	@echo "make bonus correct"

$(BONUSOBJS): obj/%.o: bonus/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@echo "make clean correct"

fclean: clean
	@rm -rf $(NAME)
	@echo "make fclean correct"

re: fclean all
	@echo "make re correct"

.PHONY: all clean fclean re bonus

