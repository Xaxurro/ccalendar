COMPILER = clang++
DEBUG = true
FLAGS_DEBUG = -fsanitize=address -g -Wall -Wextra
GTEST = -lgtest -lgtest_main
FLAGS = 

TESTS = date.test rules.test tags.test event.test

ifeq ($(DEBUG),true)
	FLAGS += $(FLAGS_DEBUG)
endif

event.o = event.o strings.o date.o tags.o
rules = $(wildcard rules/*.cpp)
rules.o = $(rules:.cpp=.o)

tests: $(TESTS)

tests-run:
	./date.test && ./tags.test && ./rules.test && ./event.test

date.test: tests/date.cpp date.o 
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

rules.test: tests/rules.cpp date.o $(rules.o)
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

tags.test: tests/tags.cpp tags.o strings.o
	$(COMPILER) $(FLAGS) $^  -o $@ $(GTEST)

event.test: tests/event.cpp $(event.o) $(rules.o)
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

regex:
	$(COMPILER) debug/regex.cpp $(event.o) $(rules.o) -o debug/regex.bin

clean:
	rm -f *.bin
	rm -f debug/*.bin
	rm -f *.test
	rm -f *.o
	rm -f rules/*.o

%.o: %.cpp
	$(COMPILER) -c $(FLAGS) $^ -o $@
