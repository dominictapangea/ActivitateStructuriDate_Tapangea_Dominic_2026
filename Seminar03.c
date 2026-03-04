
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

void afisareMasina(Masina masina) {
	
	printf("ID: %d || Numar usi: % d || Pret: %f || Model: %-10s || Nume sofer: %-10s || Serie: %c\n",
		masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	
	if (masini = NULL || nrMasini == 0) {
		printf("Vectorul de masini este gol\n");
		return;
	}
	for (int i = 0;i < nrMasini;i++)
		afisareMasina(masini[i]);
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	
	Masina* temp = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0;i < *nrMasini;i++) {
		temp[i] = (*masini)[i];
	}

	temp[*nrMasini] = masinaNoua;
	free(*masini);

	*masini = temp;
	*nrMasini++;
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un stream deja deschis
	//masina citita este returnata;
	char linie[256];
	fgets(linie, 256, file);
	char delimitator[3] = ",\n";
	Masina masina;

	masina.id = atoi(strtok(linie, delimitator));
	masina.nrUsi = atoi(strtok(NULL, delimitator));
	masina.pret = atof(strtok(NULL, delimitator));

	char* aux = strtok(NULL, delimitator);
	masina.model = malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(masina.model, aux);
    aux = strtok(NULL, delimitator);
	masina.numeSofer = (char*)malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(masina.numeSofer, aux);
	masina.serie = strtok(NULL, delimitator)[0];

	return masina;

}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {


	return 0;
}