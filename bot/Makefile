NAME				=	bot

DIRECTORY_CHECK		=	src
DIRECTORY_SOURCE	=	src
DIRECTORY_OBJECT	=	objects

FILES_CHECK			=	bot.hpp
FILES_SOURCE		=	bot.cpp \
						main.cpp

COMPILE				=	clang++
COMPILATION_FLAG	=	-Wall -Wextra -Werror -std=c++98 -g 

ARGUMENTS			=	localhost 6667 password

GREEN = '\033[92m'
RED = '\033[91m'
NONE = '\033[3m'

all: $(NAME)
	echo $(GREEN)"----- | --- --- --- ---  USAGE --- --- --- --- ---| -----"$(NONE)
	echo $(GREEN)"----- | ./bot <ip> <port> <password> <nickname>   | -----"$(NONE)
	echo $(GREEN)"----- | --- --- --- --- ------ --- --- --- --- ---| -----"$(NONE)

$(DIRECTORY_OBJECT)/%.o: $(DIRECTORY_SOURCE)/%.cpp $(FILES_CHECK:%=$(DIRECTORY_CHECK)/%)
	@printf "\e[33m"
	@printf "Compile\t$< -> $@\n"
	mkdir -p $(dir $@)
	$(COMPILE) $(COMPILATION_FLAG) -c $< -o $@

$(NAME): $(FILES_SOURCE:%.cpp=$(DIRECTORY_OBJECT)/%.o)
	@printf "Compile src/messages.cpp -> objects/messages.o\t\n"
	@printf "\e[32m"
	@printf "Build\t$@\n"
	$(COMPILE) -o $@ $(FILES_SOURCE:%.cpp=$(DIRECTORY_OBJECT)/%.o)

run: all
	@printf "\e[0m"
	./$(NAME) $(ARGUMENTS)

clean:
	@printf "\e[31m"
	@printf "Remove\t$(DIRECTORY_OBJECT)\n"
	rm -rf $(DIRECTORY_OBJECT)

fclean: clean
	@printf "Remove\t$(NAME)\n"
	rm -f $(NAME)

re: fclean all

rrun: re run

leaks: all
	@printf "\e[0m"
	valgrind make run

.PHONY: all run clean fclean re rrun leaks
.SILENT: