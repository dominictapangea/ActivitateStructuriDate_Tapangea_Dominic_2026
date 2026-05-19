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