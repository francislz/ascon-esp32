# Makefile

# variáveis
CPP = g++
CPPFLAGS = -Wall -Wconversion

OBJ = main.o ascon.o ascon_permutation.o

# dependências
main: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o main
	
main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o main.o

ascon_permutation.o: ascon_permutation.cpp ascon_permutation.hpp defs.hpp
	$(CPP) $(CPPFLAGS) -c ascon_permutation.cpp -o ascon_permutation.o

ascon.o: ascon.cpp ascon.hpp defs.hpp
	$(CPP) $(CPPFLAGS) -c ascon.cpp -o ascon.o

all: main

clean:
	rm -f *.o