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


void filtreazaHeap(Heap heap, int pozitieNod)
{
	int stanga = 2 * pozitieNod + 1;
	int dreapta = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;

	if (stanga<heap.nrElemViz && heap.vector[stanga].gradUrgenta>heap.vector[pozMax].gradUrgenta) {
		pozMax = stanga;
	}

	if (dreapta<heap.nrElemViz && heap.vector[dreapta].gradUrgenta>heap.vector[pozMax].gradUrgenta) {
		pozMax = dreapta;
	}

	if (pozMax != pozitieNod) {
		Pacient aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;

		filtreazaHeap(heap, pozMax);
	}
}

Pacient extragePacient(Heap* heap)
{
	Pacient rezultat;
	rezultat.id = -1;

	if (heap->nrElemViz > 0) {
		rezultat = heap->vector[0];

		heap->vector[0] = heap->vector[heap->nrElemViz - 1];
				heap->nrElemViz--;
		
		filtreazaHeap(*heap,0);
		return rezultat;
	}

}