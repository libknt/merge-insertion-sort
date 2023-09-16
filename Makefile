CXX = g++
CXXFLAGS = -std=c++98

ifdef PAIR
CXXFLAGS += -DPAIR
endif

ifdef SEPARATE
CXXFLAGS += -DSEPARATE 
endif

ifdef INSERTATTHESTART
CXXFLAGS += -DINSERTATTHESTART
endif

ifdef SORT
CXXFLAGS += -DSORT
endif

all: program

program: main.o
	$(CXX) $(CXXFLAGS) -o test main.o

main.o:	main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o program

fclean:clean
	rm -f test

re: fclean all

debug:
	make PAIR=1 SEPARATE=1 INSERTATTHESTART=1

p:
	make PAIR=1

sep:
	make SEPARATE=1

first:
	make INSERTATTHESTART=1

sort:
	make SORT=1
	
.PHONY: all program clean fclean re debug p sep first sort