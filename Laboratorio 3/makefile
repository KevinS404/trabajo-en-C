CC = gcc
TARGET = lab3
SOURCE = lab3.c
OBJETS = lab3.o
FLAGS = -Wall -lm -pthread -lniceprint -L .

$(TARGET): $(OBJETS)
	$(CC) $(OBJETS) -o $(TARGET) $(FLAGS)

%.o: %.c 
	$(CC) -c $< -o $@
	
clean:
	rm -f $(OBJETS) $(TARGET)

run:
	./lab3 -N 35 -c 5 -i nombreEntrada.txt -o nombreSalida.txt -b 5 -h 5 -D

.PHONY: clean