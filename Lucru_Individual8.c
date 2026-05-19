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

