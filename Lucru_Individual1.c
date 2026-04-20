#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Laptop {
	int id;
	char* brand;
	float pret;
};
typedef struct Laptop Laptop;
void afisareLaptop(Laptop laptop) {
	printf("ID: %d || Brand: %-10s || Pret: %.2f\n", laptop.id, laptop.brand, laptop.pret);
}

struct Laptop initializare(int id, char* brand, float pret) {
	struct Laptop l;
	l.id = id;
	l.brand = (char*)malloc(sizeof(char)* (strlen(brand)+1));
	strcpy(l.brand, brand);
	l.pret = pret;

	return l;
}

void adaugaLaptopInVector(Laptop** vector, int* nrLaptopuri, Laptop laptopNou)
{
	Laptop* temp = (Laptop*)malloc(sizeof(Laptop) * ((*nrLaptopuri)+1));

	for (int i = 0;i < *nrLaptopuri;i++) {
		temp[i] = (*vector)[i];
			}

	temp[*nrLaptopuri] = laptopNou;
	free(*vector);

	*vector = temp;
	(*nrLaptopuri)++;
}

Laptop citireLaptopDinFisier(FILE* f)
{
	char buffer[256];
	fgets(buffer, 256, f);
	
	char delimitator[3] = ",\n";

	int id = atoi(strtok(buffer, delimitator));
	char* brand_temp = strtok(NULL, delimitator);
	float pret = atof(strtok(NULL, delimitator));

	Laptop laptop = initializare(id, brand_temp, pret);
	return laptop;
}

Laptop* citireVectorFisier(const char* numeFisier, int* nrLaptopuri)
{
	FILE* file = fopen(numeFisier,"r");
	if (!file) {
		printf("Eroare la deschidere\n");
		return;
	}
	
		Laptop* vector = NULL;
		*nrLaptopuri = 0;

		while (!feof(file)) {
			Laptop laptopNou= citireLaptopDinFisier(file);
			adaugaLaptopInVector(&vector, nrLaptopuri, laptopNou);
		}
		fclose(file);
		return vector;
}