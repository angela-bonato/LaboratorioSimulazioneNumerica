CC = mpic++
CFLAGS = -Wall -O3 --std=c++11

es10.exe : es10.o random.o libGen.o lib10.o city.o path.o parallel.o
	$(CC) parallel.o path.o city.o lib10.o libGen.o random.o es10.o -o es10.exe
es10.o : es10.cpp
	$(CC) -c es10.cpp -o es10.o $(CFLAGS)
random.o : ../RandomGenerator/random.cpp ../RandomGenerator/random.h
	$(CC) -c ../RandomGenerator/random.cpp -o random.o $(CFLAGS)
libGen.o : ../libGen.cpp ../libGen.h
	$(CC) -c ../libGen.cpp -o libGen.o $(CFLAGS)
lib10.o : lib10.cpp lib10.h
	$(CC) -c lib10.cpp -o lib10.o $(CFLAGS)
city.o : city.cpp city.h
	$(CC) -c city.cpp -o city.o $(CFLAGS)
path.o : path.cpp path.h
	$(CC) -c path.cpp -o path.o $(CFLAGS)
parallel.o : parallel.cpp parallel.h
	$(CC) -c parallel.cpp -o parallel.o $(CFLAGS)
clean :
	rm *.o *.dat es10.exe seed.out
