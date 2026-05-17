#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
	int id;
	int varsta;
	float medie;
	char* nume;
	char* facultate;
	unsigned char grupa;
};

typedef struct Student Student;
typedef struct Nod Nod;

struct Nod {
	Student info;
	Nod* stg;
	Nod* dr;
};

Student citireStudentDinFisier(FILE* f) {
	Student s;
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, f);
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	s.varsta = atoi(strtok(NULL, sep));
	s.medie = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	s.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.facultate = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.facultate, strlen(aux) + 1, aux);
	s.grupa = *strtok(NULL, sep);
	return s;
}

void afisareStudent(Student s) {
	printf("ID: %d\n", s.id);
	printf("Varsta: %d\n", s.varsta);
	printf("Medie: %.2f\n", s.medie);
	printf("Nume: %s\n", s.nume);
	printf("Facultate: %s\n", s.facultate);
	printf("Grupa: %c\n", s.grupa);
}

void adaugaStudentInArbore(Nod** root, Student s) {
	if ((*root)) {
		if (s.id < (*root)->info.id) {
			adaugaStudentInArbore(&(*root)->stg, s);
		}
		else if (s.id > (*root)->info.id) {
			adaugaStudentInArbore(&(*root)->dr, s);
		}
	}
	else {
		(*root) = (Nod*)malloc(sizeof(Nod));
		(*root)->dr = NULL;
		(*root)->stg = NULL;
		(*root)->info = s;
		(*root)->info.nume = (char*)malloc(strlen(s.nume) + 1);
		strcpy_s((*root)->info.nume, strlen(s.nume) + 1, s.nume);
		(*root)->info.facultate = (char*)malloc(strlen(s.facultate) + 1);
		strcpy_s((*root)->info.facultate, strlen(s.facultate) + 1, s.facultate);
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(f)) {
		Student s = citireStudentDinFisier(f);
		adaugaStudentInArbore(&radacina, s);
		free(s.facultate);
		free(s.nume);
	}
	fclose(f);
	return radacina;
}

void afiseazaArboreInOrdine(Nod* radacina) {
	if (radacina) {
		afiseazaArboreInOrdine(radacina->stg);
		afisareStudent(radacina->info);
		afiseazaArboreInOrdine(radacina->dr);
	}
}

void afiseazaArborePreOrdine(Nod* radacina) {
	if (radacina) {
		afisareStudent(radacina->info);
		afiseazaArborePreOrdine(radacina->stg);
		afiseazaArborePreOrdine(radacina->dr);
	}
}

void afiseazaPostOrdine(Nod* radacina) {
	if (radacina) {
		afiseazaPostOrdine(radacina->stg);
		afiseazaPostOrdine(radacina->dr);
		afisareStudent(radacina->info);
	}
}

void dezalocareArbore(Nod** radacina) {
	if ((*radacina)) {
		dezalocareArbore(&(*radacina)->dr);
		dezalocareArbore(&(*radacina)->stg);
		free((*radacina)->info.facultate);
		free((*radacina)->info.nume);
		free(*radacina);
		(*radacina) = NULL;
	}
}

Student getStudentByID(Nod* radacina, int id) {
	Student s;
	s.id = -1;
	if (id > radacina->info.id) {
		return getStudentByID(radacina->dr, id);
	}
	else if (id < radacina->info.id) {
		return getStudentByID(radacina->stg, id);
	}
	else {
		s = radacina->info;
		s.facultate = (char*)malloc(strlen(radacina->info.facultate) + 1);
		strcpy(s.facultate, radacina->info.facultate);

		s.nume = (char*)malloc(strlen(radacina->info.nume) + 1);
		strcpy(s.nume, radacina->info.nume);
		return s;
	}
	return s;
}

int determinaNrNoduri(Nod* radacina) {
	if (radacina) {
		return 1 + determinaNrNoduri(radacina->stg) + determinaNrNoduri(radacina->dr);
	}
	else return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina) {
		return max(calculeazaInaltimeArbore(radacina->dr), calculeazaInaltimeArbore(radacina->stg));
	}
}

int main() {
	Nod* arbore = citireArboreDinFisier("studenti.txt");
	printf("AFISARE INORDINE\n");
	afiseazaArboreInOrdine(arbore);
	printf("\n\nAFISARE PREORDINE\n");
	afiseazaArborePreOrdine(arbore);
	printf("\n\nAFISARE POSTORDINE\n");
	afiseazaPostOrdine(arbore);

	Student s = getStudentByID(arbore, 3);
	printf("\n\nStudentul cu id ul 3 este:\n");
	afisareStudent(s);

	int nrNoduri = determinaNrNoduri(arbore);
	printf("\n\nNumar noduri: %d\n", nrNoduri);

	int inaltime = calculeazaInaltimeArbore(arbore);
	printf("\n\nInaltimea este: %d\n", inaltime);
}
