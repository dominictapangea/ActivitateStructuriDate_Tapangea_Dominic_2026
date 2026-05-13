#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

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

typedef struct NodP NodP;
typedef struct NodS NodS;

struct NodP {
	Masina m;
	NodP* next;
	NodS* vecini;
};

struct NodS {
	NodS* next;
	NodP* info;
};


void inserareListaP(NodP** graf, Masina m)
{
	NodP* nou = (NodP*)malloc(sizeof(NodP));
	nou->m = m;
	nou->next = NULL;
	nou->vecini = NULL;

	if (*graf) {
		NodP* aux = (*graf);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		(*graf) = nou;
	}
}

void inserareListaS(NodS** lista, NodP* vecin)
{
	NodS* nou = (NodS*)malloc(sizeof(NodS));
	nou->info = vecin;
	nou->next = NULL;
	if (*lista) {
		NodS* aux = *lista;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		nou = *lista;

	}
}

void* cautaNodDupaID(NodP* listaPrincipala, int id) {
	NodP* temp = listaPrincipala;
	while (temp) {
		if (temp->m.id == id)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

//4.
//inserare muchie
void inserareMuchie(void* listaPrincipala, int idStart, int idStop) {

}


void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void citireMuchiiDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareNoduriGraf(void* listaPrincipala) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
}

int main() {


	return 0;
}