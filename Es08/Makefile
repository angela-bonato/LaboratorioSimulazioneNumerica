CC = g++
CFLAGS = -Wall -O3 --std=c++11

es8.exe : es8.o random.o libGen.o lib8.o
	$(CC) lib8.o libGen.o random.o es8.o -o es8.exe
es8.o : es8.cpp
	$(CC) -c es8.cpp -o es8.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
libGen.o : ../libGen.cpp ../libGen.h
	$(CC) -c ../libGen.cpp -o libGen.o $(CFLAGS)
lib8.o : lib8.cpp lib8.h
	$(CC) -c lib8.cpp -o lib8.o $(CFLAGS)
clean :
	rm *.o *.dat es8.exe seed.out
