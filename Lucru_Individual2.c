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

struct Nod {
	Carte info;
	struct Nod* next;
};

typedef struct Nod Nod;

struct Carte Initializare(int id, char* titlu, float pret) {
	struct Carte c;

	c.id = id;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	c.pret = pret;

	return c;
};

void inserareLaInceput(Nod** cap, Carte carteNoua)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->next = *cap;
	*cap = nou;
}

void afisareCarte(Carte carte) {
	printf("ID: %d || Brand: %-10s || Pret: %.2f\n", carte.id, carte.titlu, carte.pret);
    
}

void afisareLista(Nod* cap) {

	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

int main()
{

}