CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: es6.exe
es6.exe : system.o es6.o particle.o random.o
	$(CC) system.o particle.o random.o es6.o -o es6.exe $(AFLAGS)
es6.o : es6.cpp SOURCE/system.h SOURCE/particle.h
	$(CC) -c es6.cpp -o es6.o $(CFLAGS)
system.o : SOURCE/system.cpp SOURCE/system.h ../RandomGenerator/random.h SOURCE/particle.h
	$(CC) -c SOURCE/system.cpp -o system.o $(CFLAGS)
particle.o : SOURCE/particle.cpp SOURCE/particle.h
	$(CC) -c SOURCE/particle.cpp -o particle.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o es6.exe
remove:
	rm OUTPUT/*.*
	rm OUTPUT/CONFIG/*.*
