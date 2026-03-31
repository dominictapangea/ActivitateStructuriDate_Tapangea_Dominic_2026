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


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
typedef struct Nod Nod;

struct Nod {
	Masina masina;
	Nod* next;
};


void pushStack(Nod** stiva,  Masina masina) {

	Nod* first = (Nod*)malloc(sizeof(Nod));
	first->masina = masina;
	first->next = *stiva;
	(*stiva) = first;

}

Masina popStack(Nod** stiva) {
	if ((*stiva) == NULL) {
		Masina rezultat;
		rezultat.id = -1;
		return rezultat;
	}

	Masina rezultat = (*stiva)->masina;
	Nod* temp = (*stiva)->next;
	free(*stiva);
	*stiva = temp;
	return rezultat;

}

char isEmptyStack(Nod** stiva) {

	return stiva = NULL;
}

void* citireStackMasiniDinFisier(const char* numeFisier) {

	FILE* file = fopen(numeFisier, "r");
	if (!file) {
		return NULL;
	}
	Nod* stiva = (Nod*)malloc(sizeof(Nod));
	while (!feof(file)) {
		Masina masina = citireMasinaDinFisier(file);
		pushStack(&stiva, masina);
	}
	fclose(file);
	return stiva;
}

void dezalocareStivaDeMasini(/*stiva*/) {
	//sunt dezalocate toate masinile si stiva de elemente
}

int size(/*stiva*/) {
	//returneaza numarul de elemente din stiva
}

typedef NodDublu NodDublu;
struct NodDublu
{
	Masina info;
	NodDublu* next;
	NodDublu* prev;

};
typedef struct ListaDubla ListaD;
struct ListaDubla
{
	NodDublu* first;
	NodDublu* last;
};

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
void enqueue(ListaD* coada , Masina masina) {
	//adauga o masina in coada
	NodDublu* newNod = malloc(sizeof(NodDublu));
	newNod->info = masina;
	newNod->next = NULL;
	newNod->prev = coada->last;
	if (coada->last) {
		coada->last->next = newNod;
	}
	else {
		coada->first = newNod;
	}
	coada->last = newNod;

}

Masina dequeue(ListaD* coada) {
	//extrage o masina din coada
	Masina rezultat;
	rezultat.id = -1;
	if (coada->first) {
		rezultat = coada->first->info;
		NodDublu* temp = coada->first;
		coada->first = temp->next;
		free(temp);
	}
	return rezultat;
}

ListaD citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	
	ListaD coada;
	coada.first = coada.last = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			enqueue(&coada, citireMasinaDinFisier(f));
		}
		fclose(f);
	}
	return coada;
}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


//metode de procesare
Masina getMasinaByID(Nod** stiva, int id) {
	Masina rezultat;
	rezultat.id = -1;
	if ((*stiva) == NULL)
	{
		/*rezultat.id = -1;*/
		return rezultat;
	}
	Nod* stivaNoua = NULL;
	while ((*stiva)) {
		Masina masinaNoua = popStack(stiva);
		if (masinaNoua.id == id)
		{
			rezultat = masinaNoua;
			break;
		}
		else {
			pushStack(&stivaNoua, masinaNoua);
		}
		
	}
	while (stivaNoua) {
		pushStack(stiva, popStack(&stivaNoua));
	}
	return rezultat;
}

float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {

	Nod* stiva = citireStackMasiniDinFisier("masini.txt.txt");

	afisareMasina(popStack(&stiva));
	afisareMasina(popStack(&stiva));

	afisareMasina(getMasinaByID(&stiva, 7));

	printf("coada-------------------------------\n");
	ListaD coada = citireCoadaDeMasiniDinFisier("masini.txt.txt");
	afisareMasina(dequeue(&coada));
	afisareMasina(dequeue(&coada));


	return 0;
}