CC = gcc
CFLAGS = -Wall -g

.PHONY: all run clean veryclean

all: test_routing

# Compila il file finale eseguibile
test_routing: test_routing.o routing.o
	$(CC) $(CFLAGS) -o $@ test_routing.o routing.o -lm

# Compila i singoli oggetti
routing.o: routing.c routing.h
	$(CC) $(CFLAGS) -c routing.c

test_routing.o: test_routing.c routing.h
	$(CC) $(CFLAGS) -c test_routing.c

# Esegui i test
run: test_routing
	./test_routing

# Pulisci i file oggetto
clean:
	rm -f *.o

# Pulisci anche l’eseguibile
veryclean: clean
	rm -f test_routing
