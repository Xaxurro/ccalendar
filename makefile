cc = clang++
all:
	$(cc) main.cpp -o calendar.bin

test:
	$(cc) -fsanitize=address -g tests/event_test.cpp -o events.test -lgtest -lgtest_main
	$(cc) -fsanitize=address -g tests/tag_test.cpp -o tags.test -lgtest -lgtest_main

clean:
	rm -f *.bin
	rm -f *.test
