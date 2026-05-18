#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pacient {
	int id;
	char* nume;
	int varsta;
	int gradUrgenta;
	char* simptome;
};

typedef struct Pacient Pacient;

struct Heap {
	int lungime;
	int nrElemViz;
	Pacient* vector;
};

typedef struct Heap Heap;

Heap initializareHeap(int lungime)
{
	Heap heap;
	heap.lungime = lungime;
	heap.nrElemViz = 0;
	heap.vector = (Pacient*)malloc(sizeof(Pacient) * lungime);
	return heap;
}

void afisarePacient(Pacient p)
{
	printf("Id: %d\n", p.id);
	printf("Nume : %s\n", p.nume);
	printf("Varsta: %d\n", p.varsta);
	printf("Grad Urgenta: %d\n", p.gradUrgenta);
	printf("Simptome: %s\n", p.simptome);
}


