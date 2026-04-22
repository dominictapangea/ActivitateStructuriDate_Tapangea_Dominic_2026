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
