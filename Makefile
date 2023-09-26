.PHONY: all clean fclean re leak address pair separate first insert

NAME	= PmergeMe
CXX		= c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRC =	main.cpp \
		PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all



# debug address leak pair separate first insert
# CXXFLAGS+= -DLISTDEBUG
# CXXFLAGS+= -DVECTORDEBUG
address:fclean
address:CXXFLAGS+= -g -fsanitize=address
address:all

leak:fclean
leak:CXXFLAGS+= -DLEAK
leak:all

pair:fclean
pair:CXXFLAGS+= -DPAIR
pair:all

separate:fclean
separate:CXXFLAGS+= -DSEPARATE
separate:all

first:fclean
first:CXXFLAGS+= -DFIRST
first:all

insert:fclean
insert:CXXFLAGS+= -DINSERT
insert:all

help:
	@echo "make address"
	@echo "make leak"
	@echo "make pair"
	@echo "make separate"
	@echo "make first"
	@echo "make insert"
	