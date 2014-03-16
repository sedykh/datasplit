CC=g++
CFLAGS=-c -m32 -O3 -Wall -static
all: datasplit

datasplit: datasplit.o apstring.o set.o core.o qsar.o dataset.o
	$(CC) datasplit.o apstring.o set.o core.o qsar.o dataset.o -m32 -o datasplit

apstring.o: apstring.cpp
	$(CC) $(CFLAGS) apstring.cpp
set.o:
	$(CC) $(CFLAGS) set.cpp

core.o: core.cpp
	$(CC) $(CFLAGS) core.cpp

qsar.o: qsar.cpp
	$(CC) $(CFLAGS) qsar.cpp

dataset.o: dataset.cpp
	$(CC) $(CFLAGS) dataset.cpp

datasplit.o: datasplit.cpp
	$(CC) $(CFLAGS) datasplit.cpp

clean:
	rm -rf *.o
