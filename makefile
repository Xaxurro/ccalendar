cc = clang++
cco = clang++ -c
ccd = clang++ -fsanitize=address -g -lgtest -lgtest_main

cpp = event.cpp strings.cpp date.cpp tags.cpp
rules = rules/*.cpp
event = event.o strings.o date.o tags.o
rules.o = rules/*.o

o:
	$(cco) $(cpp)

date:
	$(cco) date.cpp

date-test: date
	$(ccd) tests/date.cpp date.o -o date.test

rules: date
	cd ./rules && \
	clang++ -c *.cpp && \
	cd ..

rules-test: rules
	$(ccd) tests/rules.cpp $(rules.o) date.o -o rules.test

strings:
	$(cco) strings.cpp

tags: strings
	$(cco) tags.cpp

tags-test: tags
	$(ccd) tests/tags.cpp tags.o strings.o -o tags.test

event: date rules strings tags
	$(cco) event.cpp

event-test: event
	$(ccd) tests/event.cpp $(event) $(rules.o) -o event.test

tests: date-test rules-test tags-test event-test

tests-run:
	./date.test & ./tags.test & ./event.test & ./rules.test

regex:
	$(cc) debug/regex.cpp $(event) $(rules.o) -o debug/regex.bin

clean:
	rm -f *.bin
	rm -f debug/*.bin
	rm -f *.test
	rm -f *.o
	rm -f rules/*.o
