CC = g++
CFLAGS = -Wall -O3 --std=c++11

es3.exe : es3.o random.o libGen.o lib3.o
	$(CC) lib3.o libGen.o random.o es3.o -o es3.exe
es3.o : es3.cpp
	$(CC) -c es3.cpp -o es3.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
libGen.o : ../libGen.cpp ../libGen.h
	$(CC) -c ../libGen.cpp -o libGen.o $(CFLAGS)
lib3.o : lib3.cpp lib3.h
	$(CC) -c lib3.cpp -o lib3.o $(CFLAGS)
clean :
	rm *.o *.dat es3.exe seed.out
