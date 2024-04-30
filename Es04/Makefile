CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: es4.exe
es4.exe : system.o es4.o particle.o random.o
	$(CC) system.o particle.o random.o es4.o -o es4.exe $(AFLAGS)
es4.o : es4.cpp SOURCE/system.h SOURCE/particle.h
	$(CC) -c es4.cpp -o es4.o $(CFLAGS)
system.o : SOURCE/system.cpp SOURCE/system.h ../RandomGenerator/random.h SOURCE/particle.h
	$(CC) -c SOURCE/system.cpp -o system.o $(CFLAGS)
particle.o : SOURCE/particle.cpp SOURCE/particle.h
	$(CC) -c SOURCE/particle.cpp -o particle.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o es4.exe
remove:
	rm OUTPUT/*.*
	rm OUTPUT/CONFIG/*.*
