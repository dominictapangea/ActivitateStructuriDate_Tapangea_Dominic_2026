#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Pachet {
	int id;
	char* destinatar;
	float greutate;
};
typedef struct Pachet Pachet;

struct Nod {
	Pachet info;
	struct Nod* next;
};
typedef struct Nod Nod;


struct HashTable {
	int dimensiune;
	Nod** vector;
};
typedef struct HashTable HashTable;


Pachet initializarePachet(int id, const char* destinatar, float greutate) {
	Pachet p;
	p.id = id;
	p.destinatar = (char*)malloc(sizeof(char) * (strlen(destinatar) + 1));
	strcpy(p.destinatar, destinatar);
	p.greutate = greutate;
	return p;
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dimensiune = dimensiune;
	
	ht.vector = (Nod**)malloc(dimensiune * sizeof(Nod*));

	
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}


int calculeazaHash(int id, int dimensiune) {
	
	return id % dimensiune;
}


void inserareInHashTable(HashTable ht, Pachet p) {
	
	int pozitie = calculeazaHash(p.id, ht.dimensiune);

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;

	nou->next = ht.vector[pozitie];
	ht.vector[pozitie] = nou;
}

Pachet getPachetDupaID(HashTable ht, int idCautat) {
	
	int pozitie = calculeazaHash(idCautat, ht.dimensiune);

	Nod* temp = ht.vector[pozitie];
	while (temp != NULL) {
		if (temp->info.id == idCautat) {
		
			Pachet pGasit;
			pGasit.id = temp->info.id;
			pGasit.greutate = temp->info.greutate;
			pGasit.destinatar = (char*)malloc(sizeof(char) * (strlen(temp->info.destinatar) + 1));
			strcpy(pGasit.destinatar, temp->info.destinatar);

			return pGasit;
		}
		temp = temp->next;
	}

	Pachet nuExista;
	nuExista.id = -1;
	nuExista.destinatar = NULL;
	return nuExista;
}

void afisarePachet(Pachet p) {
	printf("   ID: %d || Destinatar: %-10s || Greutate: %.2f kg\n", p.id, p.destinatar, p.greutate);
}

void afisareHashTable(HashTable ht) {
	
	for (int i = 0; i < ht.dimensiune; i++) {
		printf("Clusterul [%d]:\n", i);
		if (ht.vector[i] == NULL) {
			printf("  Gol\n");
		}
		else {
			Nod* temp = ht.vector[i];
			while (temp != NULL) {
				afisarePachet(temp->info);
				temp = temp->next;
			}
		}
		printf("---------------------------------\n");
	}
}

void dezalocareHashTable(HashTable* ht) {
	
	for (int i = 0; i < ht->dimensiune; i++) {
		Nod* temp = ht->vector[i];
		
		while (temp != NULL) {
			Nod* nodDeSters = temp;
			temp = temp->next;

			free(nodDeSters->info.destinatar); 
			free(nodDeSters);                  
		}
	}
	
	free(ht->vector);
	ht->vector = NULL;
	ht->dimensiune = 0;
}




int main() {
	
	HashTable ht = initializareHashTable(3);

	Pachet p1 = initializarePachet(10, "Popescu", 2.5);
	Pachet p2 = initializarePachet(15, "Ionescu", 1.0); 
	Pachet p3 = initializarePachet(16, "Marines", 5.2); 
	Pachet p4 = initializarePachet(8, "Dumitru", 0.5);  

	
	inserareInHashTable(ht, p1);
	inserareInHashTable(ht, p2);
	inserareInHashTable(ht, p3);
	inserareInHashTable(ht, p4);

	afisareHashTable(ht);

	printf("\nCautam pachetul cu ID-ul 16:\n");
	Pachet cautat = getPachetDupaID(ht, 16);
	if (cautat.id != -1) {
		afisarePachet(cautat);
		free(cautat.destinatar);
	}
	else {
		printf("Pachetul nu a fost gasit!\n");
	}

	dezalocareHashTable(&ht);
	printf("\nMemorie eliberata complet. Tabela a fost distrusa.\n");

	return 0;
}