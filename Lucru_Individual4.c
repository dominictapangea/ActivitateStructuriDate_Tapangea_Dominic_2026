#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Pachet {
	int id;
	char* destinatar;
	float greutate;
};

typedef struct Pachet Pachet;

struct Pachet Initializare(int id, char* destinatar, float greutate) {
	Pachet p;

	p.id = id;
	p.destinatar = (char*)malloc(sizeof(char) * (strlen(destinatar) + 1));
	strcpy(p.destinatar, destinatar);
	p.greutate = greutate;

	return p;
}

struct NodStiva {
	Pachet info;
	struct NodStiva* next;
};

typedef struct NodStiva NodStiva;

struct NodCoada {
	Pachet info;
	struct NodCoada* next;
	struct NodCoada* prev;
};

struct Coada {
	NodCoada* prim;
	NodCoada* ultim;
};

typedef struct Coada Coada;
typedef struct NodCoada NodCoada;

void pushStiva(NodStiva** cap, Pachet p)
{
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->info = p;
	nou->next = *cap;
	(*cap) = nou;
}

Pachet popStiva(NodStiva** cap) {
	
	if (!(*cap)) {
		Pachet rezultat;
		rezultat.id = -1;
		return rezultat;
	}
	else
	{
		Pachet rezultat = (*cap)->info;
		NodStiva* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
		return rezultat;
	}
}

void enqueue(Coada* banda, Pachet p) {

	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->info = p;
	nou->next = NULL;
	nou->prev = banda->ultim;
	if (banda->ultim) {
		banda->ultim->next = nou;
	}
	else {
		banda->prim = nou;
	}
	banda->ultim = nou;
}

Pachet dequeue(Coada* banda) {

	if (!banda->prim) {
		Pachet rezultat;
		rezultat.id = -1;
		return rezultat;
	}
	else
	{
		Pachet rezultat = banda->prim->info;
		NodCoada* temp = banda->prim;
		banda->prim = temp->next;
		if (!banda->prim) {
			banda->ultim = NULL;
		}
		else {
			banda->prim->prev = NULL;
		}
		free(temp);
		return rezultat;
	}
}

Pachet getPachetDinStiva(NodStiva** stivaPrincipala, int idCautat) {

	Pachet rezultat;
	rezultat.id = -1;

	NodStiva* stivaAux = NULL;

	while (*stivaPrincipala != NULL) {

		Pachet p = popStiva(stivaPrincipala); 

		if (p.id == idCautat) {
			rezultat = p; 
			pushStiva(&stivaAux, p);
			break; 
		}
		else {
			
			pushStiva(&stivaAux, p);
		}
	}

	while (stivaAux != NULL) {
		
		pushStiva(stivaPrincipala, popStiva(&stivaAux));
	}

	return rezultat;
}

Pachet citirePachetDinFisier(FILE* f) {
	char buffer[256];
	fgets(buffer, 256, f);

	char delimitator[3] = ",\n";

	int id = atoi(strtok(buffer, delimitator));
	char* destinatar_temp = strtok(NULL, delimitator);
	float greutate = atof(strtok(NULL, delimitator));

	return Initializare(id, destinatar_temp, greutate);
}

NodStiva* citireStivaDinFisier(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		return NULL;
	}
	NodStiva* cap = NULL;
	while (!feof(f)) {
		pushStiva(&cap, citirePachetDinFisier(f));
	}
	fclose(f);
	return cap;
}

Coada citireCoadaDinFisier(const char* numeFisier)
{
	Coada banda;
	banda.prim = NULL;
	banda.ultim = NULL;

	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("eroare");
		return banda;
	}
	
	while (!feof(f)) {
		enqueue(&banda, citirePachetDinFisier(f));
	}
	fclose(f);
	return banda;
}

