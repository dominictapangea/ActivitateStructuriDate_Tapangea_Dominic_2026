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

struct NodArbore {
	Masina info;
	struct NodArbore* left;
	struct NodArbore* right;
};

typedef struct NodArbore NodArbore;

//creare structura pentru un nod dintr-un arbore binar de cautare

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
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


void adaugaMasinaInArbore( NodArbore** root, Masina masinaNoua) {
	
	if (*root) {
		if ((*root)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*root)->left, masinaNoua);
		}
		else
		{
			adaugaMasinaInArbore(&(*root)->right, masinaNoua);
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->info = masinaNoua;
		nou->left = NULL;
		nou->right = NULL;
		(*root) = nou;
	}
}

NodArbore* citireArboreDeMasiniDinFisier(const char* numeFisier) {

	FILE* file = fopen(numeFisier, "r");
	NodArbore* root = NULL;
	if (file) {
		while (!feof(file))
		{
			Masina m = citireMasinaDinFisier(file);
			adaugaMasinaInArbore(&root, m);
		}
	}
	fclose(file);
	return root;
}

void afisareInOrdine(NodArbore* root) {

	if (root) {
		afisareInOrdine(root->left);
		afisareMasina(root->info);
		afisareInOrdine(root->right);

	}
}

void afisareMasiniDinArbore(NodArbore* root) {

	if (root) {
		afisareMasina(root->info);
		afisareMasiniDinArbore(root->left);
		afisareMasiniDinArbore(root->right);

	}
}

void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente
}

Masina getMasinaByID(/*arborele de masini*/int id) {
	Masina m;

	return m;
}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {

	NodArbore* radacina = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareInOrdine(radacina);
	return 0;
}