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

//creare structura pentru un nod dintr-un arbore binar de cautare

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


void adaugaMasinaInArbore(Nod** root, Masina masinaNoua) {
	if ((*root) == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->dr = NULL;
		nou->stg = NULL;
		nou->info = masinaNoua;
		(*root) = nou;
		return;
	}
	if (masinaNoua.id < (*root)->info.id) {
		adaugaMasinaInArbore(&(*root)->stg, masinaNoua);
	}
	else {
		adaugaMasinaInArbore(&(*root)->dr, masinaNoua);
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	Nod* nou = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		adaugaMasinaInArbore(&nou, citireMasinaDinFisier(file));
	}
	fclose(file);
	return nou;
}

void afisareMasiniDinArbore(Nod* root) {
	//afisam inordine aici
	if (root) {
		afisareMasiniDinArbore(root->stg);
		afisareMasiniDinArbore(root);
		afisareMasiniDinArbore(root->dr);
	}
}

void afiseazaPostordine(Nod* root) {
	if (root) {
		afiseazaPostordine(root->stg);
		afiseazaPostordine(root->dr);
		afiseazaPostordine(root);
	}
}

void dezalocareArboreDeMasini(Nod** root) {
	if (*root) {
		dezalocareArboreDeMasini(&(*root)->stg);
		dezalocareArboreDeMasini(&(*root));
		dezalocareArboreDeMasini(&(*root)->dr);
		free((*root)->info.model);
		free((*root)->info.numeSofer);
		free(*root);
		*root = NULL;
	}
}

Masina getMasinaByID(Nod* root,int id) {
	Masina m;
	if (root) {
		if (root->info.id == id) {
			m = root->info;
			m.model = malloc(strlen(m.model) + 1);
			strcpy_s(m.model, strlen(m.model) + 1, root->info.model);
			m.numeSofer = malloc(strlen(m.numeSofer) + 1);
			strcpy_s(m.numeSofer, strlen(m.numeSofer) + 1, root->info.numeSofer);
			return m;
		}
		else {
			if (root->info.id <= id) {
				m = getMasinaByID(root->dr, id);
			}
			else {
				m = getMasinaByID(root->stg, id);
			}
		}
	}
	else {
		m.id = -1;
	}
	return m;
}

int determinaNumarNoduri(Nod* root) {
	if (root) {
		int nrNoduriStg = determinaNumarNoduri(root->stg);
		int nrNoduriDr = determinaNumarNoduri(root->dr);
		return 1 + nrNoduriDr + nrNoduriStg;
	}
	else 
	return 0;
}

int calculeazaMax(int a, int b) {
	return (a > b) ? a : b;
}

int calculeazaInaltimeArbore(Nod* root) {
	if (root) {
		return -1;
	}
	else {
		return 1 + calculeazaMax(calculeazaInaltimeArbore(root->dr), calculeazaInaltimeArbore(root->stg));
	}
}

float calculeazaPretTotal(Nod* root) {
	if (root == NULL)
		return 0;
	else {
		float pretStg = calculeazaPretTotal(root->stg);
		float pretDr = calculeazaPretTotal(root->dr);
		return pretDr + pretStg + root->info.pret;
	}
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* tree = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareMasiniDinArbore(tree);
	afisareMasina(getMasinaByID(tree, 3));
	int nrNoduri = determinaNumarNoduri(tree);
	printf("Nr total noduri: %d", nrNoduri);
	printf("Inaltime arbore: %d", calculeazaInaltimeArbore(tree));
	float pretTotal = calculeazaPretTotal(tree);
	printf("Pret total: %.2f", pretTotal);
	dezalocareArboreDeMasini(&tree);

	return 0;
}