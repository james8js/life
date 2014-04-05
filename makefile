CC = cc  

all: life.o file.o png.o lodepng.o functions.o main.c 
	$(CC) life.o file.o png.o lodepng.o functions.o main.c -o life -Wall -g

life.o: life.c life.h
	$(CC) -c life.c life.h

file.o: file.c file.h
	$(CC) -c file.c file.h

png.o: png.c png.h
	$(CC) -c png.c png.h

lodepng.o: lodepng.c lodepng.h
	$(CC) -c lodepng.c lodepng.h

functions.o: functions.c functions.h
	$(CC) -c functions.c functions.h

