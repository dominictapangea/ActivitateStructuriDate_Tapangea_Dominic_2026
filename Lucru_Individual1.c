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