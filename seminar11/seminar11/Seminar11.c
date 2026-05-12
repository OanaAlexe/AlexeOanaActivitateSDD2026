#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* stg;
	Nod* dr;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
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

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina) {
		return max(calculeazaInaltimeArbore(radacina->stg), calculeazaInaltimeArbore(radacina->dr)) + 1;
	}
	else
	return 0;
}

//ALTE FUNCTII NECESARE:
// - aici veti adauga noile functii de care aveti nevoie.

char calculeazGradEchilibru(Nod* root) {
	if (root) {
		return calculeazaInaltimeArbore(root->stg) - calculeazaInaltimeArbore(root->dr);
	}
	else {
		return 0;
	}
}

void rotireStanga(Nod** root) {
	Nod* aux = (*root)->dr;
	(*root)->dr = aux->stg;
	aux->stg = *root;
}

void rotireDreapta(Nod** root) {
	Nod* aux = (*root)->stg;
	(*root)->stg = aux->dr;
	aux->dr = *root;
}

void adaugaMasinaInArboreEchilibrat(Nod** root, Masina masinaNoua){
	if ((*root)) {
		if ((*root)->info.id > masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&(*root)->stg, masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&(*root)->dr, masinaNoua);
		}
		int grad = calculeazGradEchilibru(*root);
		if (grad == 2) {
			
		}
	}
}

//la lucrare heap, abc, avl, grafuri

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* root = NULL;
	while(!feof(file)) {
		Masina m1 = citireMasinaDinFisier(file);
		adaugaMasinaInArboreEchilibrat(&(root), m1);
	}
	fclose(file);
	return root;
}

void afisareMasiniDinArbore(Nod* root) { //preordine, i think
	if (root) {
		afisareMasina(root->info);
		afisareMasiniDinArbore(root->stg);
		afisareMasiniDinArbore(root->dr);
	}
}

void dezalocareArboreDeMasini(Nod** root) {
	if (*root) {
		dezalocareArboreDeMasini(&(*root)->stg);
		dezalocareArboreDeMasini(&(*root)->dr);
		free((*root)->info.model);
		free((*root)->info.numeSofer);
		free(*root);
		(*root) = NULL;
	}
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(Nod* root, const char* numeSofer) {
	float sum = 0;
	if(root) {
		sum += calculeazaPretulMasinilorUnuiSofer(root->stg, numeSofer);
		sum += calculeazaPretulMasinilorUnuiSofer(root->dr, numeSofer);
		if (strcmp(root->info.numeSofer, numeSofer) == 0) {
			sum += root->info.pret;
		}

	}
	return sum;
}

int main() {
	Nod* root = citireArboreDeMasiniDinFisier("masini.txt");
	float pret = calculeazaPretulMasinilorUnuiSofer(root, "Ionescu");
	printf("Pretul masinii lui Ionescu este: %.2f", pret);
	afisareMasiniDinArbore(root);
	dezalocareArboreDeMasini(&root);

	return 0;
}