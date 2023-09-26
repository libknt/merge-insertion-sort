all:
	bash test.sh -n 30 -c 1 -l 100

simple:
	@bash simple_test.sh

clean:
	rm -f PmergeMe

fclean:clean
	make fclean -C ../
	rm -rf ./log
	

p:
	make pair -C ..
 
s:
	make separate -C ..

f:
	make first -C ..

sort:
	make sort -C ..

re:
	make re -C ..

i:
	bash infinity.sh