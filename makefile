COMPILER = clang++
DEBUG ?= true
FLAGS_DEBUG = -fsanitize=address -g -Wall -Wextra
FLAGS_RELEASE = -O2 -Wall -Wextra
GTEST = -lgtest -lgtest_main
FLAGS = 

TESTS = files.test colors.test date.test rules.test tags.test regex.test event.test

ifeq ($(DEBUG),true)
	FLAGS = $(FLAGS_DEBUG)
else
	FLAGS = $(FLAGS_RELEASE)
endif

event.o = event.o strings.o date.o tags.o
rules = $(wildcard rules/*.cpp)
rules.o = $(rules:.cpp=.o)
all.o = $(event.o) $(rules.o) files.o

tests-run: FLAGS = $(FLAGS_DEBUG)
tests-run: $(TESTS)
	./colors.test && ./date.test && ./tags.test && ./rules.test && ./regex.test && ./event.test && ./files.test 

files.test: tests/files.cpp files.o $(all.o)
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

colors.test: tests/color.cpp
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

date.test: tests/date.cpp date.o 
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

rules.test: tests/rules.cpp strings.o date.o $(rules.o)
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

tags.test: tests/tags.cpp tags.o date.o strings.o
	$(COMPILER) $(FLAGS) $^  -o $@ $(GTEST)

event.test: tests/event.cpp $(all.o)
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

regex.test: tests/regex.cpp $(all.o)
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

release: FLAGS = $(FLAGS_RELEASE)
release: $(all.o)
	$(COMPILER) main.cpp $(all.o) -o ccalendar

regex.bin: debug/regex.cpp $(all.o)
	$(COMPILER) $(FLAGS) $^ -o $@ $(GTEST)

clean:
	rm -f *.bin
	rm -f debug/*.bin
	rm -f *.test
	rm -f *.o
	rm -f rules/*.o

%.o: %.cpp
	$(COMPILER) -c $(FLAGS) $^ -o $@
