cc = clang++
all:
	$(cc) main.cpp -o calendar.bin

clean:
	rm *.o
	rm *.bin
