CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: es7.exe
es7.exe : system.o es7.o particle.o random.o lib7.o
	$(CC) system.o particle.o random.o lib7.o es7.o -o es7.exe $(AFLAGS)
es7.o : es7.cpp SOURCE/system.h SOURCE/particle.h lib7.h
	$(CC) -c es7.cpp -o es7.o $(CFLAGS)
system.o : SOURCE/system.cpp SOURCE/system.h ../RandomGenerator/random.h SOURCE/particle.h
	$(CC) -c SOURCE/system.cpp -o system.o $(CFLAGS)
particle.o : SOURCE/particle.cpp SOURCE/particle.h
	$(CC) -c SOURCE/particle.cpp -o particle.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
lib7.o : lib7.cpp lib7.h
	$(CC) -c lib7.cpp -o lib7.o $(CFLAGS)
clean :
	rm *.o es7.exe
remove:
	rm OUTPUT/*.*
	rm OUTPUT/CONFIG/*.*
