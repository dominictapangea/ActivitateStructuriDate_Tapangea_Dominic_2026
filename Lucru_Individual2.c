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
	printf("ID: %d || Titlu: %-10s || Pret: %.2f\n", carte.id, carte.titlu, carte.pret);
    
}

void afisareLista(Nod* cap) {

	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void inserareLaFinal(Nod** cap, Carte carteNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->next = NULL;
	if (!*cap) {
		*cap = nou;
	}
	else
	{
		Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
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

Nod* citireListaCartiDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("eroare la deschiderea fisierului!\n");
		return NULL;
	}
	Nod* cap = NULL;

	while (!feof(f)) {
		Carte carteNoua = citireCarteDinFisier(f);
		inserareLaFinal(&cap, carteNoua);
	}
	fclose(f);
	return cap;
}

int main()
{
	Nod* cap = NULL;


}