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


void afisareHeap(Heap heap) {
	for (int i = 0;i < heap.nrElemViz;i++) {
		afisarePacient(heap.vector[i]);
	}
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
	}
	return rezultat;
}


Pacient citirePacientDinFisier(FILE* f)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);

	char* aux;
	Pacient p1;

	aux = strtok(buffer, sep);
	p1.id = atoi(aux);

	aux = strtok(NULL, sep);
	p1.nume = (char*)malloc(strlen(aux) + 1);
	strcpy(p1.nume, aux);
	p1.varsta = atoi(strtok(NULL, sep));
	p1.gradUrgenta = atoi(strtok(NULL, sep));
	
	aux = strtok(NULL, sep);
	p1.simptome = (char*)malloc(strlen(aux) + 1);
	strcpy(p1.simptome, aux);

	return p1;
}


Heap citireHeapDinFisier(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(20);
	if (f) {
		while (!feof(f)) {
			heap.vector[heap.nrElemViz++] = citirePacientDinFisier(f);

		}
		fclose(f);

		for (int i = (heap.nrElemViz - 2) / 2;i >= 0;i--) {
			filtreazaHeap(heap, i);
		}
	}
	return heap;
}

void dezalocareHeap(Heap* heap)
{
	for (int i = 0;i < heap->nrElemViz;i++) {
		free(heap->vector[i].nume);
		free(heap->vector[i].simptome);
	}
	free(heap->vector);
	heap->lungime = 0;
	heap->nrElemViz = 0;
	heap->vector = NULL;
}

int main()
{
	Heap heap = citireHeapDinFisier("pacienti.txt");
	afisareHeap(heap);

	printf("Extrageri: \n");
	Pacient p1 = extragePacient(&heap);
	afisarePacient(p1);
	Pacient p2 = extragePacient(&heap);
	afisarePacient(p2);

	dezalocareHeap(&heap);
	return 0;
}