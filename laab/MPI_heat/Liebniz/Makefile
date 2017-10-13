# kompilator c
CCOMP = /usr/lib64/openmpi/bin/mpicc

# konsolidator
LINK = /usr/lib64/openmpi/bin/mpicc

MPIRUN = /usr/lib64/openmpi/bin/mpiexec 

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG -p
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3 -fopenmp -p

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

# zaleznosci i komendy

Leibniz: Leibniz.o
	$(LINK) $(OPT) Leibniz.o -o Leibniz $(LIB)

Leibniz.o: Leibniz.c
	$(CCOMP) -c $(OPT) Leibniz.c $(INC)

run:
	$(MPIRUN) -np 8 ./Leibniz

clean:
	rm -f *.o
