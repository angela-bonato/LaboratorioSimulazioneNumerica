CC = g++
CFLAGS = -Wall -O3 --std=c++11

es5.exe : es5.o random.o libGen.o lib5.o
	$(CC) lib5.o libGen.o random.o es5.o -o es5.exe
es5.o : es5.cpp
	$(CC) -c es5.cpp -o es5.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
libGen.o : ../libGen.cpp ../libGen.h
	$(CC) -c ../libGen.cpp -o libGen.o $(CFLAGS)
lib5.o : lib5.cpp lib5.h
	$(CC) -c lib5.cpp -o lib5.o $(CFLAGS)
clean :
	rm *.o *.dat es5.exe seed.out
