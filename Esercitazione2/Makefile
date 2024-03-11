CC = g++
CFLAGS = -Wall -O3 --std=c++11

es2.exe : es2.o random.o libGen.o lib2.o
	$(CC) lib2.o libGen.o random.o es2.o -o es2.exe
es2.o : es2.cpp
	$(CC) -c es2.cpp -o es2.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
libGen.o : ../libGen.cpp ../libGen.h
	$(CC) -c ../libGen.cpp -o libGen.o $(CFLAGS)
lib2.o : lib2.cpp lib2.h
	$(CC) -c lib2.cpp -o lib2.o $(CFLAGS)
clean :
	rm *.o *.dat es2.exe seed.out
