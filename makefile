cc = clang++
cco = clang++ -c
ccd = clang++ -fsanitize=address -g -lgtest -lgtest_main

cpp = event.cpp strings.cpp date.cpp tags.cpp
event = event.o strings.o date.o tags.o
rules = rules.o date.o 

o:
	$(cco) $(cpp)

date:
	$(cco) date.cpp -o date.o

rules: date
	$(cco) rules/fixed.cpp -o rules.o

date-test: date
	$(ccd) tests/date.cpp date.o -o date.test

rules-test: rules
	$(ccd) tests/rules.cpp $(rules) -o rules.test

tests: date-test rules-test
	$(ccd) tests/event.cpp $(event) -o event.test
	$(ccd) tests/tags.cpp $(event) -o tags.test

runtests:
	./date.test & ./tags.test & ./event.test & ./rules.test

clean:
	rm -f *.bin
	rm -f *.test
	rm -f *.o
