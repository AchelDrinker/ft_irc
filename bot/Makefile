NAME = bot
SRCS = $(shell find . -name "*.cpp")
OBJ_PATH := ./objs
OBJS = $(SRCS:.cpp=.o)
OBJ := $(patsubst %,$(OBJ_PATH)%,$(OBJS))
FLAGS = -Wall -Wextra -Werror -std=c++98

GREEN = '\033[92m'
RED = '\033[91m'
NONE = '\033[3m'

all: $(NAME)

$(NAME): $(SRCS) $(OBJS)
	@mkdir objs
	@mv $(OBJS) objs
	@echo $(GREEN) "--Loading--" $(NONE)
	@sleep 0.2
	@c++ $(FLAGS) $(SRCS) -o $(NAME)
	@echo $(GREEN) "$(NAME) was created ! " $(NONE)

%o: %.c
	c++ -c $(FLAGS) $< -o $@

clean:
	@echo $(RED) "-- Deleting-- " $(NONE)
	@sleep 0.2
	@rm -rf $(OBJ_PATH)
	@echo $(RED) "Objects was deleted" $(NONE)

fclean: clean
	@echo $(RED) "Deleting --$(NAME)-- " $(NONE)
	@sleep 0.2
	@rm -rf $(NAME)
	@echo $(RED) "$(NAME) was deleted !" $(NONE)

re: fclean all

.PHONY: all clean fclean re