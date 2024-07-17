NAME = philo

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RESET := \033[0m

BUILD_DIR = build

SRCS_DIR = src

SRCS = $(addprefix $(SRCS_DIR)/, main.c ft_atoi.c init_data.c init_philo.c \
is_valid_args.c create_threads.c monitoring.c philo_routine.c \
get_current_time.c print_msg.c dead_or_full.c ft_putendl_fd.c \
clean_up.c ft_usleep.c)

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.o)

HEADER = include

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(HEADER)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)$(NAME) created ✅$(RESET)"

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling ..."

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(NAME)
	@echo "$(RED)$(NAME) deleted.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
