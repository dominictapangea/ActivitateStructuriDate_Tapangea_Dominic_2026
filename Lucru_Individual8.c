#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Carte {

	int id;
	char* titlu;
	float pret;
};

typedef struct Carte Carte;

struct NodArbore {
	Carte info;
	struct NodArbore* left;
	struct NodArbore* right;
};

typedef struct NodArbore NodArbore;


void inserareInAbrore(NodArbore** radacina, Carte c) {
	if (*radacina != NULL) {
		if (c.id < (*radacina)->info.id) {
			inserareInAbrore(&(*radacina)->left, c);
		}
		else if (c.id > (*radacina)->info.id) {
			inserareInAbrore(&(*radacina)->right, c);
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->info = c;
		nou->left = NULL;
		nou->right = NULL;
		*radacina = nou;
	}
}


void afisareCarte(Carte c)
{
	printf("ID: %d || Titlu: %-15s || Pret: %.2f RON\n", c.id, c.titlu, c.pret);
}

void afisareInOrdine(NodArbore* radacina) 
{
	if (radacina != NULL) {
		afisareInOrdine(radacina->left);
		afisareCarte(radacina->info);
		afisareInOrdine(radacina->right);
	}
}