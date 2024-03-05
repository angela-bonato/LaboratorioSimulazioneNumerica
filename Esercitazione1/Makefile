CC = g++
CFLAGS = -Wall -O3 --std=c++11

es1.exe : es1.o ../RandomGenerator/random.o ../libGen.o lib1.o
	$(CC) lib1.o ../libGen.o ../RandomGenerator/random.o es1.o -o es1.exe
es1.o : es1.cpp
	$(CC) -c es1.cpp -o es1.o $(CFLAGS)
../RandomGenerator/random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o ../RandomGenerator/random.o $(CFLAGS)
../libGen.o : ../libGen.cpp ../libGen.h
	$(CC) -c ../libGen.cpp -o ../libGen.o $(CFLAGS)
lib1.o : lib1.cpp lib1.h
	$(CC) -c lib1.cpp -o lib1.o $(CFLAGS)
clean :
	rm *.o *.dat es1.exe seed.out
