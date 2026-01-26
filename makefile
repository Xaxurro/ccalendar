cc = clang++
cco = clang++ -c
ccd = clang++ -fsanitize=address -g -lgtest -lgtest_main

cpp = event.cpp strings.cpp date.cpp tags.cpp
event = event.o strings.o date.o tags.o

o:
	$(cco) $(cpp)

test: o
	$(ccd) tests/event.cpp $(event) -o event.test
	$(ccd) tests/tags.cpp $(event) -o tags.test
	$(ccd) tests/date.cpp date.o -o date.test

runtest:
	./date.test && ./tags.test && ./event.test

clean:
	rm -f *.bin
	rm -f *.test
	rm -f *.o
