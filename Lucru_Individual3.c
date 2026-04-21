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