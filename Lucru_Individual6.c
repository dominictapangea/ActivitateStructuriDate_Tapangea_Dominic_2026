#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {

	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct StructuraMasina Masina;

struct Heap {
	int lungime;
	int nrElemViz;
	Masina* vector;
};
typedef struct Heap Heap;



void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareHeap(Heap heap) {
	for (int i = 0;i < heap.nrElemViz;i++) {
		afisareMasina(heap.vector[i]);
	}
}


Heap initializareHeap(int lungime)
{
	Heap heap;
	heap.lungime = lungime;
	heap.nrElemViz = 0;
	heap.vector = (Masina*)malloc(sizeof(Masina) * lungime);
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod)
{
	int stanga = 2 * pozitieNod + 1;
	int dreapta = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;

	if (stanga<heap.nrElemViz && heap.vector[stanga].pret>heap.vector[pozMax].pret) {
		pozMax = stanga;
	}

	if (dreapta<heap.nrElemViz && heap.vector[dreapta].pret>heap.vector[pozMax].pret) {
		pozMax = dreapta;
	}

	if (pozMax != pozitieNod) {
		Masina aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;

		filtreazaHeap(heap, pozMax);
	}
}