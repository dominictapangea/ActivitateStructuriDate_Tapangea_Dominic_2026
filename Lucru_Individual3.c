#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	char* titlu;
	float pret;
};

typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Nod {
	Carte info;
	struct Nod* next;
	struct Nod* prev;
};

struct ListaDubla {
	Nod* prim; 
	Nod* ultim;
};

struct Carte Initializare(int id, char* titlu, float pret)
{
	Carte c;
	c.id = id;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	c.pret = pret;

	return c;
}

void inserareLaFinal(ListaDubla* lista, Carte carteNoua)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->next = NULL;
	nou->prev = lista->ultim;
	if (lista->ultim != NULL) {
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

void afisareCarte(Carte carte) {
	
	printf("ID: %d || Titlu: %-10s || Pret: %.2f\n", carte.id, carte.titlu, carte.pret);
}

void afisareDeLaInceput(ListaDubla lista) {

	Nod* temp = lista.prim;

	while (temp) {
		afisareCarte(temp->info);
		temp = temp->next;
	}
}

void afisareDeLaFinal(ListaDubla lista) {

	Nod* temp = lista.ultim;
	while (temp) {
		afisareCarte(temp->info);
		temp = temp->prev;
	}
}

Carte citireCarteDinFisier(FILE* f) {
	char buffer[256];
	fgets(buffer, 256, f);

	char delimitator[3] = ",\n";

	int id = atoi(strtok(buffer, delimitator));
	char* titlu_temp = strtok(NULL, delimitator);
	float pret = atof(strtok(NULL, delimitator));

	return Initializare(id, titlu_temp, pret);
}

ListaDubla citireLDCartiDinFisier(const char* numeFisier) {

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("Eroare la deschiderea fisierului\n");
		return lista;
	}

	while (!feof(f)) {
		Carte c = citireCarteDinFisier(f);
		inserareLaFinal(&lista, c);
	}
	fclose(f);
	return lista;
}

void stergeCarteDupaID(ListaDubla* lista, int idCautat)
{
	Nod* p = lista->prim;
	while (p != NULL && p->info.id != idCautat) {
		p = p->next;
	}
	if (p) {
		if (p->prev != NULL) {
			p->prev->next = p->next;
		}
		else {
			lista->prim = p->next;
		}

		if (p->next != NULL) {
			p->next->prev = p->prev;
		}
		else {
			lista->ultim = p->prev;
		}
		free(p->info.titlu);
		free(p);
	}
}