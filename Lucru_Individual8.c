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

Carte cautareDupaID(NodArbore* radacina, int idCautat)
{
	if (radacina = NULL) {
		Carte c;
		c.id = -1;
		return c;
	}
	else if (idCautat < radacina->info.id) {
		return cautareDupaID(radacina->left, idCautat);
	}
	else if (idCautat > radacina->info.id) {
		return cautareDupaID(radacina->right, idCautat);
	}
	else {
		Carte c = radacina->info;
		c.titlu = (char*)malloc(strlen(radacina->info.titlu) + 1);
		strcpy(c.titlu, radacina->info.titlu);
		return c;
	}
}


int numarNoduri(NodArbore* radacina) {
	if (radacina != NULL) {
		return 1 + numarNoduri(radacina->left) + numarNoduri(radacina->right);
	}
	return 0;
}

int inaltimeArbore(NodArbore* radacina)
{
	if (radacina != NULL) {
		return 1 + max(inaltimeArbore(radacina->left), inaltimeArbore(radacina->right));
	}
	return 0;
}


Carte citireCarteDinFisier(FILE* f)
{
	char buffer[256];
	char sep[3] = ",\n";
	fgets(buffer, 256, f);

	char* aux;
	Carte c;

	aux = strtok(buffer, sep);
	c.id = atoi(aux);

	aux = strtok(NULL, sep);
	c.titlu = (char*)malloc(strlen(aux) + 1);
	strcpy(c.titlu, aux);

	c.pret = atof(strtok(NULL, sep));

	return c;
}

NodArbore* citireArboreDinFisier(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	NodArbore* radacina = NULL;
	if (f) {
		while (!feof(f)) {
			inserareInAbrore(&radacina, citireCarteDinFisier(f));
		}
		fclose(f);
	}
	return radacina;
}


void dezalocareArbore(NodArbore** radacina)
{
	if (*radacina != NULL) {
		dezalocareArbore(&(*radacina)->left);
		dezalocareArbore(&(*radacina)->right);

		free((*radacina)->info.titlu);
		free(*radacina);
		*radacina = NULL;
	}
}
