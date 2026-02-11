cc = clang++
cco = clang++ -c
ccd = clang++ -fsanitize=address -g -lgtest -lgtest_main

event.o = event.o strings.o date.o tags.o
rules = $(wildcard rules/*.cpp)
rules.o = $(rules:.cpp=.o)

tests: date.test rules.test tags.test event.test

tests-run:
	./date.test && ./tags.test && ./event.test && ./rules.test

date.test: tests/date.cpp date.o 
	$(ccd) $^ -o $@

rules.test: tests/rules.cpp date.o $(rules.o)
	$(ccd) $^ -o $@

tags.test: tests/tags.cpp tags.o strings.o
	$(ccd) $^  -o $@

event.test: tests/event.cpp $(event.o) $(rules.o)
	$(ccd) $^ -o $@

regex:
	$(cc) debug/regex.cpp $(event.o) $(rules.o) -o debug/regex.bin

clean:
	rm -f *.bin
	rm -f debug/*.bin
	rm -f *.test
	rm -f *.o
	rm -f rules/*.o

%.o: %.cpp
	$(cco) $^ -o $@
