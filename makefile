cc = clang++
ccd = clang++ -fsanitize=address -g -lgtest -lgtest_main
all:
	$(cc) main.cpp -o calendar.bin

test:
	$(ccd) tests/event.cpp event.cpp -o events.test
	$(ccd) tests/tag.cpp tag.cpp -o tags.test
	$(ccd) tests/date.cpp date.cpp -o date.test

date:
	$(ccd) tests/date.cpp date.cpp -o date.test

clean:
	rm -f *.bin
	rm -f *.test
