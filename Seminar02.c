#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>


struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};
struct Telefon initializare(int id, int RAM, char* producator, float pret, char serie) {
	struct Telefon t;
	t.id = id;
	t.RAM = RAM;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(t.producator, producator);
	t.pret = pret;
	t.serie = serie;


	return t;
}

struct Telefon copiazaTelefon(struct Telefon t) {
	struct Telefon telefon = initializare(t.id, t.RAM, t.producator, t.pret, t.serie);
	return telefon;
}

void afisare(struct Telefon t) {
	//afisarea tuturor atributelor.
	printf("Id: %d\nRAM: %d\nProducator: %s\nPret: %.2f\nSerie: %c\n\n", t.id, t.RAM, t.producator, t.pret, t.serie);
}

void afisareVector(struct Telefon* vector, int nrElemente) {

	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0;i < nrElemente;i++)
	{
		afisare(vector[i]);
	}
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	if (nrElementeCopiate > nrElemente) {
		nrElementeCopiate = nrElemente;
	}
	struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);

	if (vectorNou != NULL) {
		for (int i = 0;i < nrElementeCopiate;i++)
		{
			vectorNou[i] = copiazaTelefon(vector[i]);
		}
	}
	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul

	for (int i = 0;i < *nrElemente;i++) {
		free((*vector)[i].producator);
		(*vector)[i].producator = NULL;
	}

	*vector = NULL;
	*nrElemente = 0;

}

void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pret_min, struct Telefon** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;
	for (int i = 0;i < nrElemente;i++) {
		if (vector[i].pret >= pret_min) {
			(*dimensiune)++;
		}
	}

	*vectorNou = malloc((*dimensiune) * sizeof(struct Telefon));

	for (int i = 0, j = 0;i < nrElemente;i++) {
		if (vector[i].pret >= pret_min) {
			(*vectorNou)[j] = copiazaTelefon(vector[i]);
			j += 1;
		}
	}
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon s;
	s.id = 1;

	return s;
}



int main() {

	struct Telefon t;
	t = initializare(1, 64, "IOS", 1000.5, 'A');
	afisare(t);

	int nrTelefoane = 3;
	struct Telefon* telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);

	telefoane[0] = initializare(1, 64, "IOS", 1005.5, 'A');
	telefoane[1] = initializare(2, 64, "IOS", 1008.5, 'S');
	telefoane[2] = copiazaTelefon(t);

	afisareVector(telefoane, nrTelefoane);

	int nrTelefoaneCopiate = 2;
	struct Telefon* telefoaneCopiate = copiazaPrimeleNElemente(telefoane, nrTelefoane, 2);
	printf("Vector telefoane copiate: \n");
	afisareVector(telefoaneCopiate, nrTelefoaneCopiate);

	dezalocare(&telefoaneCopiate, &nrTelefoaneCopiate);
	printf("Vector telefoane dupa dezalocare: \n");
	afisareVector(telefoane, nrTelefoane);

	struct Telefon* vectorNou;
	int dimensiune;
	copiazaTelefoaneScumpe(telefoane, nrTelefoane, 1006.8, &vectorNou, &dimensiune);
	printf("Telefoane scumpe: \n");
	afisareVector(vectorNou, dimensiune);

	return 0;
}