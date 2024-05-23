CC = g++
CFLAGS = -Wall -O3 --std=c++11

es9.exe : es9.o random.o libGen.o lib9.o city.o path.o
	$(CC) path.o city.o lib9.o libGen.o random.o es9.o -o es9.exe
es9.o : es9.cpp
	$(CC) -c es9.cpp -o es9.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
libGen.o : ../libGen.cpp ../libGen.h
	$(CC) -c ../libGen.cpp -o libGen.o $(CFLAGS)
lib9.o : lib9.cpp lib9.h
	$(CC) -c lib9.cpp -o lib9.o $(CFLAGS)
city.o : city.cpp city.h
	$(CC) -c city.cpp -o city.o $(CFLAGS)
path.o : path.cpp path.h
	$(CC) -c path.cpp -o path.o $(CFLAGS)
clean :
	rm *.o *.dat es9.exe seed.out
