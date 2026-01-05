cc = clang++
all:
	$(cc) main.cpp -o calendar.bin

test:
	$(cc) tests/event_test.cpp -o tests.bin -lgtest -lgtest_main

clean:
	rm *.o
	rm *.bin
